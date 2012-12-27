/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Instance_Ulduar
SD%Complete:
SDComment:
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

instance_ulduar::instance_ulduar(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_ulduar::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

    for (uint8 i = 0; i < MAX_SPECIAL_ACHIEV_CRITS; ++i)
        m_abAchievCriteria[i] = false;
}

bool instance_ulduar::IsEncounterInProgress() const
{
    for (uint8 i = 0; i < MAX_BOSS_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            return true;
    }

    return false;
}

void instance_ulduar::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_WARD_OF_LIFE:
            for (uint8 i = urand(3, 5); i > 0; --i)
                pCreature->SummonCreature(NPC_WRITHING_LASHER, pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 3000);
            // not break
        case NPC_WRITHING_LASHER:
            pCreature->SetInCombatWithZone();
            return;
        case NPC_KEEPER_OF_NORGANNON:
        case NPC_BRANN_BRONZEBEARD:
            if (GetData(TYPE_LEVIATHAN_DIFFICULTY) != NONE_DIFFICULTY)
                pCreature->SetVisibility(VISIBILITY_OFF);
            break;
        case NPC_LEVIATHAN:
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            break;
        case NPC_IGNIS:
            break;
        case NPC_IRON_CONSTRUCT:
            m_lIronConstructsGuids.push_back(pCreature->GetObjectGuid());
            return;
        case NPC_RAZORSCALE:
        case NPC_COMMANDER:
        case NPC_XT002:
            break;
        case NPC_XT_TOY_PILE:
            m_lXtToyPileGuids.push_back(pCreature->GetObjectGuid());
            return;
        // Assembly of Iron
        case NPC_STEELBREAKER:
        case NPC_RUNEMASTER_MOLGEIM:
        case NPC_STORMCALLER_BRUNDIR:
            break;
        // Kologarn
        case NPC_KOLOGARN:
            if (GetData(TYPE_KOLOGARN) == DONE)
                pCreature->SummonCreature(NPC_KOLOGARN_BRIDGE_DUMMY, pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ(), pCreature->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0);
        case NPC_KOLOGARN_BRIDGE_DUMMY:
        // Auriaya
        case NPC_AURIAYA:
        case NPC_FERAL_DEFENDER:
        // Mimiron
        case NPC_AERIAL_UNIT:
        case NPC_VX001:
        case NPC_MIMIRON:
        case NPC_LEVIATHAN_MK:
        // Hodir
        case NPC_HODIR:
        case NPC_HELPER_DRUID:
        case NPC_HELPER_MAGE:
        case NPC_HELPER_SHAMAN:
        case NPC_HELPER_PRIEST:
        //Thorim
        case NPC_THORIM:
        case NPC_RUNIC_COLOSSUS:
            break;
        case NPC_THUNDER_ORB:
        {
            if (pCreature->GetPositionZ() > 425.0f)
            {
                m_lUpperOrbs.push_back(pCreature->GetObjectGuid());
            }
            else
            {
                m_lLowerOrbs.push_back(pCreature->GetObjectGuid());
            }
            return;
        }
        case NPC_RIGHT_HAND_TRIGGER:
        case NPC_LEFT_HAND_TRIGGER:
            SortHandTrigger(pCreature);
            return;
        case NPC_RUNE_GIANT:
        case NPC_JORMUNGAR_BEHEMOTH:
        case NPC_FREYA:
        case NPC_BRIGHTLEAF:
        case NPC_IRONBRACH:
        case NPC_STONEBARK:
        case NPC_VEZAX:
        case NPC_ANIMUS:
        case NPC_YOGGSARON:
        case NPC_SARA:
        case NPC_YOGG_BRAIN:
        case NPC_ALGALON:
            break;
        case NPC_OMINOUS_CLOUD:
            m_lCloudGuids.push_back(pCreature->GetObjectGuid());
            return;
        case NPC_SANCTUM_SENTRY:
            m_lSanctumSentryGuids.push_back(pCreature->GetObjectGuid());
            return;

        // used to handle the keepers images
        // set to invisible by default and only made visible if the encounter is done
        case HODIR_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if (m_auiEncounter[TYPE_HODIR] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            break;
        case FREYA_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if (m_auiEncounter[TYPE_FREYA] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            break;
        case THORIM_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if (m_auiEncounter[TYPE_THORIM] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            break;
        case MIMIRON_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if (m_auiEncounter[TYPE_MIMIRON] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            break;
        default:
            return;
    }
    m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
}

void instance_ulduar::OnPlayerEnterArea(Player* pPlayer, uint32 uiNewAreaId, uint32 uiOldAreaId)
{
    switch(uiNewAreaId)
    {
        case 4273:
        {
            // Prevent use vehicle for kill all bosses
            VehicleKitPtr vehicleKit = pPlayer->GetVehicle();
            if (vehicleKit)
            {
                pPlayer->ExitVehicle();
                Creature* pCreature = (Creature*)vehicleKit->GetBase();
                if (pCreature)
                    pCreature->ForcedDespawn();
            }
            break;
        }
        default:
            break;
    }
}

void instance_ulduar::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        // Repair
        case RX_214_REPAIR:
            pGo->SummonGameobject(RX_214_REPAIR_TRAP, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), 0, 0);
            return;
        // Towers
        case GO_TOWER_OF_FROST:
        case GO_TOWER_OF_FLAME:
        case GO_TOWER_OF_LIFE:
        case GO_TOWER_OF_STORMS:
            break;
        // doors & other
        // The siege
        case GO_SHIELD_WALL:
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_LEVIATHAN_GATE:
            if (GetData(TYPE_LEVIATHAN) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
            break;
        case GO_XT002_GATE:
            if (GetData(TYPE_IGNIS) == DONE && GetData(TYPE_RAZORSCALE) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            else
                pGo->SetGoState(GO_STATE_READY);
            break;
        case GO_BROKEN_HARPOON:
            m_lBrokenHarpoonGUID.push_back(pGo->GetObjectGuid());
            pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            return;

            // Archivum
        case GO_IRON_ENTRANCE_DOOR:
            break;
        case GO_ARCHIVUM_DOOR:
            if (GetData(TYPE_ASSEMBLY) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            else
                pGo->SetGoState(GO_STATE_READY);
            break;
        case GO_ARCHIVUM_CONSOLE:
        case GO_UNIVERSE_FLOOR_ARCHIVUM:
            // Celestial Planetarium
        case GO_CELESTIAL_ACCES:
        case GO_CELESTIAL_DOOR:
        case GO_UNIVERSE_FLOOR_CELESTIAL:
        case GO_AZEROTH_GLOBE:
            break;
            // Shattered Hallway
        case GO_KOLOGARN_BRIDGE:
            if (GetData(TYPE_KOLOGARN) == DONE)
                pGo->SetGoState(GO_STATE_READY);
            else
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_SHATTERED_DOOR:
            break;
            // The keepers
            // Hodir
        case GO_HODIR_EXIT:
            if (m_auiEncounter[TYPE_HODIR] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_HODIR_ICE_WALL:
            if (m_auiEncounter[TYPE_HODIR] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_HODIR_ENTER:
            pGo->SetGoState(GO_STATE_ACTIVE);
            break;
            // Mimiron
        case GO_MIMIRON_TRAM:
            if (m_auiEncounter[TYPE_AURIAYA] == DONE)
            {
                pGo->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                pGo->SetGoState(GO_STATE_READY);
            }
            break;
        case GO_MIMIRON_BUTTON:
            if (m_auiEncounter[TYPE_MIMIRON] == NOT_STARTED)
                pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
        case GO_MIMIRON_DOOR_1:
        case GO_MIMIRON_DOOR_2:
        case GO_MIMIRON_DOOR_3:
        case GO_MIMIRON_ELEVATOR:
        case GO_MIMIRON_TEL1:
        case GO_MIMIRON_TEL2:
        case GO_MIMIRON_TEL3:
        case GO_MIMIRON_TEL4:
        case GO_MIMIRON_TEL5:
        case GO_MIMIRON_TEL6:
        case GO_MIMIRON_TEL7:
        case GO_MIMIRON_TEL8:
        case GO_MIMIRON_TEL9:
            // Thorim
        case GO_DARK_IRON_PORTCULIS:
        case GO_RUNED_STONE_DOOR:
        case GO_THORIM_STONE_DOOR:
        case GO_LIGHTNING_FIELD:
            break;
        case GO_DOOR_LEVER:
            pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;

            // Prison
        case GO_ANCIENT_GATE:
            DoOpenMadnessDoorIfCan();
            break;
        case GO_VEZAX_GATE:
            pGo->SetGoState(GO_STATE_READY);
            if (m_auiEncounter[TYPE_VEZAX])
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_YOGG_GATE:
        case GO_BRAIN_DOOR1:
        case GO_BRAIN_DOOR2:
        case GO_BRAIN_DOOR3:
            // loot
            // Kologarn
        case GO_CACHE_OF_LIVING_STONE:
        case GO_CACHE_OF_LIVING_STONE_H:

            // Hodir
        case GO_CACHE_OF_WINTER:
        case GO_CACHE_OF_RARE_WINTER:
        case GO_CACHE_OF_WINTER_H:
        case GO_CACHE_OF_RARE_WINTER_H:
            // Freya
        case GO_FREYA_GIFT:
        case GO_FREYA_GIFT_HARD:
        case GO_FREYA_GIFT_H:
        case GO_FREYA_GIFT_HARD_H:
            // Thorim
        case GO_CACHE_OF_STORMS:
        case GO_CACHE_OF_RARE_STORMS:
        case GO_CACHE_OF_STORMS_H:
        case GO_CACHE_OF_RARE_STORMS_H:
            // Mimiron
        case GO_CACHE_OF_INOV:
        case GO_CACHE_OF_INOV_HARD:
        case GO_CACHE_OF_INOV_H:
        case GO_CACHE_OF_INOV_HARD_H:
            // Alagon
        case GO_GIFT_OF_OBSERVER:
        case GO_GIFT_OF_OBSERVER_H:
            break;
        default:
            return;
    }
    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_ulduar::OnCreatureDeath(Creature* pCreature)
{
    if (GetData(TYPE_IGNIS) == IN_PROGRESS && pCreature->GetEntry() == NPC_IRON_CONSTRUCT)
    {
        if (m_bOneIsDeath)
        {
            SetSpecialAchievementCriteria(TYPE_ACHIEV_SHATTERED, true);
        }
        else
        {
            m_bOneIsDeath = true;
            m_uiShatterTimer = 5 * IN_MILLISECONDS;
        }
    }
    if (GetData(TYPE_AURIAYA) == IN_PROGRESS && pCreature->GetEntry() == NPC_SANCTUM_SENTRY)
    {
        SetSpecialAchievementCriteria(TYPE_ACHIEV_CRAZY_CAT_LADY, false);
    }
    if (GetData(TYPE_THORIM) == IN_PROGRESS // Thorim
        || pCreature->GetEntry() == NPC_JORMUNGAR_BEHEMOTH // Preadds
        || pCreature->GetEntry() == NPC_CAPTAIN_ALY               
        || pCreature->GetEntry() == NPC_CAPTAIN_HORDE
        || pCreature->GetEntry() == NPC_MERCENARY_ALY
        || pCreature->GetEntry() == NPC_MERCENARY_HORDE) 
    {
        m_lThorimMobsGuids.push_back(pCreature->GetObjectGuid());
    }
}

// functions to open or close some doors
void instance_ulduar::OpenDoor(uint32 uiEntry)
{
    if (!uiEntry)
        return;

    GameObject* pGo = GetSingleGameObjectFromStorage(uiEntry);

    if (pGo)
        pGo->SetGoState(GO_STATE_ACTIVE);
}

void instance_ulduar::CloseDoor(uint32 uiEntry)
{
    if (!uiEntry)
        return;

    GameObject* pGo = GetSingleGameObjectFromStorage(uiEntry);

    if (pGo)
        pGo->SetGoState(GO_STATE_READY);
}

// used in order to unlock the door to Vezax and make vezax attackable
void instance_ulduar::DoOpenMadnessDoorIfCan()
{
    if (m_auiEncounter[TYPE_MIMIRON] == DONE && m_auiEncounter[TYPE_HODIR] == DONE && m_auiEncounter[TYPE_THORIM] == DONE && m_auiEncounter[TYPE_FREYA] == DONE)
        OpenDoor(GO_ANCIENT_GATE);
}

void instance_ulduar::DoColossusExplosion(ExplosionSide explosionSide)
{
    m_explosionSide = explosionSide;
    m_uiExplosionRow = 0;
    m_uiExplosionTimer = 250;
}
void instance_ulduar::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_LEVIATHAN:
            if (uiData == IN_PROGRESS)
                CloseDoor(GO_SHIELD_WALL);
            else
                OpenDoor(GO_SHIELD_WALL);
            if (uiData == SPECIAL)
            {
                if (GameObject* pGo = GetSingleGameObjectFromStorage(GO_LEVIATHAN_GATE))
                    pGo->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
            }
            break;
        case TYPE_IGNIS:
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_SHATTERED, false);
                DoStartTimedAchievement(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, ACHIEV_START_IGNIS_ID);
            }
            // Add respawn and kill
            if (uiData == FAIL || uiData == IN_PROGRESS)
            {
                for (GuidList::iterator itr = m_lIronConstructsGuids.begin(); itr != m_lIronConstructsGuids.end(); ++itr)
                {
                    if (Creature* pAdd = instance->GetCreature(*itr))
                        if (!pAdd->isAlive())
                            pAdd->Respawn();
                }
            }
            if (uiData == DONE)
            {
                for (GuidList::iterator itr = m_lIronConstructsGuids.begin(); itr != m_lIronConstructsGuids.end(); ++itr)
                {
                    if (Creature* pAdd = instance->GetCreature(*itr))
                    {
                        if (pAdd->isAlive())
                            pAdd->DealDamage(pAdd, pAdd->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
                    }
                }
                if (GetData(TYPE_RAZORSCALE) == DONE)
                    OpenDoor(GO_XT002_GATE);
            }
            break;
        case TYPE_RAZORSCALE:
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_QUICK_SHAVE, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_IRON_DWARF_MEDIUM_RARE, false);
            }
            else if (uiData == DONE)
            {
                if (GetData(TYPE_IGNIS) == DONE)
                    OpenDoor(GO_XT002_GATE);
            }
            break;
        case TYPE_XT002:
            if (uiData == DONE || uiData == FAIL)
                OpenDoor(GO_XT002_GATE);
            else if (uiData == IN_PROGRESS)
            {
                CloseDoor(GO_XT002_GATE);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_NERF_ENGINEERING, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_HEARTBREAKER, false);
                DoStartTimedAchievement(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, ACHIEV_START_XT_002_ID);
            }
            break;
        case TYPE_ASSEMBLY:
            if (uiData == DONE)
            {
                OpenDoor(GO_IRON_ENTRANCE_DOOR);
                OpenDoor(GO_ARCHIVUM_DOOR);
                OpenDoor(GO_SHATTERED_DOOR);
            }
            else if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_YOU_BRUNDIR, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_YOU_MOLGEIM, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_YOU_STEELBREAKER, true);
                CloseDoor(GO_IRON_ENTRANCE_DOOR);
            }
            else if (uiData == FAIL)
            {
                if (Creature* pBrundir = GetSingleCreatureFromStorage(NPC_STORMCALLER_BRUNDIR))
                {
                    if (!pBrundir->isAlive())
                        pBrundir->Respawn();
                }
                if (Creature* pMolgeim = GetSingleCreatureFromStorage(NPC_RUNEMASTER_MOLGEIM))
                {
                    if (!pMolgeim->isAlive())
                        pMolgeim->Respawn();
                }
                if (Creature* pSteelbreaker = GetSingleCreatureFromStorage(NPC_STEELBREAKER))
                {
                    if (!pSteelbreaker->isAlive())
                        pSteelbreaker->Respawn();
                }
                OpenDoor(GO_IRON_ENTRANCE_DOOR);
            }
            break;
        case TYPE_KOLOGARN:
            if (uiData == DONE)
            {
                // Summon loot box
                if (instance->IsRegularDifficulty())
                    DoRespawnGameObject(GO_CACHE_OF_LIVING_STONE, 30*MINUTE);
                else
                    DoRespawnGameObject(GO_CACHE_OF_LIVING_STONE_H, 30*MINUTE);

                if (GameObject* pGo = GetSingleGameObjectFromStorage(GO_KOLOGARN_BRIDGE))
                    pGo->SetGoState(GO_STATE_READY);
            }
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_DISARMED, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_OPEN_ARMS, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_IF_LOOKS_COULD_KILL, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_RUBBLE_AND_ROLL, false);
            }
            break;
        case TYPE_AURIAYA:
            if (uiData == DONE)
            {
                if (GameObject* pGO = GetSingleGameObjectFromStorage(GO_MIMIRON_TRAM))
                {
                    pGO->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                    pGO->SetGoState(GO_STATE_READY);
                }
            }
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_NINE_LIVES, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_CRAZY_CAT_LADY, true);
            }
            break;
            // Keepers
        case TYPE_MIMIRON:
            DoUseDoorOrButton(GO_MIMIRON_DOOR_1);
            DoUseDoorOrButton(GO_MIMIRON_DOOR_2);
            DoUseDoorOrButton(GO_MIMIRON_DOOR_3);
            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_MIMIRON_HARD] != DONE)
                {
                    if (instance->IsRegularDifficulty())
                    {
                        DoRespawnGameObject(GO_CACHE_OF_INOV, 30*MINUTE);
                    }
                    else
                    {
                        DoRespawnGameObject(GO_CACHE_OF_INOV_H, 30*MINUTE);
                    }
                }
                // used to make the friendly keeper visible
                if (Creature* pImage = GetSingleCreatureFromStorage(KEEPER_MIMIRON))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            if (uiData == IN_PROGRESS)
                SetSpecialAchievementCriteria(TYPE_ACHIEV_FIREFIGHTER, false);
            break;
        case TYPE_HODIR:
            if (uiData == DONE)
            {
                OpenDoor(GO_HODIR_ENTER);
                DoUseDoorOrButton(GO_HODIR_ICE_WALL);
                DoUseDoorOrButton(GO_HODIR_EXIT);
                if (instance->IsRegularDifficulty())
                {
                    DoRespawnGameObject(GO_CACHE_OF_WINTER, 30*MINUTE);
                }
                else
                {
                    DoRespawnGameObject(GO_CACHE_OF_WINTER_H, 30*MINUTE);
                }
                // used to make the friendly keeper visible
                if (Creature* pImage = GetSingleCreatureFromStorage(KEEPER_HODIR))
                    pImage->SetVisibility(VISIBILITY_ON);

                DoOpenMadnessDoorIfCan();
            }
            else if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_CHEESE_FREEZE, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_COOLEST_FRIEND, true);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_RARE_CACHE, true);
                CloseDoor(GO_HODIR_ENTER);
            }
            else if (uiData == FAIL)
                OpenDoor(GO_HODIR_ENTER);
            break;
        case TYPE_THORIM:
            DoUseDoorOrButton(GO_LIGHTNING_FIELD);
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_SIFFED, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_LOSE_YOUR_ILLUSION, false);
                DoUseDoorOrButton(GO_DARK_IRON_PORTCULIS);
            }
            if (uiData == DONE)
            {
                if (m_auiEncounter[TYPE_THORIM_HARD] != DONE)
                {
                    if (instance->IsRegularDifficulty())
                    {
                        DoRespawnGameObject(GO_CACHE_OF_STORMS, 30*MINUTE);
                    }
                    else
                    {
                        DoRespawnGameObject(GO_CACHE_OF_STORMS_H, 30*MINUTE);
                    }
                }
                // used to make the friendly keeper visible
                if (Creature* pImage = GetSingleCreatureFromStorage(KEEPER_THORIM))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            break;
        case TYPE_FREYA:
            if (uiData == DONE)
            {
                // do this in order to see how many elders were alive and spawn the correct chest
                // hard mode drop
                if (m_auiEncounter[TYPE_FREYA_HARD] != DONE)
                {
                    if (instance->IsRegularDifficulty())
                    {
                        DoRespawnGameObject(GO_FREYA_GIFT, 30*MINUTE);
                    }
                    else
                    {
                        DoRespawnGameObject(GO_FREYA_GIFT_H, 30*MINUTE);
                    }
                }
                // used to make the friendly keeper visible
                if (Creature* pImage = GetSingleCreatureFromStorage(KEEPER_FREYA))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_BACK_TO_NATURE, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_KNOCK_WOOD, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_KNOCK_KNOCK_WOOD, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_KNOCK_KNOCK_KNOCK_WOOD, false);
            }
            break;
            // Prison
        case TYPE_VEZAX:
            if (uiData == DONE)
                DoUseDoorOrButton(GO_VEZAX_GATE);
            if (uiData == IN_PROGRESS)
            {
                SetSpecialAchievementCriteria(TYPE_ACHIEV_MORNING_SARONITE, false);
            }
            break;
        case TYPE_YOGGSARON:
            DoUseDoorOrButton(GO_YOGG_GATE);
            if (uiData == IN_PROGRESS)
            {
                DoStartTimedAchievement(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, ACHIEV_START_YOGG_SARON_ID);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_THREE_LIGHTS, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_TWO_LIGHTS, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_ONE_LIGHT, false);
                SetSpecialAchievementCriteria(TYPE_ACHIEV_ALONE, false);
            }
            if (uiData == FAIL)
            {
                // respawn clouds
                for (GuidList::iterator iter = m_lCloudGuids.begin(); iter != m_lCloudGuids.end(); ++iter)
                    if (Creature* pTmp = instance->GetCreature(*iter))
                        pTmp->Respawn();
                // respawn Sara
                if (Creature* pSara = GetSingleCreatureFromStorage(NPC_SARA))
                {
                    if (!pSara->isAlive())
                        pSara->Respawn();
                    else
                        pSara->AI()->EnterEvadeMode();
                }
                if (Creature* pYoggBrain = GetSingleCreatureFromStorage(NPC_YOGG_BRAIN))
                {
                    if (!pYoggBrain->isAlive())
                        pYoggBrain->Respawn();
                    else
                        pYoggBrain->AI()->EnterEvadeMode();
                }
            }
            break;

            // Celestial Planetarium
        case TYPE_ALGALON:
            DoUseDoorOrButton(GO_CELESTIAL_DOOR);
            DoUseDoorOrButton(GO_UNIVERSE_FLOOR_CELESTIAL);
            if (uiData == DONE)
                DoRespawnGameObject(GO_GIFT_OF_OBSERVER, 30*MINUTE);
            break;

            // Hard modes
        case TYPE_LEVIATHAN_DIFFICULTY:
        case TYPE_XT002_HARD:
            break;
        case TYPE_ASSEMBLY_HARD:
            break;
        case TYPE_MIMIRON_HARD:
            if (uiData == DONE)
            {
                if (instance->IsRegularDifficulty())
                {
                    DoRespawnGameObject(GO_CACHE_OF_INOV_HARD, 30*MINUTE);
                }
                else
                {
                    DoRespawnGameObject(GO_CACHE_OF_INOV_HARD_H, 30*MINUTE);
                }
            }
            break;
        case TYPE_HODIR_HARD:
            if (uiData == DONE)
            {
                if (instance->IsRegularDifficulty())
                {
                    DoRespawnGameObject(GO_CACHE_OF_RARE_WINTER, 30*MINUTE);
                }
                else
                {
                    DoRespawnGameObject(GO_CACHE_OF_RARE_WINTER_H, 30*MINUTE);
                }
            }
            break;
        case TYPE_THORIM_HARD:
            if (uiData == DONE)
            {
                if (instance->IsRegularDifficulty())
                {
                    DoRespawnGameObject(GO_CACHE_OF_RARE_STORMS, 30*MINUTE);
                }
                else
                {
                    DoRespawnGameObject(GO_CACHE_OF_RARE_STORMS_H, 30*MINUTE);
                }
            }
            break;
        case TYPE_FREYA_HARD:
            if (uiData == DONE)
            {
                if (instance->IsRegularDifficulty())
                {
                    DoRespawnGameObject(GO_FREYA_GIFT_HARD, 30*MINUTE);
                }
                else
                {
                    DoRespawnGameObject(GO_FREYA_GIFT_HARD_H, 30*MINUTE);
                }
            }
            break;
        case TYPE_VEZAX_HARD:
        case TYPE_YOGGSARON_HARD:
            break;

        // Ulduar keepers
        case TYPE_KEEPER_HODIR:
        case TYPE_KEEPER_THORIM:
        case TYPE_KEEPER_FREYA:
        case TYPE_KEEPER_MIMIRON:
            break;

        // teleporters
        case TYPE_LEVIATHAN_TP:
        case TYPE_XT002_TP:
        case TYPE_MIMIRON_TP:
            break;

        // mini boss
        case TYPE_RUNIC_COLOSSUS:
            if (uiData == DONE)
                OpenDoor(GO_RUNED_STONE_DOOR);
            else
                CloseDoor(GO_RUNED_STONE_DOOR);
            break;
        case TYPE_RUNE_GIANT:
            if (uiData == DONE)
                OpenDoor(GO_THORIM_STONE_DOOR);
            else
                CloseDoor(GO_THORIM_STONE_DOOR);
            break;
        case TYPE_LEVIATHAN_MK:
            break;
        case TYPE_VX001:
            /*if (uiData == DONE)     // just for animation :)
            {
                for (uint8 i = 0; i < 9; i++)
                    DoUseDoorOrButton(m_uiMimironTelGUID[i]);
            }*/
            break;
        case TYPE_AERIAL_UNIT:
        case TYPE_YOGG_BRAIN:
            break;

        //phases
        case TYPE_MIMIRON_PHASE:
        case TYPE_YOGG_PHASE:
        case TYPE_VISION_PHASE:
            break;
        default:
            error_log("Used undefined uiType(%u) in instance_ulduar::SetData()", uiType);
            return;
    }
    m_auiEncounter[uiType] = uiData;

    if (uiData == DONE || uiData == FAIL)
    {
        OUT_SAVE_INST_DATA;

        // save all encounters, hard bosses and keepers
        std::ostringstream saveStream;
        saveStream << m_auiEncounter[TYPE_LEVIATHAN] << " " << m_auiEncounter[TYPE_IGNIS] << " " << m_auiEncounter[TYPE_RAZORSCALE] << " "
            << m_auiEncounter[TYPE_XT002] << " " << m_auiEncounter[TYPE_ASSEMBLY] << " " << m_auiEncounter[TYPE_KOLOGARN] << " "
            << m_auiEncounter[TYPE_AURIAYA] << " " << m_auiEncounter[TYPE_MIMIRON] << " " << m_auiEncounter[TYPE_HODIR] << " "
            << m_auiEncounter[TYPE_THORIM] << " " << m_auiEncounter[TYPE_FREYA] << " " << m_auiEncounter[TYPE_VEZAX] << " "
            << m_auiEncounter[TYPE_YOGGSARON] << " " << m_auiEncounter[TYPE_ALGALON] << " " << m_auiEncounter[TYPE_LEVIATHAN_DIFFICULTY] << " "
            << m_auiEncounter[TYPE_MIMIRON_HARD] << " "
            << m_auiEncounter[TYPE_HODIR_HARD] << " " << m_auiEncounter[TYPE_THORIM_HARD] << " " << m_auiEncounter[TYPE_FREYA_HARD] << " "
            << m_auiEncounter[TYPE_VEZAX_HARD] << " " << m_auiEncounter[TYPE_YOGGSARON_HARD] << " " << m_auiEncounter[TYPE_KEEPER_HODIR] << " "
            << m_auiEncounter[TYPE_KEEPER_THORIM] << " " << m_auiEncounter[TYPE_KEEPER_FREYA] << " " << m_auiEncounter[TYPE_KEEPER_MIMIRON] << " "
            << m_auiEncounter[TYPE_LEVIATHAN_TP] << " " << m_auiEncounter[TYPE_XT002_TP] << " " << m_auiEncounter[TYPE_MIMIRON_TP];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_ulduar::SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet)
{
    if (uiType < MAX_SPECIAL_ACHIEV_CRITS)
        m_abAchievCriteria[uiType] = bIsMet;
}

