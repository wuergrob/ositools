#pragma once

#include "DivBaseTypes.h"

namespace osidbg
{

#pragma pack(push, 1)
	struct CRPGStats_Object
	{
		void * VMT;
		uint32_t A;
		uint32_t Unused1;
		uint32_t ModifierListIndex;
		uint32_t Unused2;
		int32_t * IndexedProperties;
		uint64_t Unused3;
		uint64_t Unused4;
		char * Name;
		TranslatedString TranslatedStringX;
		uint64_t B[18];
		FixedString FS2;
		uint64_t EntryType;
		FixedStringMapBase<int> PropertyList;
		uint32_t Unused5;
		FixedStringMapBase<int> ConditionList;
		uint32_t Unused6;
		uint64_t AIFlags;
		ObjectSet<void *> Requirements; // Set<Requirement>
		ObjectSet<void *> MemorizationRequirements; // Set<Requirement>
		ObjectSet<void *> CrimeReactionPriorities; // Set<CrimeReactionPriority>
		ObjectSet<FixedString> StringProperties1;
		ObjectSet<FixedString> ComboCategories;
		void * SomeSTDWSTRING;
		uint64_t C[3];
		uint32_t Using;
		uint32_t D;
	};

	struct CRPGStats_ObjectInstance : public CRPGStats_Object
	{
		uint32_t InstanceId;
	};

	struct CDivinityStats_Equipment_Attributes
	{
		enum StatsType : uint32_t
		{
			ST_Weapon = 0,
			ST_Armor = 1,
			ST_Shield = 2
		};

		void * VMT;
		uint32_t InstanceId;
		uint32_t Unkn0;
		uint64_t Unkn1;
		int32_t Durability;
		int32_t DurabilityDegradeSpeed;
		int32_t StrengthBoost;
		int32_t FinesseBoost;
		int32_t IntelligenceBoost;
		int32_t ConstitutionBoost;
		int32_t Memory;
		int32_t WitsBoost;
		int32_t SightBoost;
		int32_t HearingBoost;
		int32_t VitalityBoost;
		int32_t SourcePointsBoost;
		int32_t MaxAP;
		int32_t StartAP;
		int32_t APRecovery;
		int32_t AccuracyBoost;
		int32_t DodgeBoost;
		int32_t LifeSteal;
		int32_t CriticalChance;
		int32_t ChanceToHitBoost;
		int32_t MovementSpeedBoost;
		int32_t RuneSlots;
		int32_t RuneSlots_V1;
		int32_t FireResistance;
		int32_t AirResistance;
		int32_t WaterResistance;
		int32_t EarthResistance;
		int32_t PoisonResistance;
		int32_t TenebriumResistance;
		int32_t PiercingResistance;
		int32_t CorrosiveResistance;
		int32_t PhysicalResistance;
		int32_t MagicResistance;
		int32_t CustomResistance;
		int32_t Movement;
		int32_t Initiative;
		int32_t Willpower;
		int32_t Bodybuilding;
		int32_t MaxSummons;
		int32_t AbilityModifiers[40];
		int32_t Value;
		int32_t Weight;
		uint32_t Unkn2;
		void * Reflection;
		FixedString Skills;
		FixedString ItemColor;
		uint32_t ModifierType;
		uint32_t Unkn3;
		FixedString ObjectInstanceName;
		FixedString FS4;
		uint32_t EquipmentStatsType;
		uint32_t Talents[4];
		uint32_t Unkn4;
		uint64_t Flags;
	};

	struct CDivinityStats_Equipment_Attributes_Weapon : public CDivinityStats_Equipment_Attributes
	{
		int32_t DamageType;
		int32_t MinDamage;
		int32_t MaxDamage;
		int32_t DamageBoost;
		int32_t DamageFromBase;
		int32_t CriticalDamage;
		float WeaponRange;
		int32_t CleaveAngle;
		float CleavePercentage;
		int32_t AttackAPCost;
	};

	struct CDivinityStats_Equipment_Attributes_Shield : public CDivinityStats_Equipment_Attributes
	{
		int32_t ArmorValue;
		int32_t ArmorBoost;
		int32_t MagicArmorValue;
		int32_t MagicArmorBoost;
		int32_t Blocking;
	};

	struct CDivinityStats_Equipment_Attributes_Armor : public CDivinityStats_Equipment_Attributes
	{
		int32_t ArmorValue;
		int32_t ArmorBoost;
		int32_t MagicArmorValue;
		int32_t MagicArmorBoost;
	};

	struct CDivinityStats_Item : public CRPGStats_ObjectInstance
	{
		uint32_t _Pad0;
		uint32_t U1;
		uint32_t ItemType;
		uint32_t ItemSlot;
		uint32_t WeaponType;
		uint32_t AnimType;
		uint32_t WeaponRange;
		uint32_t IsIdentified;
		uint32_t U2;
		uint32_t U3;
		uint32_t U4;
		bool IsTwoHanded;
		bool HasAddedItems_M;
		bool U5;
		bool HasModifiedSkills;
		uint32_t U6;
		uint64_t Skills;
		uint32_t DamageTypeOverwrite;
		uint32_t Durability;
		uint32_t DurabilityCounter;
		uint32_t U7;
		FixedString ItemTypeReal;
		FixedString U8;
		CDivinityStats_Equipment_Attributes ** DynamicAttributes_Start;
		CDivinityStats_Equipment_Attributes ** DynamicAttributes_End;
		uint64_t U9[3];
		uint32_t MaxCharges;
		uint32_t Charges;
		uint8_t LevelGroupIndex;
		uint8_t RootGroupIndex;
		uint8_t NameGroupIndex;
		uint8_t NameIndex;
		uint32_t NameCool;
		ObjectSet<void *> Tags_Maybe;
		ObjectSet<FixedString> BoostNameSet;
		uint64_t U10[12];
	};

