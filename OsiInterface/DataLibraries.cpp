#include "stdafx.h"
#include "DataLibraries.h"
#include "ExtensionState.h"
#include "OsirisProxy.h"
#include <GameDefinitions/Symbols.h>
#include <string>
#include <functional>
#include <psapi.h>
#include <DbgHelp.h>

namespace osidbg
{
	void InitPropertyMaps();

	decltype(LibraryManager::StatusGetEnterChance) * decltype(LibraryManager::StatusGetEnterChance)::gHook;
	decltype(LibraryManager::StatusHealEnter) * decltype(LibraryManager::StatusHealEnter)::gHook;
	decltype(LibraryManager::StatusHitEnter) * decltype(LibraryManager::StatusHitEnter)::gHook;
	decltype(LibraryManager::CharacterHitHook) * decltype(LibraryManager::CharacterHitHook)::gHook;
	decltype(LibraryManager::ApplyStatusHook) * decltype(LibraryManager::ApplyStatusHook)::gHook;

	bool GlobalStringTable::UseMurmur = false;

	uint8_t CharToByte(char c)
	{
		if (c >= '0' && c <= '9') {
			return c - '0';
		}
		else if (c >= 'A' && c <= 'F') {
			return c - 'A' + 0x0A;
		}
		else if (c >= 'a' && c <= 'f') {
			return c - 'a' + 0x0A;
		}
		else {
			Fail("Invalid hexadecimal character");
		}
	}

	uint8_t HexByteToByte(char c1, char c2)
	{
		uint8_t hi = CharToByte(c1);
		uint8_t lo = CharToByte(c2);
		return (hi << 4) | lo;
	}

	void Pattern::FromString(std::string const & s)
	{
		if (s.size() % 3) Fail("Invalid pattern length");
		auto len = s.size() / 3;
		if (!len) Fail("Zero-length patterns not allowed");

		pattern_.clear();
		pattern_.reserve(len);

		char const * c = s.data();
		for (auto i = 0; i < len; i++) {
			PatternByte b;
			if (c[2] != ' ') Fail("Bytes must be separated by space");
			if (c[0] == 'X' && c[1] == 'X') {
				b.pattern = 0;
				b.mask = 0;
			}
			else {
				b.pattern = HexByteToByte(c[0], c[1]);
				b.mask = 0xff;
			}

			pattern_.push_back(b);
			c += 3;
		}

		if (pattern_[0].mask != 0xff) Fail("First byte of pattern must be an exact match");
	}

	void Pattern::FromRaw(const char * s)
	{
		auto len = strlen(s) + 1;
		pattern_.resize(len);
		for (auto i = 0; i < len; i++) {
			pattern_[i].pattern = (uint8_t)s[i];
			pattern_[i].mask = 0xFF;
		}
	}

	bool Pattern::MatchPattern(uint8_t const * start)
	{
		auto p = start;
		for (auto const & pattern : pattern_) {
			if ((*p++ & pattern.mask) != pattern.pattern) {
				return false;
			}
		}

		return true;
	}

	void Pattern::ScanPrefix1(uint8_t const * start, uint8_t const * end, std::function<std::optional<bool> (uint8_t const *)> callback, bool multiple)
	{
		uint8_t initial = pattern_[0].pattern;

		for (auto p = start; p < end; p++) {
			if (*p == initial) {
				if (MatchPattern(p)) {
					auto matched = callback(p);
					if (!multiple || (matched && *matched)) return;
				}
			}
		}
	}

	void Pattern::ScanPrefix2(uint8_t const * start, uint8_t const * end, std::function<std::optional<bool> (uint8_t const *)> callback, bool multiple)
	{
		uint16_t initial = pattern_[0].pattern
			| (pattern_[1].pattern << 8);

		for (auto p = start; p < end; p++) {
			if (*reinterpret_cast<uint16_t const *>(p) == initial) {
				if (MatchPattern(p)) {
					auto matched = callback(p);
					if (!multiple || (matched && *matched)) return;
				}
			}
		}
	}

	void Pattern::ScanPrefix4(uint8_t const * start, uint8_t const * end, std::function<std::optional<bool> (uint8_t const *)> callback, bool multiple)
	{
		uint32_t initial = pattern_[0].pattern
			| (pattern_[1].pattern << 8)
			| (pattern_[2].pattern << 16)
			| (pattern_[3].pattern << 24);

		for (auto p = start; p < end; p++) {
			if (*reinterpret_cast<uint32_t const *>(p) == initial) {
				if (MatchPattern(p)) {
					auto matched = callback(p);
					if (!multiple || (matched && *matched)) return;
				}
			}
		}
	}