bool instance_ulduar::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{
    switch (uiCriteriaId)
    {
        case ACHIEV_CRIT_SHATTERED:
        case ACHIEV_CRIT_SHATTERED_H:
            return m_abAchievCriteria[TYPE_ACHIEV_SHATTERED];
        case ACHIEV_CRIT_QUICK_SHAVE:
        case ACHIEV_CRIT_QUICK_SHAVE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_QUICK_SHAVE];
        case ACHIEV_CRIT_IRON_DWARF_MEDIUM_RARE:
        case ACHIEV_CRIT_IRON_DWARF_MEDIUM_RARE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_IRON_DWARF_MEDIUM_RARE];
        case ACHIEV_CRIT_NERF_ENGINEERING:
        case ACHIEV_CRIT_NERF_ENGINEERING_H:
            return m_abAchievCriteria[TYPE_ACHIEV_NERF_ENGINEERING];
        case ACHIEV_CRIT_HEARTBREAKER:
        case ACHIEV_CRIT_HEARTBREAKER_H:
            return m_abAchievCriteria[TYPE_ACHIEV_HEARTBREAKER];
        case ACHIEV_CRIT_YOU_BRUNDIR:
        case ACHIEV_CRIT_YOU_BRUNDIR_H:
            return m_abAchievCriteria[TYPE_ACHIEV_YOU_BRUNDIR];
        case ACHIEV_CRIT_YOU_MOLGEIM:
        case ACHIEV_CRIT_YOU_MOLGEIM_H:
            return m_abAchievCriteria[TYPE_ACHIEV_YOU_MOLGEIM];
        case ACHIEV_CRIT_YOU_STEELBREAKER:
        case ACHIEV_CRIT_YOU_STEELBREAKER_H:
            return m_abAchievCriteria[TYPE_ACHIEV_YOU_STEELBREAKER];
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_BRUNDIR:
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_BRUNDIR_H:
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_MOLGEIM:
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_MOLGEIM_H:
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_STEELBREAKER:
        case ACHIEV_CRIT_BUT_I_AM_ON_YOUR_SIDE_STEELBREAKER_H:
        {
            if (GetData(TYPE_ASSEMBLY) == DONE)
            {
                if (pSource && pSource->HasAura(SPELL_IRON_BOOT_AURA))
                    return true;
            }
            break;
        }
        case ACHIEV_CRIT_DISARMED:
        case ACHIEV_CRIT_DISARMED_H:
            return m_abAchievCriteria[TYPE_ACHIEV_DISARMED];
        case ACHIEV_CRIT_OPEN_ARMS:
        case ACHIEV_CRIT_OPEN_ARMS_H:
            return m_abAchievCriteria[TYPE_ACHIEV_OPEN_ARMS];
        case ACHIEV_IF_LOOKS_COULD_KILL:
        case ACHIEV_IF_LOOKS_COULD_KILL_H:
            return m_abAchievCriteria[TYPE_ACHIEV_IF_LOOKS_COULD_KILL];
        case ACHIEV_CRIT_RUBBLE_AND_ROLL:
        case ACHIEV_CRIT_RUBBLE_AND_ROLL_H:
            return m_abAchievCriteria[TYPE_ACHIEV_RUBBLE_AND_ROLL];
        case ACHIEV_CRIT_NINE_LIVES:
        case ACHIEV_CRIT_NINE_LIVES_H:
            return m_abAchievCriteria[TYPE_ACHIEV_NINE_LIVES];
        case ACHIEV_CRIT_CRAZY_CAT_LADY:
        case ACHIEV_CRIT_CRAZY_CAT_LADY_H:
            return m_abAchievCriteria[TYPE_ACHIEV_CRAZY_CAT_LADY];
        case ACHIEV_CRIT_CHEESE_FREEZE:
        case ACHIEV_CRIT_CHEESE_FREEZE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_CHEESE_FREEZE];
        case ACHIEV_CRIT_COOLEST_FRIEND:
        case ACHIEV_CRIT_COOLEST_FRIEND_H:
            return m_abAchievCriteria[TYPE_ACHIEV_COOLEST_FRIEND];
        case ACHIEV_CRIT_RARE_CACHE:
        case ACHIEV_CRIT_RARE_CACHE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_RARE_CACHE];
        case ACHIEV_CRIT_SIFFED:
        case ACHIEV_CRIT_SIFFED_H:
            return m_abAchievCriteria[TYPE_ACHIEV_SIFFED];
        case ACHIEV_CRIT_LOSE_YOUR_ILLUSION:
        case ACHIEV_CRIT_LOSE_YOUR_ILLUSION_H:
            return m_abAchievCriteria[TYPE_ACHIEV_LOSE_YOUR_ILLUSION];
        case ACHIEV_CRIT_BACK_TO_NATURE:
        case ACHIEV_CRIT_BACK_TO_NATURE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_BACK_TO_NATURE];
        case ACHIEV_CRIT_KNOCK_WOOD:
        case ACHIEV_CRIT_KNOCK_WOOD_H:
            return m_abAchievCriteria[TYPE_ACHIEV_KNOCK_WOOD];
        case ACHIEV_CRIT_KNOCK_KNOCK_WOOD:
        case ACHIEV_CRIT_KNOCK_KNOCK_WOOD_H:
            return m_abAchievCriteria[TYPE_ACHIEV_KNOCK_KNOCK_WOOD];
        case ACHIEV_CRIT_KNOCK_KNOCK_KNOCK_WOOD:
        case ACHIEV_CRIT_KNOCK_KNOCK_KNOCK_WOOD_H:
            return m_abAchievCriteria[TYPE_ACHIEV_KNOCK_KNOCK_KNOCK_WOOD];
        case ACHIEV_CRIT_FIREFIGHTER:
        case ACHIEV_CRIT_FIREFIGHTER_H:
            return m_abAchievCriteria[TYPE_ACHIEV_FIREFIGHTER];
        case ACHIEV_CRIT_SARONITE_N:
        case ACHIEV_CRIT_SARONITE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_MORNING_SARONITE];
        case ACHIEV_CRIT_THREE_LIGHTS:
        case ACHIEV_CRIT_THREE_LIGHTS_H:
            return m_abAchievCriteria[TYPE_ACHIEV_THREE_LIGHTS];
        case ACHIEV_CRIT_TWO_LIGHTS:
        case ACHIEV_CRIT_TWO_LIGHTS_H:
            return m_abAchievCriteria[TYPE_ACHIEV_TWO_LIGHTS];
        case ACHIEV_CRIT_ONE_LIGHT:
        case ACHIEV_CRIT_ONE_LIGHT_H:
            return m_abAchievCriteria[TYPE_ACHIEV_ONE_LIGHT];
        case ACHIEV_CRIT_ALONE:
        case ACHIEV_CRIT_ALONE_H:
            return m_abAchievCriteria[TYPE_ACHIEV_ALONE];
    }

    return false;
}