	struct EoCGameRandom
	{
		uint64_t Unkn0;
		uint32_t Unkn1[7];
		uint8_t Unkn2;
	};

	struct CharacterEquippedItem
	{
		uint32_t ItemStatsHandle;
		uint8_t ItemSlot;
		bool IsEquipped;
	};

	struct CharacterStat
	{
		uint64_t Unkn0;
		uint64_t Unkn1;

		uint32_t SummonLifelinkModifier;
		uint32_t Strength;
		uint32_t Memory;
		uint32_t Intelligence;
		uint32_t Movement;
		uint32_t MovementSpeedBoost;
		uint32_t Finesse;
		uint32_t Wits;
		uint32_t Constitution;

		uint32_t FireResistance;
		uint32_t EarthResistance;
		uint32_t WaterResistance;
		uint32_t AirResistance;
		uint32_t PoisonResistance;
		uint32_t ShadowResistance;

		uint32_t Willpower;
		uint32_t Bodybuilding;
		uint32_t PiercingResistance;
		uint32_t PhysicalResistance;
		uint32_t CorrosiveResistance;
		uint32_t MagicResistance;
		uint32_t CustomResistance;

		uint32_t Sight;
		uint32_t Hearing;
		uint32_t FOV;
		uint32_t APMaximum;
		uint32_t APStart;
		uint32_t APRecovery;
		uint32_t CriticalChance;
		uint32_t Initiative;
		uint32_t Vitality;
		uint32_t VitalityBoost;
		uint32_t MagicPoints;
		uint32_t Level;
		uint32_t Gain;

		uint32_t Armor;
		uint32_t MagicArmor;
		uint32_t ArmorBoost;
		uint32_t MagicArmorBoost;
		uint32_t ArmorBoostGrowthPerLevel;
		uint32_t MagicArmorBoostGrowthPerLevel;
		uint32_t DamageBoost;
		uint32_t DamageBoostGrowthPerLevel;

		uint32_t Accuracy;
		uint32_t Dodge;
		uint32_t MaxResistance;
		uint32_t LifeSteal;
		uint32_t Weight;
		uint32_t ChanceToHitBoost;
		uint32_t RangeBoost;
		uint32_t APCostBoost;
		uint32_t SPCostBoost;
		uint32_t MaxSummons;
		uint32_t Abilities[40];
		uint32_t BonusWeaponDamageMultiplier;
		uint32_t Talents[4];
		uint32_t RemovedTalents[4];
		uint16_t Traits[18];
		uint32_t BoostConditionsMask;
		FixedString TranslationKey;
		FixedString BonusWeapon;
		uint64_t Reflection;
		uint32_t Unkn2;
		uint32_t Unkn3;
		uint64_t AttributeFlags;
		uint32_t Unkn4;
	};

	struct CDivinityStats_Character : public CRPGStats_ObjectInstance
	{
		uint32_t _Pad0;
		uint32_t CurrentVitality;
		uint32_t CurrentArmor;
		uint32_t CurrentMagicArmor;
		uint32_t ArmorAfterHitCooldownMultiplier;
		uint32_t MagicArmorAfterHitCooldownMultiplier;
		uint32_t MPStart;
		uint32_t CurrentAP;
		uint32_t BonusActionPoints;
		uint32_t Experience;
		uint32_t Reputation;
		bool Flanked;
		uint8_t _Pad1[3];
		uint32_t Karma;
		uint8_t Flags;
		uint8_t _Pad2[3];
		uint32_t Unkn0;
		ObjectSet<int> TraitOrder;
		uint32_t Unkn1[2];
		struct EsvCharacter * Character;
		uint32_t Unkn2;
		uint32_t IsIncapacitatedRefCount;
		CharacterStat ** DynamicStats;
		CharacterStat ** DynamicStatsEnd;
		uint64_t Unkn3[2];
		CharacterEquippedItem ** ItemStats;
		CharacterEquippedItem ** ItemStatsEnd;
		uint64_t Unkn4;
		ObjectSet<void *> SurfacePathInfluences;
		uint32_t ActiveBoostConditions[16];
		EoCGameRandom DamageRng;
		uint8_t _Pad4[3];
		EoCGameRandom CriticalHitRng;
		uint8_t _Pad5[3];
		uint32_t MaxVitality;
		uint32_t BoostedMaxVitality;
		uint32_t MaxArmor;
		uint32_t BoostedMaxArmor;
		uint32_t MaxMagicArmor;
		uint32_t BoostedMaxMagicArmor;
		uint32_t BoostedSight;
		uint32_t Sight;
		uint32_t Flags0;
		uint32_t Flags1;
		uint32_t Flags2;
		uint32_t Flags3;
		uint32_t Unkn5[2];
		bool SomeComputePendingFlag;
		uint8_t _Pad6[3];
		uint32_t MaxSummons;
		uint32_t BoostedMaxSummons;
		uint32_t MaxMpOverride;
		uint64_t DisabledTalents;
		uint64_t Unkn6;
	};

	struct RPGEnumeration
	{
		FixedString Name;
		FixedStringMapBase<int32_t> Values;
	};

	struct CRPGStats_Modifier
	{
		int32_t RPGEnumerationIndex;
		int32_t Unknown2;
		int32_t UnknownZero;
		uint32_t _Padding;
		FixedString Name;
	};

	template <class T>
	struct CNamedElementManager
	{
		void * VMT;
		void * PrimitiveSetVMT;
		PrimitiveSet<T *> Primitives;
		uint64_t Unknown;
		FixedStringMapBase<uint32_t> NameHashMap;
		uint32_t Unused;
		uint32_t NumItems;
		uint32_t NumSomeItems;

		int FindIndex(FixedString str) const
		{
			auto ptr = NameHashMap.Find(str.Str);
			if (ptr != nullptr) {
				return (int)*ptr;
			}
			else {
				return -1;
			}
		}

