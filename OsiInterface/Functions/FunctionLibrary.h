#pragma once

#include "../CustomFunctions.h"
#include "../ExtensionState.h"
#include <GameDefinitions/EntitySystem.h>
#include <GameDefinitions/Character.h>
#include <GameDefinitions/Item.h>
#include <GameDefinitions/GameAction.h>
#include <GameDefinitions/Misc.h>
#include <GameDefinitions/ActionMachine.h>

namespace dse
{
	class OsirisProxy;
	struct UIObjectManager;
}

namespace dse::esv
{
	class CustomFunctionLibrary
	{
	public:
		CustomFunctionLibrary(OsirisProxy & osiris);

		void Register();
		void RegisterHelperFunctions();
		void RegisterMathFunctions();
		void RegisterStatFunctions();
		void RegisterStatusFunctions();
		void RegisterGameActionFunctions();
		void RegisterProjectileFunctions();
		void RegisterHitFunctions();
		void RegisterPlayerFunctions();
		void RegisterItemFunctions();
		void RegisterCharacterFunctions();
		void RegisterCustomStatFunctions();
		void RegisterLuaFunctions();

		void PostStartup();
		void OnBaseModuleLoadedServer();
		void OnBaseModuleLoadedClient();

		int32_t OnStatusGetEnterChance(esv::Status__GetEnterChance wrappedGetEnterChance, 
			esv::Status * status, bool isEnterCheck);
		int32_t OnGetHitChance(CDivinityStats_Character__GetHitChance * wrappedGetHitChance, 
			CDivinityStats_Character * attacker, CDivinityStats_Character * target);
		void OnStatusHealEnter(esv::Status * status);

		void OnActionMachineSetState(esv::ActionMachine * self, uint64_t actionLayer, esv::ActionState * actionState, int * somePtr, bool force, bool setLayer, bool succeeded);
		void OnSkillFormatDescriptionParam(SkillPrototype::FormatDescriptionParam next, SkillPrototype *skillPrototype,
			CDivinityStats_Character *tgtCharStats, eoc::Text *eocText, int paramIndex, bool isFromItem,
			float xmm9_4_0, FixedString * paramText, ObjectSet<STDString> * stdStringSet);
		void OnStatusFormatDescriptionParam(StatusPrototype::FormatDescriptionParam next, StatusPrototype *prototype, 
			CRPGStats_ObjectInstance* owner, CRPGStats_ObjectInstance* statusSource, float multiplier,
			eoc::Text * text, int paramIndex, FixedString * param, ObjectSet<STDString> * paramSet);
		void OnUpdateTurnOrder(esv::TurnManager * self, uint8_t combatId);
		void OnCreateUIObject(UIObjectManager* self, ObjectHandle* handle, unsigned int layerIndex, unsigned int creatorId, int flags, 
			uint64_t resourceFlags, uint16_t playerId, ObjectHandle* result);

		void ThrowStatusHitEnter(esv::Status* status);
		void ThrowCharacterHit(esv::Character* self, CDivinityStats_Character* attackerStats,
			CDivinityStats_Item* itemStats, DamagePairList* damageList, HitType hitType, bool noHitRoll,
			HitDamageInfo* damageInfo, int forceReduceDurability, CRPGStats_Object_Property_List* skillProperties, HighGroundBonus highGround,
			bool procWindWalker, CriticalRoll criticalRoll, DamageHelpers& helper);
		void ThrowApplyStatus(esv::StatusMachine* self, esv::Status* status);

	private:
		OsirisProxy & osiris_;
		bool PostLoaded{ false };
	};

}