	void Pattern::Scan(uint8_t const * start, size_t length, std::function<std::optional<bool> (uint8_t const *)> callback, bool multiple)
	{
		// Check prefix length
		auto prefixLength = 0;
		for (auto i = 0; i < pattern_.size(); i++) {
			if (pattern_[i].mask == 0xff) {
				prefixLength++;
			} else {
				break;
			}
		}

		auto end = start + length - pattern_.size();
		if (prefixLength >= 4) {
			ScanPrefix4(start, end, callback, multiple);
		} else if (prefixLength >= 2) {
			ScanPrefix2(start, end, callback, multiple);
		} else {
			ScanPrefix1(start, end, callback, multiple);
		}
	}

	bool LibraryManager::IsConstStringRef(uint8_t const * ref, char const * str) const
	{
		return
			ref >= moduleStart_ 
			&& ref < moduleStart_ + moduleSize_
			&& strcmp((char const *)ref, str) == 0;
	}

	bool LibraryManager::IsFixedStringRef(uint8_t const * ref, char const * str) const
	{
		if (ref >= moduleStart_ && ref < moduleStart_ + moduleSize_) {
			auto fsx = (FixedString const *)ref;
			if (*fsx && strcmp(fsx->Str, str) == 0) {
				return true;
			}
		}

		return false;
	}

	bool LibraryManager::EvaluateSymbolCondition(SymbolMappingCondition const & cond, uint8_t const * match)
	{
		uint8_t const * ptr{ nullptr };
		switch (cond.Type) {
		case SymbolMappingCondition::kString:
			ptr = AsmLeaToAbsoluteAddress(match + cond.Offset);
			return ptr != nullptr && IsConstStringRef(ptr, cond.String);

		case SymbolMappingCondition::kFixedString:
			ptr = AsmLeaToAbsoluteAddress(match + cond.Offset);
			return ptr != nullptr && IsFixedStringRef(ptr, cond.String);

		case SymbolMappingCondition::kNone:
		default:
			return true;
		}
	}

	SymbolMappingResult LibraryManager::ExecSymbolMappingAction(SymbolMappingTarget const & target, uint8_t const * match)
	{
		if (target.Type == SymbolMappingTarget::kNone) return SymbolMappingResult::Success;

		uint8_t const * ptr{ nullptr };
		switch (target.Type) {
		case SymbolMappingTarget::kAbsolute:
			ptr = match + target.Offset;
			break;

		case SymbolMappingTarget::kIndirectCall:
			ptr = AsmCallToAbsoluteAddress(match + target.Offset);
			break;

		case SymbolMappingTarget::kIndirectLea:
			ptr = AsmLeaToAbsoluteAddress(match + target.Offset);
			break;

		default:
			break;
		}

		if (ptr != nullptr) {
			if (target.TargetPtr != nullptr) {
				*target.TargetPtr = const_cast<uint8_t *>(ptr);
			}

			if (target.NextSymbol != nullptr) {
				if (!MapSymbol(*target.NextSymbol, ptr, target.NextSymbolSeekSize)) {
					return SymbolMappingResult::Fail;
				}
			}

			if (target.Handler != nullptr) {
				return target.Handler(ptr);
			} else {
				return SymbolMappingResult::Success;
			}
		} else {
			ERR("Could not map match to symbol address while resolving '%s'", target.Name);
			return SymbolMappingResult::Fail;
		}
	}

	bool LibraryManager::MapSymbol(SymbolMappingData const & mapping, uint8_t const * customStart, std::size_t customSize)
	{
		Pattern p;
		p.FromString(mapping.Matcher);

		uint8_t const * memStart;
		std::size_t memSize;

		switch (mapping.Scope) {
		case SymbolMappingData::kBinary:
			memStart = moduleStart_;
			memSize = moduleSize_;
			break;

		case SymbolMappingData::kText:
			memStart = moduleTextStart_;
			memSize = moduleTextSize_;
			break;

		case SymbolMappingData::kCustom:
			memStart = customStart;
			memSize = customSize;
			break;

		default:
			memStart = nullptr;
			memSize = 0;
			break;
		}

		bool mapped = false;
		p.Scan(memStart, memSize, [this, &mapping, &mapped](const uint8_t * match) -> std::optional<bool> {
			if (EvaluateSymbolCondition(mapping.Conditions, match)) {
				auto action1 = ExecSymbolMappingAction(mapping.Target1, match);
				auto action2 = ExecSymbolMappingAction(mapping.Target2, match);
				auto action3 = ExecSymbolMappingAction(mapping.Target3, match);
				mapped = action1 == SymbolMappingResult::Success 
					&& action2 == SymbolMappingResult::Success
					&& action3 == SymbolMappingResult::Success;
				return action1 != SymbolMappingResult::TryNext 
					&& action2 != SymbolMappingResult::TryNext
					&& action3 != SymbolMappingResult::TryNext;
			} else {
				return {};
			}
		});

		if (!mapped && !(mapping.Flag & SymbolMappingData::kAllowFail)) {
			ERR("No match found for mapping '%s'", mapping.Name);
			InitFailed = true;
			if (mapping.Flag & SymbolMappingData::kCritical) {
				CriticalInitFailed = true;
			}
		}

		return mapped;
	}