		T * Find(int index) const
		{
			if (index < 0 || index >= (int)Primitives.ItemCount) {
				return nullptr;
			}
			else {
				return Primitives.Buf[index];
			}
		}

		T * Find(FixedString str) const
		{
			auto ptr = NameHashMap.Find(str.Str);
			if (ptr != nullptr) {
				return Primitives.Buf[*ptr];
			}
			else {
				return nullptr;
			}
		}
	};

	struct ModifierList
	{
		CNamedElementManager<CRPGStats_Modifier> Attributes;
		FixedString Name;

		CRPGStats_Modifier * GetAttributeInfo(const char * name, int * attributeIndex) const;
	};

	struct CRPGStatsManager
	{
		CNamedElementManager<RPGEnumeration> modifierValueList;
		CNamedElementManager<ModifierList> modifierList;
		CNamedElementManager<CRPGStats_Object> objects;
		CNamedElementManager<uint64_t> levelMods;
		CNamedElementManager<uint64_t> deltaMods;
		CNamedElementManager<uint64_t> treasureSubtables;
		CNamedElementManager<uint64_t> treasureTables;
		CNamedElementManager<uint64_t> itemTypes;
		uint64_t unknown[47];
		PrimitiveSet<FixedString> ModifierFSSet;
		uint64_t unknown2[165];

		ModifierList * GetTypeInfo(CRPGStats_Object * object);
		RPGEnumeration * GetAttributeInfo(CRPGStats_Object * object, const char * attributeName, int & attributeIndex);
		std::optional<FixedString> GetAttributeFixedString(CRPGStats_Object * object, const char * attributeName);
		std::optional<int> GetAttributeInt(CRPGStats_Object * object, const char * attributeName);
		bool SetAttributeString(CRPGStats_Object * object, const char * attributeName, const char * value);
		bool SetAttributeInt(CRPGStats_Object * object, const char * attributeName, int32_t value);
		bool ObjectExists(FixedString statsId, FixedString type);
	};

	struct NetworkObjectFactory : public ObjectFactory
	{
		FixedStringMapBase<void *> CharacterMap;
		uint32_t _Pad;
		uint32_t Unkn4;
		uint32_t _Pad2;
		uint64_t Unkn5;
		uint32_t Unkn6;
		uint32_t _Pad3;
		uint64_t Unkn7[7];
		Array<unsigned short> ShortArray;
		uint64_t Unkn8;
	};

	struct ComponentEntry
	{
		// todo
		Component * component;
		uint64_t dummy[31];
	};

	struct EntityWorld
	{
		uint64_t Unkn[17];
		Array<ComponentEntry> Components;
	};

	struct CharacterFactory : public NetworkObjectFactory
	{
		void * VMT2;
		void * VMT3;
		FixedStringMapBase<void *> FSMap_ReloadComponent;
		uint32_t _Pad4;
		EntityWorld * Entities;
		uint64_t Unkn8[2];
	};

	struct ItemFactory : public NetworkObjectFactory
	{
		void * VMT2;
		void * VMT3;
		FixedStringMapBase<void *> FSMap_ReloadComponent;
		uint32_t _Pad4;
		EntityWorld * Entities;
		uint64_t Unkn8[2];
	};

	struct EsvStatusVMT
	{
		void * Destroy;
		void * SetObjectHandle;
		void * GetObjectHandle;
		void * GetStatusId;
		void * GetTriggerBehavior_M;
		void * AddStatsData2_Maybe;
		void * GetStatsIdByIndex;
		void * VMT38;
		void * VMT40;
		void * VMT48;
		void * CanEnter;
		void * Init;
		void * Enter;
		void * Resume;
		void * Update;
		void * Tick;
		void * Exit;
		void * VMT88;
		void * ConsumeStatsId;
		void * VMT98;
		void * IsImmobilizingStatus;
		void * VMTA8;
		void * VMTB0;
		void * GetSyncData;
		void * VMTC0;
		void * Serialize;
		void * VMTD0;
		void * CreateVisuals;
		void * DestroyVisuals;
		void * SetHostileFlagFromSavingThrow_M;
		void * GetEnterChance;
		void * AddStatsData_Maybe;
	};

	struct EsvStatus
	{
		virtual ~EsvStatus() = 0;
		virtual void SetObjectHandle(ObjectHandle Handle) = 0;
		virtual void GetObjectHandle(ObjectHandle * Handle) = 0;
		virtual uint32_t GetStatusId() = 0;
		// 3 - Toggle, 0 - Normal, 1 - ???, 2 - OnlyOnce?
		virtual uint32_t GetTriggerBehavior_M() = 0;
		virtual void AddStatsData2_Maybe() = 0;
		virtual void * GetStatsIdByIndex(int index) = 0;
		virtual void VMT38() = 0;
		virtual void VMT40() = 0;
		virtual void VMT48() = 0;
		virtual bool CanEnter() = 0;
		virtual void Init() = 0;
		virtual bool Enter() = 0;
		virtual bool Resume() = 0;
		virtual void Update(void * A, float Time_M) = 0;
		virtual void Tick(int * a2, float a3, float a4) = 0;
		virtual void Exit() = 0;
		virtual void VMT88() = 0;
		virtual void ConsumeStatsId() = 0;
		virtual void VMT98() = 0;
		virtual void IsImmobilizingStatus() = 0;
		virtual void VMTA8() = 0;
		virtual void VMTB0() = 0;
		virtual void GetSyncData() = 0;
		virtual void VMTC0() = 0;
		virtual void Serialize() = 0;
		virtual void VMTD0() = 0;
		virtual void CreateVisuals() = 0;
		virtual void DestroyVisuals() = 0;
		virtual void SetHostileFlagFromSavingThrow_M() = 0;
		virtual void GetEnterChance() = 0;
		virtual void AddStatsData_Maybe() = 0;