bool instance_ulduar::CheckConditionCriteriaMeet(Player const* pPlayer, uint32 uiInstanceConditionId, WorldObject const* pConditionSource, ConditionSource conditionSourceType)
{
    if (pConditionSource->GetTypeId() == TYPEID_UNIT)
    {
        uint32 entry = pConditionSource->GetEntry();
        switch (uiInstanceConditionId)
        {
            case INSTANCE_CONDITION_ID_NORMAL_MODE:
                if (entry == NPC_XT002)
                    return GetData(TYPE_XT002_HARD) != DONE;
                break;
            case INSTANCE_CONDITION_ID_HARD_MODE:
                if (entry == NPC_XT002)
                    return GetData(TYPE_XT002_HARD) == DONE;
                break;
            case INSTANCE_CONDITION_ID_HARD_MODE_2:
                break;
            case INSTANCE_CONDITION_ID_HARD_MODE_3:
                break;
            case INSTANCE_CONDITION_ID_HARD_MODE_4:
                break;
            default:
                break;
        }
    }

    script_error_log("instance_ulduar::CheckConditionCriteriaMeet called with unsupported Id %u. Called with param plr %s, src %s, condition source type %u",
                         uiInstanceConditionId, pPlayer ? pPlayer->GetGuidStr().c_str() : "NULL", pConditionSource ? pConditionSource->GetGuidStr().c_str() : "NULL", conditionSourceType);
    return false;
}