	uint8_t const * AsmCallToAbsoluteAddress(uint8_t const * call)
	{
		if (call[0] != 0xE8) {
			ERR("AsmCallToAbsoluteAddress(): Not a call @ %p", call);
			return nullptr;
		}

		int32_t rel = *(int32_t const *)(call + 1);
		return call + rel + 5;
	}

	uint8_t const * AsmLeaToAbsoluteAddress(uint8_t const * lea)
	{
		if ((lea[0] != 0x48 && lea[0] != 0x4C) || (lea[1] != 0x8D && lea[1] != 0x8B)) {
			ERR("AsmLeaToAbsoluteAddress(): Not a LEA @ %p", lea);
			return nullptr;
		}

		int32_t rel = *(int32_t const *)(lea + 3);
		return lea + rel + 7;
	}

	void LibraryManager::FindTextSegment()
	{
		IMAGE_NT_HEADERS * pNtHdr = ImageNtHeader(const_cast<uint8_t *>(moduleStart_));
		IMAGE_SECTION_HEADER * pSectionHdr = (IMAGE_SECTION_HEADER *)(pNtHdr + 1);

		for (std::size_t i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++) {
			if (memcmp(pSectionHdr->Name, ".text", 6) == 0) {
				moduleTextStart_ = moduleStart_ + pSectionHdr->VirtualAddress;
				moduleTextSize_ = pSectionHdr->SizeOfRawData;
				return;
			}
		}

		// Fallback, if .text segment was not found
		moduleTextStart_ = moduleStart_;
		moduleTextSize_ = moduleSize_;
	}

	bool LibraryManager::FindLibraries()
	{
		memset(&gCharacterStatsGetters.Ptrs, 0, sizeof(gCharacterStatsGetters.Ptrs));

#if defined(OSI_EOCAPP)
		if (FindEoCApp(moduleStart_, moduleSize_)) {
#else
		if (FindEoCPlugin(moduleStart_, moduleSize_)) {
#endif

			FindTextSegment();
			MapAllSymbols(false);

#if defined(OSI_EOCAPP)
			FindServerGlobalsEoCApp();
			FindEoCGlobalsEoCApp();
			FindGlobalStringTableEoCApp();
#else
			FindExportsEoCPlugin();
			FindServerGlobalsEoCPlugin();
			FindEoCGlobalsEoCPlugin();
			FindGlobalStringTableCoreLib();
#endif

			return !CriticalInitFailed;
		} else {
			ERR("LibraryManager::FindLibraries(): Unable to determine application type.");
			return false;
		}
	}

	bool LibraryManager::PostStartupFindLibraries()
	{
		if (PostLoaded) {
			return !CriticalInitFailed;
		}

		auto initStart = std::chrono::high_resolution_clock::now();

		MapAllSymbols(true);

		if (!CriticalInitFailed) {
			InitPropertyMaps();

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());

			if (gStaticSymbols.StatusHitVMT != nullptr) {
				StatusHitEnter.Wrap(gStaticSymbols.StatusHitVMT->Enter);
			}

			if (gStaticSymbols.StatusHealVMT != nullptr) {
				StatusHealEnter.Wrap(gStaticSymbols.StatusHealVMT->Enter);
				StatusGetEnterChance.Wrap(gStaticSymbols.StatusHealVMT->GetEnterChance);
			}

			if (gStaticSymbols.CharacterHit != nullptr) {
				CharacterHitHook.Wrap(gStaticSymbols.CharacterHit);
			}

			if (gStaticSymbols.StatusMachineApplyStatus != nullptr) {
				ApplyStatusHook.Wrap(gStaticSymbols.StatusMachineApplyStatus);
			}

			gCharacterStatsGetters.WrapAll();

			DetourTransactionCommit();

			// Temporary workaround for crash when GetMaxMP is wrapped
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			if (gCharacterStatsGetters.GetMaxMp != nullptr) {
				gCharacterStatsGetters.WrapperMaxMp.Unwrap();
			}
			DetourTransactionCommit();
		}

		auto initEnd = std::chrono::high_resolution_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(initEnd - initStart).count();
		DEBUG("LibraryManager::PostStartupFindLibraries() took %d ms", ms);

		PostLoaded = true;
		return !CriticalInitFailed;
	}