		enum Flags0
		{
			SF0_KeepAlive = 1,
			SF0_IsOnSourceSurface = 2,
			SF0_IsFromItem = 4,
			SF0_Channeled = 8,
			SF0_IsLifeTimeSet = 0x10,
			SF0_InitiateCombat = 0x20,
			SF0_Influence = 0x80
		};

		enum Flags1
		{
			SF1_BringIntoCombat = 1,
			SF1_IsHostileAct = 2,
			SF1_IsInvulnerable = 8,
			SF1_IsResistingDeath = 0x10
		};

		enum Flags2
		{
			SF2_ForceStatus = 1,
			SF2_ForceFailStatus = 2,
			SF2_RequestDelete = 0x20,
			SF2_RequestDeleteAtTurnEnd = 0x40,
			SF2_Started = 0x80
		};

		enum CauseType : uint8_t
		{
			CT_None = 0,
			CT_SurfaceMove = 1,
			CT_SurfaceCreate = 2,
			CT_SurfaceStatus = 3,
			CT_StatusEnter = 4,
			CT_StatusTick = 5,
			CT_Attack = 6,
			CT_Offhand = 7,
			CT_GM = 8
		};

		// void * VMT;
		FixedString FS1;
		uint32_t NetID;
		uint32_t _Pad0;
		uint64_t U1;
		FixedString StatusId;
		uint32_t CanEnterChance;
		float StartTimer;
		float LifeTime;
		float CurrentLifeTime;
		float TurnTimer;
		float Strength;
		float StatsMultiplier;
		CauseType DamageSourceType;
		uint8_t _Pad1[3];
		ObjectHandle StatusHandle;
		ObjectHandle TargetCIHandle;
		ObjectSet<ObjectHandle> StatusOwner;
		ObjectHandle StatusSourceHandle;
		ObjectHandle SomeHandle;
		uint8_t Flags2;
		uint8_t Flags0;
		uint8_t Flags1;
		uint8_t _Pad2;
		uint32_t _Pad3;
	};

	struct TDamagePair
	{
		uint32_t Amount;
		uint32_t DamageType;
	};

	enum DeathType : uint8_t
	{
		DET_None = 0,
		DET_Physical = 1,
		DET_Piercing = 2,
		DET_Arrow = 3,
		DET_DoT = 4,
		DET_Incinerate = 5,
		DET_Acid = 6,
		DET_Electrocution = 7,
		DET_FrozenShatter = 8,
		DET_PetrifiedShatter = 9,
		DET_Explode = 10,
		DET_Surrender = 11,
		DET_Hang = 12,
		DET_KnockedDown = 13,
		DET_Lifetime = 14,
		DET_Sulfur = 15,
		DET_Sentinel = 16
	};

	enum DamageType : uint32_t
	{
		DT_None = 0,
		DT_Physical = 1,
		DT_Piercing = 2,
		DT_Corrosive = 3,
		DT_Magic = 4,
		DT_Chaos = 5,
		DT_Fire = 6,
		DT_Air = 7,
		DT_Water = 8,
		DT_Earth = 9,
		DT_Poison = 10,
		DT_Shadow = 11,
		DT_Custom = 12
	};

	enum ItemSlot : uint8_t
	{
		IS_Helmet = 0,
		IS_Breast = 1,
		IS_Leggings = 2,
		IS_Weapon = 3,
		IS_Shield = 4,
		IS_Ring = 5,
		IS_Belt = 6,
		IS_Boots = 7,
		IS_Gloves = 8,
		IS_Amulet = 9,
		IS_Ring2 = 10,
		IS_Wings = 11,
		IS_Horns = 12,
		IS_Overhead = 13
	};

	struct HitDamageInfo
	{
		enum EffectFlag
		{
			EF_Hit = 1,
			EF_Blocked = 2,
			EF_Dodged = 4,
			EF_Missed = 8,
			EF_CriticalHit = 0x10,
			EF_AlwaysBackstab = 0x20,
			EF_FromSetHP = 0x40,
			EF_DontCreateBloodSurface = 0x80,
			EF_Reflection = 0x200,
			EF_NoDamageOnOwner = 0x400,
			EF_FromShacklesOfPain = 0x800,
			EF_DamagedMagicArmor = 0x1000,
			EF_DamagedPhysicalArmor = 0x2000,
			EF_DamagedVitality = 0x4000,
			EF_PropagatedFromOwner = 0x10000,
			EF_ProcWindWalker = 0x80000
		};

		uint32_t Equipment{ 0 };
		uint32_t TotalDamageDone{ 0 };
		uint32_t Unknown{ 0 };
		DeathType DeathType{ DET_Sentinel };
		uint8_t _Pad1[3];
		DamageType DamageType{ DT_None };
		uint32_t AttackDirection{ 0 };
		uint32_t ArmorAbsorption{ 0 };
		uint32_t LifeSteal{ 0 };
		uint32_t EffectFlags{ 0 };
		bool HitWithWeapon{ false };
		uint8_t _Pad2[3];
		Array<TDamagePair> DamageList;
	};

	struct EsvStatusHit : public EsvStatus
	{
		uint32_t Unk2;
		uint8_t Unk3;
		uint8_t _Pad4[3];
		void * RPGPropertyList;
		HitDamageInfo DamageInfo;
		ObjectHandle HitByHandle;
		ObjectHandle HitWithHandle;
		ObjectHandle WeaponHandle;
		// 0 - ASAttack
		// 1 - Character::ApplyDamage, StatusDying, ExecPropertyDamage, StatusDamage
		// 2 - AI hit test
		// 5 - InSurface
		// 6 - SetHP, osi::ApplyDamage, StatusConsume
		uint32_t HitReason;
		uint8_t _Pad5[4];
		FixedString SkillId;
		bool Interruption;
		bool AllowInterruptAction;
		bool SomeBool;
		uint8_t _Pad6[1];
		uint8_t PropertyContext;
		uint8_t _Pad7[3];
		Vector3 ImpactPosition;
		Vector3 ImpactOrigin;
		Vector3 ImpactDirection;
		uint32_t Unk4;
	};