void instance_ulduar::SortHandTrigger(Creature* pCreature)
{
    // only Handtrigger NPC
    if (pCreature->GetEntry() != NPC_RIGHT_HAND_TRIGGER && pCreature->GetEntry() != NPC_LEFT_HAND_TRIGGER)
        return;

    if (pCreature->GetPositionY() < -376)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][0].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -376 && pCreature->GetPositionY() < -363)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][1].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -363 && pCreature->GetPositionY() < -351)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][2].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -351 && pCreature->GetPositionY() < -337)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][3].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -337 && pCreature->GetPositionY() < -322)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][4].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -322 && pCreature->GetPositionY() < -308)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][5].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -308 && pCreature->GetPositionY() < -293)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][6].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -293 && pCreature->GetPositionY() < -279)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][7].push_back(pCreature->GetObjectGuid());
    }
    else if (pCreature->GetPositionY() >= -279 && pCreature->GetPositionY() < -265)
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][8].push_back(pCreature->GetObjectGuid());
    }
    else
    {
        m_lHandTriggerGuids[pCreature->GetEntry() == NPC_RIGHT_HAND_TRIGGER ? RIGHT_EXPLOSION : LEFT_EXPLOSION][9].push_back(pCreature->GetObjectGuid());
    }
}

void instance_ulduar::Update(uint32 const uiDiff)
{
    if (m_bOneIsDeath)
    {
        if (m_uiShatterTimer < uiDiff)
        {
            m_bOneIsDeath = false;
        }
        else
            m_uiShatterTimer -= uiDiff;
    }

    if (m_uiExplosionTimer < uiDiff)
    {
        if (m_explosionSide != NO_EXPLOSION)
        {
            if (m_uiExplosionRow > 9)
            {
                m_explosionSide = NO_EXPLOSION;
            }
            else
            {
                if (Creature* pColossus = GetSingleCreatureFromStorage(NPC_RUNIC_COLOSSUS))
                {
                    for (GuidList::iterator itr = m_lHandTriggerGuids[m_explosionSide][m_uiExplosionRow].begin(); itr != m_lHandTriggerGuids[m_explosionSide][m_uiExplosionRow].end(); ++itr)
                    {
                        if (Unit* trigger = instance->GetUnit(*itr))
                        {
                            trigger->CastSpell(trigger, SPELL_RUNIC_SMASH_DMG, false, 0, 0, pColossus->GetObjectGuid());
                        }
                    }
                }
                ++m_uiExplosionRow;
                m_uiExplosionTimer = 250;
            }
        }
    }
    else
        m_uiExplosionTimer -= uiDiff;
}