	void LibraryManager::Cleanup()
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());

		StatusGetEnterChance.Unwrap();
		StatusHitEnter.Unwrap();
		StatusHealEnter.Unwrap();
		CharacterHitHook.Unwrap();
		ApplyStatusHook.Unwrap();

		DetourTransactionCommit();
	}

	void LibraryManager::ShowStartupError(std::wstring const & msg, bool wait, bool exitGame)
	{
		ERR(L"STARTUP ERROR: %s", msg.c_str());

		if (gStaticSymbols.EoCClient == nullptr
			|| gStaticSymbols.EoCClientHandleError == nullptr
			|| EoCAlloc == nullptr) {
			return;
		}

		if (wait) {
			std::thread messageThread([this, msg, exitGame]() {
				unsigned retries{ 0 };
				while (!CanShowError() && retries < 600) {
					Sleep(100);
					retries++;
				}

				STDWString str;
				str.Set(msg);
				gStaticSymbols.EoCClientHandleError(*gStaticSymbols.EoCClient, &str, exitGame, &str);
			});
			messageThread.detach();
		} else {
			STDWString str;
			str.Set(msg);
			gStaticSymbols.EoCClientHandleError(*gStaticSymbols.EoCClient, &str, exitGame, &str);
		}
	}

	bool LibraryManager::CanShowError()
	{
		if (gStaticSymbols.EoCClient == nullptr
			|| *gStaticSymbols.EoCClient == nullptr
			|| (*gStaticSymbols.EoCClient)->GameStateMachine == nullptr
			|| *(*gStaticSymbols.EoCClient)->GameStateMachine == nullptr
			|| gStaticSymbols.EoCClientHandleError == nullptr) {
			return false;
		}

		auto state = (*(*gStaticSymbols.EoCClient)->GameStateMachine)->State;
		return state == GameState::Running
			|| state == GameState::Paused
			|| state == GameState::GameMasterPause
			|| state == GameState::Menu
			|| state == GameState::Lobby;
	}

	class WriteAnchor
	{
	public:
		WriteAnchor(uint8_t const * ptr, std::size_t size)
			: ptr_(const_cast<uint8_t *>(ptr)),
			size_(size)
		{
			BOOL succeeded = VirtualProtect((LPVOID)ptr_, size_, PAGE_READWRITE, &oldProtect_);
			if (!succeeded) Fail("VirtualProtect() failed");
		}

		~WriteAnchor()
		{
			BOOL succeeded = VirtualProtect((LPVOID)ptr_, size_, oldProtect_, &oldProtect_);
			if (!succeeded) Fail("VirtualProtect() failed");
		}

		inline uint8_t * ptr()
		{
			return ptr_;
		}

	private:
		uint8_t * ptr_;
		std::size_t size_;
		DWORD oldProtect_;
	};

	void LibraryManager::EnableCustomStats()
	{
		if (gStaticSymbols.UICharacterSheetHook == nullptr
			|| gStaticSymbols.ActivateClientSystemsHook == nullptr
			|| gStaticSymbols.ActivateServerSystemsHook == nullptr
			|| gStaticSymbols.CustomStatUIRollHook == nullptr) {
			ERR("LibraryManager::EnableCustomStats(): Hooks not available");
			return;
		}

		if (ExtensionState::Get().HasFeatureFlag("CustomStats") && !EnabledCustomStats) {
			{
				uint8_t const replacement[] = { 0x90, 0x90 };
				WriteAnchor code(gStaticSymbols.ActivateClientSystemsHook, sizeof(replacement));
				memcpy(code.ptr(), replacement, sizeof(replacement));
			}

			{
				uint8_t const replacement[] = { 0x90, 0x90 };
				WriteAnchor code(gStaticSymbols.ActivateServerSystemsHook, sizeof(replacement));
				memcpy(code.ptr(), replacement, sizeof(replacement));
			}

			{
				uint8_t const replacement[] = { 0xC3 };
				WriteAnchor code(gStaticSymbols.CustomStatUIRollHook, sizeof(replacement));
				memcpy(code.ptr(), replacement, sizeof(replacement));
			}

			EnabledCustomStats = true;
		}

		if (ExtensionState::Get().HasFeatureFlag("CustomStats")
			&& ExtensionState::Get().HasFeatureFlag("CustomStatsPane")
			&& !EnabledCustomStatsPane) {
			uint8_t const replacement[] = {
#if defined(OSI_EOCAPP)
				0xc6, 0x45, 0xf8, 0x01
#else
				0xB2, 0x01, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
#endif
			};

			WriteAnchor code(gStaticSymbols.UICharacterSheetHook, sizeof(replacement));
			memcpy(code.ptr(), replacement, sizeof(replacement));
			EnabledCustomStatsPane = true;
		}
	}
}