	struct EsvStatusHeal : public EsvStatus
	{
		uint32_t EffectTime;
		uint32_t HealAmount;
		uint32_t HealEffect;
		uint8_t _Pad4[4];
		FixedString HealEffectId;
		uint32_t HealType;
		uint32_t AbsorbSurfaceRange;
		ObjectSet<void *> AbsorbSurfaceTypes;
		uint64_t Unkn2;
		bool TargetDependentHeal;
		uint8_t _Pad5[3];
		uint32_t TargetDependentValue[3];
		uint32_t TargetDependentHealAmount[3];
		uint32_t Unkn3;
	};

	struct EsvStatusManager
	{
		uint64_t U1[8];
		uint8_t U2[240];
		EsvStatus ** Statuses;
		uint32_t U3;
		uint32_t StatusCount;
		uint64_t U4[4];
	};

	struct EsvSkillConditions
	{
		int32_t MinimumHealthPercentage;
		int32_t MaximumHealthPercentage;
		bool HasNoPhysicalArmor;
		bool HasNoMagicalArmor;
		uint8_t _Pad[6];
		ObjectSet<FixedString> Tags;
	};

	struct EsvSkillInfo
	{
		float ScoreModifier;
		int32_t StartRound;
		int32_t MinimumImpact;
		bool OnlyCastOnSelf;
		uint8_t AIFlags; // Enum
		uint8_t _Pad[2];
		EsvSkillConditions SourceConditions;
		EsvSkillConditions TargetConditions;
		bool CasualExplorer;
		bool Classic;
		bool TacticianHardcore;
		bool HonorHardcore;
		uint32_t Unknown;
	};

	struct EsvSkill
	{
		void * VMT;
		FixedString UnknownFS;
		uint32_t NetID;
		uint8_t _Pad[4];
		EsvSkillInfo Info;
		ObjectSet<ObjectHandle> CauseList;
		ObjectHandle UnknownHandle;
		uint32_t Unknown1;
		uint8_t _Pad2[4];
		ObjectHandle OwnerHandle;
		FixedString SkillId;
		float ActiveCooldown;
		bool IsActivated;
		bool IsLearned;
		bool ZeroMemory;
		bool OncePerCombat;
		bool Unknown2;
		uint8_t _Pad3[3];
		uint32_t NumCharges;
		uint8_t _Pad4[4];
		uint64_t Unknown3;
	};

	struct EsvSkillManager
	{
		void * FreeSkillState;
		ObjectHandle OwnerHandle;
		FixedStringMapBase<EsvSkill *> Skills;
		uint8_t _Pad[4];
		FixedStringRefMap<uint32_t> TimeItemAddedToSkillManager;
		bool IsLoading;
		uint8_t _Pad2[3];
		uint32_t SomeCount;
	};

	enum EsvCharacterFlags : uint64_t
	{
		kHostControl = 0x08,
		kOffStage = 0x20,
		kCannotBePossessed = 0x80
	};

	enum EsvCharacterFlags2 : uint8_t
	{
		kGlobal = 0x01,
		kHasOsirisDialog = 0x02,
		kHasDefaultDialog = 0x04,
		kTreasureGeneratedForTrader = 0x10,
		kResurrected = 0x20
	};

	enum EsvCharacterFlags3 : uint8_t
	{
		kIsPet = 0x01,
		kIsSpectating = 0x02,
		kNoReptuationEffects = 0x04,
		kHasWalkSpeedOverride = 0x08,
		kHasRunSpeedOverride = 0x10,
		kIsGameMaster = 0x20,
		kIsPossessed = 0x40
	};

	struct EsvSkillBarItem
	{
		enum ItemType : uint32_t
		{
			kNone = 0,
			kSkill = 1,
			kItem = 2
		};

		ItemType Type;
		uint32_t _Pad;
		FixedString SkillOrStatId;
		ObjectHandle ItemHandle;
	};

	struct EsvPlayerCustomData
	{
		void * VMT;
		bool Initialized;
		bool CustomLookEnabled;
		uint8_t _Pad[6];
		STDWString Name;
		TranslatedString NameTranslated;
		uint64_t Unkn1[18];
		FixedString ClassType;
		uint32_t SkinColor;
		uint32_t HairColor;
		uint32_t ClothColor1;
		uint32_t ClothColor2;
		uint32_t ClothColor3;
		bool IsMale;
		uint8_t _Pad2[3];
		FixedString Race;
		FixedString OriginName;
		FixedString Icon;
		FixedString MusicInstrument;
		FixedString OwnerProfileID;
		FixedString ReservedProfileID;
		FixedString AiPersonality;
		FixedString Speaker;
		void * CustomIconImg;
	};

	struct EsvPlayerData
	{
		ObjectHandle SomeObjectHandle;
		ObjectSet<EsvSkillBarItem> SkillBar;
		ObjectSet<uint32_t> LockedAbility;
		FixedStringMapBase<void *> ShapeShiftVariableManagers;
		uint8_t _Pad1[4];
		FixedStringMapBase<void *> ShapeShiftAttitudeMaps;
		uint8_t _Pad2[4];
		bool LevelUpMarker;
		uint8_t SelectedSkillSetIndex;
		uint8_t _Pad3[6];
		FixedString QuestSelected;
		EsvPlayerCustomData CustomData;
		uint64_t Unkn1[3];
		void * PreviousPickpocketTargets;
		ObjectHandle SomeObjectHandle2;
		ObjectSet<glm::vec3> PreviousPositions;
		uint32_t PreviousPositionId;
		bool HelmetOption;
		bool Dirty;
		uint8_t _Pad4[2];
		uint32_t Renown;
		uint8_t CachedTension;
		uint8_t _Pad5[3];
		ObjectHandle SomeObjectHandle3;
		uint8_t HomesteadKeyState;
		uint8_t _Pad6[7];
		ObjectHandle RecruiterHandle;
		FixedString OriginalTemplate;
		FixedString Region;
	};