uint32 instance_ulduar::GetData(uint32 uiType)
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

const char* instance_ulduar::Save()
{
    return m_strInstData.c_str();
}

void instance_ulduar::Load(const char* strIn)
{
    if (!strIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(strIn);

    std::istringstream loadStream(strIn);
    loadStream >> m_auiEncounter[TYPE_LEVIATHAN] >> m_auiEncounter[TYPE_IGNIS] >> m_auiEncounter[TYPE_RAZORSCALE] >> m_auiEncounter[TYPE_XT002]
    >> m_auiEncounter[TYPE_ASSEMBLY] >> m_auiEncounter[TYPE_KOLOGARN] >> m_auiEncounter[TYPE_AURIAYA] >> m_auiEncounter[TYPE_MIMIRON]
    >> m_auiEncounter[TYPE_HODIR] >> m_auiEncounter[TYPE_THORIM] >> m_auiEncounter[TYPE_FREYA] >> m_auiEncounter[TYPE_VEZAX]
    >> m_auiEncounter[TYPE_YOGGSARON] >> m_auiEncounter[TYPE_ALGALON] >> m_auiEncounter[TYPE_LEVIATHAN_DIFFICULTY]
    >> m_auiEncounter[TYPE_MIMIRON_HARD] >> m_auiEncounter[TYPE_HODIR_HARD] >> m_auiEncounter[TYPE_THORIM_HARD]
    >> m_auiEncounter[TYPE_FREYA_HARD] >> m_auiEncounter[TYPE_VEZAX_HARD] >> m_auiEncounter[TYPE_YOGGSARON_HARD] >> m_auiEncounter[TYPE_KEEPER_HODIR]
    >> m_auiEncounter[TYPE_KEEPER_THORIM] >> m_auiEncounter[TYPE_KEEPER_FREYA] >> m_auiEncounter[TYPE_KEEPER_MIMIRON] >> m_auiEncounter[TYPE_LEVIATHAN_TP]
    >> m_auiEncounter[TYPE_XT002_TP] >> m_auiEncounter[TYPE_MIMIRON_TP];

    for (uint8 i = 0; i < MAX_BOSS_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_ulduar(Map* pMap)
{
    return new instance_ulduar(pMap);
}

void AddSC_instance_ulduar()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_ulduar";
    pNewScript->GetInstanceData = &GetInstanceData_instance_ulduar;
    pNewScript->RegisterSelf();
}