	struct EocPlayerUpgrade
	{
		CDivinityStats_Character * Stats;
		uint32_t AttributePoints;
		uint32_t CombatAbilityPoints;
		uint32_t CivilAbilityPoints;
		uint32_t TalentPoints;
		uint64_t Unknown;
		ObjectSet<int> Attributes;
		ObjectSet<int> Abilities;
		uint32_t Talents[4];
		ObjectSet<uint16_t> Traits;
		bool IsCustom;
	};

	struct EsvCharacter
	{
		virtual ~EsvCharacter() = 0;
		virtual void VMT08() = 0;
		virtual uint64_t Ret5() = 0;
		virtual void SetObjectHandle(ObjectHandle Handle) = 0;
		virtual void GetObjectHandle(ObjectHandle * Handle) = 0;
		virtual void SetGuid(FixedString const & fs) = 0;
		virtual FixedString * GetGuid() = 0;
		virtual void SetNetID(uint32_t netId) = 0;
		virtual void GetNetID(uint32_t & netId) = 0;
		virtual void SetCurrentTemplate() = 0;
		virtual void GetCurrentTemplate() = 0;
		virtual void SetGlobal() = 0;
		virtual void GetGlobal() = 0;
		virtual void GetComponentType() = 0;
		virtual void GetEntityObjectByHandle() = 0;
		virtual void GetName() = 0;
		virtual void SetFlags(uint64_t flag) = 0;
		virtual void ClearFlags(uint64_t flag) = 0;
		virtual void HasFlag() = 0;
		virtual void SetAiColliding() = 0;
		virtual void GetTags() = 0;
		virtual void IsTagged() = 0;
		virtual Vector3 const * GetTranslate() = 0;
		virtual void GetRotation() = 0;
		virtual float GetScale() = 0;
		virtual void SetTranslate(Vector3 const & translate) = 0;
		virtual void SetRotation() = 0;
		virtual void SetScale(float scale) = 0;
		virtual void GetVelocity() = 0;
		virtual void SetVelocity(Vector3 const & translate) = 0;
		virtual void LoadVisual() = 0;
		virtual void UnloadVisual() = 0;
		virtual void ReloadVisual() = 0;
		virtual void GetVisual() = 0;
		virtual void GetPhysics() = 0;
		virtual void SetPhysics() = 0;
		virtual void LoadPhysics() = 0;
		virtual void UnloadPhysics() = 0;
		virtual void ReloadPhysics() = 0;
		virtual void GetHeight() = 0;
		virtual void GetParentUUID() = 0;
		virtual FixedString * GetCurrentLevel() = 0;
		virtual void SetCurrentLevel(FixedString const & level) = 0;
		virtual void AddPeer() = 0;
		virtual void UNK1() = 0;
		virtual void UNK2() = 0;
		virtual void UNK3() = 0;
		virtual void GetAi() = 0;
		virtual void LoadAi() = 0;
		virtual void UnloadAi() = 0;
		virtual void GetDisplayName() = 0;
		virtual void SavegameVisit() = 0;
		virtual void GetEntityNetworkId() = 0;
		virtual void SetTemplate() = 0;
		virtual void SetOriginalTemplate_M() = 0;

		EsvStatus * GetStatusByHandle(ObjectHandle handle) const;

		BaseComponent Base;
		FixedString MyGuid;
		uint32_t NetID;
		uint32_t _Pad1;
		glm::vec3 WorldPos;
		uint32_t _Pad2;
		EsvCharacterFlags Flags;
		uint32_t U2;
		uint32_t _Pad3;
		void * CurrentLevel;
		glm::mat3 WorldRot;
		float Scale;
		PrimitiveSet<void *> PeerIDClassNames;
		uint64_t U3[2];
		void * CurrentTemplate;
		void * OriginalTemplate;
		void * TemplateUsedForSkills;
		EsvCharacterFlags2 Flags2;
		EsvCharacterFlags3 Flags3;
		uint8_t FlagsEx;
		uint8_t Team;
		uint8_t Color;
		uint8_t _Pad4[3];
		uint64_t U4[7];
		void * AnimationOverrideFS;
		uint32_t WalkSpeedOverride;
		uint32_t RunSpeedOverride;
		ObjectSet<FixedString> VoiceSet;
		uint8_t NeedsUpdateCount;
		uint8_t ScriptForceUpdateCount;
		uint8_t ForceSynchCount;
		bool U5;
		uint8_t _Pad5[4];
		CDivinityStats_Character * Stats;
		ObjectHandle InventoryHandle;
		uint64_t U6[2];
		void * SteeringMachine;
		void * BehaviourMachine;
		uint64_t U7[2];
		void * OsirisController;
		uint64_t U8[5];
		void * TaskController;
		EsvStatusManager * StatusManager;
		EsvSkillManager * SkillManager;
		void * VariableManager;
		void * RaceVariableManager_M;
		void * Attitudes;
		uint64_t U9[4];
		uint32_t Dialog;
		bool IsDialogAiControlled;
		uint8_t U10[3];
		float LifeTime;
		float TurnTimer;
		float TriggerTrapsTimer;
		uint32_t U11;
		uint64_t U12;
		ObjectHandle OwnerHandle;
		ObjectHandle FollowCharacterHandle;
		ObjectHandle EnemyCharacterHandle;
		ObjectHandle SpiritCharacterHandle;
		ObjectHandle CorpseCharacterHandle;
		ObjectHandle ObjectHandle6;
		ObjectSet<ObjectHandle> EnemyHandles;
		ObjectSet<void *> SurfacePathInfluenceSet; // Set<eoc::SurfacePAthInfluence>
		ObjectSet<ObjectHandle> SummonHandles;
		void * PlanManager;
		uint32_t PartialAP;
		uint32_t _Pad6;
		void * StatusManagerDirty_M;
		ObjectSet<ObjectHandle> ObjectHandleSet3;
		ObjectSet<FixedString> RegisteredTriggers;
		EsvPlayerData * PlayerData;
		EocPlayerUpgrade PlayerUpgrade;
		uint8_t _Pad61[7];
		uint64_t U13[2];
		void * CustomDisplayName;
		void * StoryDisplayName;
		void * OriginalTransformDisplayName;
		uint64_t U14[20];
		uint32_t MaxVitalityPatchCheck;
		uint32_t MaxArmorPatchCheck;
		uint32_t MaxMagicArmorPatchCheck;
		uint32_t _Pad7;
		void * AnimationSetOverride;
		ObjectHandle PartyHandle;
		ObjectSet<FixedString> CreatedTemplateItems;
		void * Treasures;
		Set<ObjectHandle> CustomTradeTreasure;
		uint64_t U141;
		void * Target;
		uint64_t U15[3];
		ObjectHandle CrimeHandle;
		ObjectHandle PreviousCrimeHandle;
		uint32_t CrimeState;
		uint32_t PreviousCrimeState;
		bool IsAlarmed;
		bool CrimeWarningsEnabled;
		bool CrimeInterrogationEnabled;
		bool _Pad8;
		uint32_t InvestigationTimer;
		void * DisabledCrime;
		uint64_t U16[3];
		uint64_t DamageCounter;
		uint64_t HealCounter;
		uint64_t KillCounter;
		uint64_t U17;
		uint64_t Archetype;
		uint64_t EquipmentColor;
		uint64_t ProjectileTemplate;
		uint64_t TimeElapsed;
		uint64_t PreferredAiTarget;
		uint64_t U18[10];
		void * VisualSetIndices;
		bool ReadyCheckBlocked;
		bool CorpseLootable;
		uint8_t NumConsumables;
		uint8_t _Pad9[5];
		void * PreviousLevel;
	};

	struct EsvItem
	{
		virtual ~EsvItem() = 0;
		virtual void HandleTextKeyEvent() = 0;
		virtual uint64_t Ret5() = 0;
		virtual void SetObjectHandle(ObjectHandle Handle) = 0;
		virtual void GetObjectHandle(ObjectHandle * Handle) = 0;
		virtual void SetGuid(FixedString const & fs) = 0;
		virtual FixedString * GetGuid() = 0;
		virtual void SetNetID(uint32_t netId) = 0;
		virtual void GetNetID(uint32_t & netId) = 0;
		virtual void SetCurrentTemplate() = 0;
		virtual void GetCurrentTemplate() = 0;
		virtual void SetGlobal() = 0;
		virtual void GetGlobal() = 0;
		virtual void GetComponentType() = 0;
		virtual void GetEntityObjectByHandle() = 0;
		virtual void GetName() = 0;
		virtual void SetFlags(uint64_t flag) = 0;
		virtual void ClearFlags(uint64_t flag) = 0;
		virtual void HasFlag() = 0;
		virtual void SetAiColliding() = 0;
		virtual void GetTags() = 0;
		virtual void IsTagged() = 0;
		virtual Vector3 const * GetTranslate() = 0;
		virtual void GetRotation() = 0;
		virtual float GetScale() = 0;
		virtual void SetTranslate(Vector3 const & translate) = 0;
		virtual void SetRotation() = 0;
		virtual void SetScale(float scale) = 0;
		virtual void GetVelocity() = 0;
		virtual void SetVelocity(Vector3 const & translate) = 0;
		virtual void LoadVisual() = 0;
		virtual void UnloadVisual() = 0;
		virtual void ReloadVisual() = 0;
		virtual void GetVisual() = 0;
		virtual void GetPhysics() = 0;
		virtual void SetPhysics() = 0;
		virtual void LoadPhysics() = 0;
		virtual void UnloadPhysics() = 0;
		virtual void ReloadPhysics() = 0;
		virtual void GetHeight() = 0;
		virtual void GetParentUUID() = 0;
		virtual FixedString * GetCurrentLevel() = 0;
		virtual void SetCurrentLevel(FixedString const & level) = 0;
		virtual void AddPeer() = 0;
		virtual void UNK1() = 0;
		virtual void UNK2() = 0;
		virtual void UNK3() = 0;
		virtual void GetAi() = 0;
		virtual void LoadAi() = 0;
		virtual void UnloadAi() = 0;
		virtual void GetDisplayName() = 0;
		virtual void SavegameVisit() = 0;
		virtual void GetEntityNetworkId() = 0;
		virtual void SetTemplate() = 0;
		virtual void SetOriginalTemplate_M() = 0;

		BaseComponent Base;
		FixedString MyGuid;
		uint32_t NetID;
		uint32_t _Pad1;
		glm::vec3 WorldPos;
		uint32_t _Pad2;
		uint64_t Flags2;
		uint32_t U2;
		uint32_t _Pad3;
		void * CurrentLevel;
		glm::mat3 WorldRot;
		float Scale;
		uint8_t Flags3;
		uint8_t _Pad4[7];
		uint64_t U3[4];
		glm::vec3 WorldVelocity;
		uint32_t _Pad5;
		uint64_t U4;
		FixedString CurrentTemplate;
		uint64_t OriginalTemplateType;
		STDWString CustomDisplayName;
		STDWString CustomDescription;
		STDWString CustomBookContent;
		FixedString StatsId;
		CDivinityStats_Item * StatsDynamic;
		CRPGStats_Object * StatsFromName;
		void * Generation;
		ObjectHandle InventoryHandle;
		void * Parent;
		uint16_t Slot;
		uint16_t _Pad6;
		uint32_t Amount;
		uint32_t Vitality;
		uint32_t Armor;
		ObjectHandle InUseByCharacterHandle;
		uint64_t U5[2];
		uint32_t LockLevel;
		uint32_t _Pad7;
		void * ItemMachine;
		void * PlanMachine;
		void * VariableManager;
		EsvStatusManager * StatusMachine;
		void * U6;
		ObjectHandle OwnerHandle;
		ObjectHandle OriginalOwnerCharacter;
		void * Sockets;
		uint64_t U7;
		uint32_t ComputedVitality;
		uint32_t Durability;
		FixedString ItemType;
		uint32_t GoldValueOverwrite;
		uint32_t WeightValueOverwrite;
		uint64_t U8;
		void * Tags;
		void * DynamicTags;
		uint32_t U9;
		uint32_t HasDynamicTags;
		uint64_t U10;
		uint64_t TeleportTargetOverride;
		uint32_t TreasureLevel;
		uint32_t LevelOverride;
		bool ForceSynch;
		uint8_t _Pad8[3];
		uint32_t TeleportUseCount;
		uint64_t PreviousLevel;
	};

	struct ShootProjectileHelper
	{
		FixedString SkillId;
		ObjectHandle SourceCharacter;
		ObjectHandle Target;
		ObjectHandle Target2;
		glm::vec3 StartPosition;
		glm::vec3 EndPosition;
		uint8_t Random;
		uint8_t _Pad[7];
		void * DamageList;
		int32_t CasterLevel;
		uint32_t _Pad2;
		void * CollisionInfo;
		bool IsTrap;
		bool UnknownFlag1;
		uint8_t _Pad3[6];
		FixedString FS2;
		float StatusClearChance;
		bool HasCaster;
		bool IsStealthed;
		bool UnknownFlag2;
	};

	struct EsvGameAction
	{
		enum ActionType
		{
			RainAction = 1,
			StormAction = 2,
			WallAction = 4,
			TornadoAction = 6,
			PathAction = 7,
			GameObjectMoveAction = 8,
			StatusDomeAction = 9
		};

		void * VMT;
		FixedString SomeFS;
		uint64_t NetID;
		PrimitiveSet<uint16_t> PeerIDClassNames;
		uint64_t _Unk[2];
		ObjectHandle MyHandle;
		uint32_t GameActionType;
		bool Active;
		bool Dirty;
		uint8_t _Pad1[2];
		float ActivateTimer;
		uint32_t _Pad2;
	};

	struct EsvGameActionManager
	{
		uint8_t Unmapped[0x130];
		Set<EsvGameAction *> GameActions;
	};

	struct EsvTornadoAction : public EsvGameAction
	{
		FixedString SkillId;
		ObjectHandle OwnerHandle;
		glm::vec3 Position;
		glm::vec3 Target;
		float TurnTimer;
		bool Finished;
		bool IsFromItem;
		uint8_t _Pad3[2];
		float HitRadius;
		uint32_t _Pad4;
		uint64_t _Unk2;
		ObjectSet<Vector3> AnchorList;
		uint64_t Anchor;
		float Interpolation;
		uint32_t _Unk3;
		ObjectHandle SurfaceActionHandle;
		ObjectSet<ObjectHandle> HitCharacterHandles;
		ObjectSet<ObjectHandle> HitItemHandles;
		FixedString CleanseStatuses;
		float StatusClearChance;
	};

	struct EsvStormAction : public EsvGameAction
	{
		ObjectHandle OwnerHandle;
		glm::vec3 Position;
		float LifeTime;
		FixedString SkillId;
		float TurnTimer;
		float StrikeTimer;
		bool Finished;
		bool IsFromItem;
		uint8_t _Pad3[6];
		uint64_t Unkn[3 * 5];
		ObjectSet<FixedString> FSSet;
		ObjectSet<void *> ProjectileTargetDescSet;
		ObjectSet<void *> StrikeSet;
	};

	struct EsvRainAction : public EsvGameAction
	{
		ObjectHandle OwnerHandle;
		glm::vec3 Position;
		float AreaRadius;
		float LifeTime;
		float Duration;
		bool FirstTick;
		uint8_t _Pad3[7];
		FixedString SkillId;
		float ConsequencesStartTime;
		float TurnTimer;
		bool Finished;
		bool IsFromItem;
		uint8_t _Pad4[2];
		FixedString SkillProperties;
	};

	struct EsvWallAction : public EsvGameAction
	{
		FixedString SkillId;
		ObjectHandle OwnerHandle;
		glm::vec3 Target;
		glm::vec3 Source;
		float LifeTime;
		uint8_t _Pad3[4];
		ObjectSet<void *> Walls;
		float TurnTimer;
		bool Finished;
		bool IsFromItem;
		uint8_t _Pad4[2];
		uint64_t Unk1;
		uint64_t Unk2;
		uint32_t Unk3;
		uint32_t Unk4;
	};

	struct EsvStatusDomeAction : public EsvGameAction
	{
		ObjectHandle OwnerHandle;
		glm::vec3 Position;
		uint8_t _Pad3[4];
		float LifeTime;
		uint8_t _Pad4[4];
		FixedString SkillId;
		bool Finished;
		uint8_t _Pad5[7];
		void * SkillStatusAura;
	};

	struct EsvGameObjectMoveAction : public EsvGameAction
	{
		void * PathMover;
		ObjectHandle ObjectToMove;
		bool DoneMoving;
		uint8_t _Pad3[3];
		uint32_t U3[2];
		uint8_t _Pad4[4];
		ObjectHandle CasterCharacterHandle;
		FixedString BeamEffectName;
		ObjectHandle SomeHandle;
		uint64_t _U4[8];
	};

	struct SummonHelperResults
	{
		ObjectHandle SummonHandle;
		uint32_t Unknown;
	};

	struct SummonHelperSummonArgs
	{
		ObjectHandle OwnerCharacterHandle;
		FixedString GameObjectTemplateFS;
		FixedString Level;
		glm::vec3 Position;
		uint32_t SummonLevel;
		float Lifetime;
		bool IsTotem;
		bool MapToAiGrid;
	};
#pragma pack(pop)

}