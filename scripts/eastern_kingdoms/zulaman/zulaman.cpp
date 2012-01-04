/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: Zulaman
SD%Complete: 90
SDComment: Forest Frog will turn into different NPC's. Workaround to prevent new entry from running this script
SDCategory: Zul'Aman
EndScriptData */

/* ContentData
npc_forest_frog
EndContentData */

#include "precompiled.h"
#include "zulaman.h"
#include "escort_ai.h"

/*######
## npc_forest_frog
######*/

enum
{
    SPELL_REMOVE_AMANI_CURSE = 43732,
    SPELL_PUSH_MOJO          = 43923,
    NPC_FOREST_FROG          = 24396
};

struct MANGOS_DLL_DECL npc_forest_frogAI : public ScriptedAI
{
    npc_forest_frogAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset() { }

    void DoSpawnRandom()
    {
        if (m_pInstance)
        {
            uint32 cEntry = 0;
            switch(urand(0, 10))
            {
                case 0: cEntry = 24024; break;              //Kraz      // wrong here?
                case 1: cEntry = 24397; break;              //Mannuth
                case 2: cEntry = 24403; break;              //Deez
                case 3: cEntry = 24404; break;              //Galathryn
                case 4: cEntry = 24405; break;              //Adarrah
                case 5: cEntry = 24406; break;              //Fudgerick
                case 6: cEntry = 24407; break;              //Darwen
                case 7: cEntry = 24445; break;              //Mitzi
                case 8: cEntry = 24448; break;              //Christian
                case 9: cEntry = 24453; break;              //Brennan
                case 10: cEntry = 24455; break;             //Hollee
            }

            if (!m_pInstance->GetData(TYPE_RAND_VENDOR_1))
                if (!urand(0, 9))
                    cEntry = 24408;                         //Gunter

            if (!m_pInstance->GetData(TYPE_RAND_VENDOR_2))
                if (!urand(0, 9))
                    cEntry = 24409;                         //Kyren

            if (cEntry)
                m_creature->UpdateEntry(cEntry);

            if (cEntry == 24408)
                m_pInstance->SetData(TYPE_RAND_VENDOR_1,DONE);

            if (cEntry == 24409)
                m_pInstance->SetData(TYPE_RAND_VENDOR_2,DONE);
        }
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_REMOVE_AMANI_CURSE && caster->GetTypeId() == TYPEID_PLAYER && m_creature->GetEntry() == NPC_FOREST_FROG)
        {
            //increase or decrease chance of mojo?
            if (!urand(0, 49))
                DoCastSpellIfCan(caster, SPELL_PUSH_MOJO, CAST_TRIGGERED);
            else
                DoSpawnRandom();
        }
    }
};
CreatureAI* GetAI_npc_forest_frog(Creature* pCreature)
{
    return new npc_forest_frogAI(pCreature);
}

/*######
## npc_harrison_jones_za
######*/

enum
{
    SAY_START               = -1568079,
    SAY_AT_GONG             = -1568080,
    SAY_OPEN_ENTRANCE       = -1568081,

    SPELL_BANGING_THE_GONG  = 45225
};

#define GOSSIP_ITEM_BEGIN   "Thanks for the concern, but we intend to explore Zul'Aman."
#define GOSSIP_ITEM_HAKOR   "Event Starts." // TODO : What is correct gossip text ?
#define GOSSIP_ITEM_TANZAR  "Event Starts." // TODO : What is correct gossip text ?
#define GOSSIP_ITEM_KRAZ    "Event Starts." // TODO : What is correct gossip text ?
#define GOSSIP_ITEM_ASHLI   "Event Starts." // TODO : What is correct gossip text ?

struct MANGOS_DLL_DECL npc_harrison_jones_zaAI : public npc_escortAI
{
    npc_harrison_jones_zaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 1:
                DoScriptText(SAY_AT_GONG, m_creature);

                if (GameObject* pStrangeGong = m_pInstance->GetSingleGameObjectFromStorage(GO_STRANGE_GONG))
                    pStrangeGong->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);

                //Start bang gong for 2min
                m_creature->CastSpell(m_creature, SPELL_BANGING_THE_GONG, false);
                SetEscortPaused(true);
                break;
            case 3:
                DoScriptText(SAY_OPEN_ENTRANCE, m_creature);
                break;
            case 4:
                m_pInstance->SetData(TYPE_EVENT_RUN, IN_PROGRESS);
                m_pInstance->SetData(TYPE_NALORAKK, NOT_STARTED);
                m_pInstance->SetData(TYPE_AKILZON, NOT_STARTED);
                m_pInstance->SetData(TYPE_JANALAI, NOT_STARTED);
                //TODO: Spawn group of Amani'shi Savage and make them run to entrance
                break;
        }
    }

    void Reset() { }

    void StartEvent()
    {
        DoScriptText(SAY_START, m_creature);
        Start();
    }

    void SetHoldState(bool bOnHold)
    {
        SetEscortPaused(bOnHold);

        //Stop banging gong if still
        if (m_pInstance && m_pInstance->GetData(TYPE_EVENT_RUN) == SPECIAL && m_creature->HasAura(SPELL_BANGING_THE_GONG))
            m_creature->RemoveAurasDueToSpell(SPELL_BANGING_THE_GONG);
    }
};

bool GossipHello_npc_harrison_jones_za(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pInstance && pInstance->GetData(TYPE_EVENT_RUN) == NOT_STARTED)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEGIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_harrison_jones_za(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (npc_harrison_jones_zaAI* pHarrisonAI = dynamic_cast<npc_harrison_jones_zaAI*>(pCreature->AI()))
            pHarrisonAI->StartEvent();

        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_harrison_jones_za(Creature* pCreature)
{
    return new npc_harrison_jones_zaAI(pCreature);
}

/*######
## npc_tanzar_za
######*/

struct MANGOS_DLL_DECL npc_tanzar_zaAI : public npc_escortAI
{
    npc_tanzar_zaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    bool m_bEventStarted;

    ScriptedInstance* m_pInstance;

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 2:
                m_creature->HandleEmote(EMOTE_STATE_USESTANDING);
                break;
            case 3:
                // TODO: Tanzar say ...
                if (GameObject* pTanzarsTrunk = m_pInstance->GetSingleGameObjectFromStorage(GO_TANZARS_TRUNK))
                    pTanzarsTrunk->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                m_creature->HandleEmote(EMOTE_ONESHOT_NONE);
                m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                SetRun(true);
                break;
        }
    }

    void Reset()
    {
        m_bEventStarted = false;
    }

    void StartEvent()
    {
        if (!m_bEventStarted)
        {
            if (GameObject* pGo = m_pInstance->GetSingleGameObjectFromStorage(GO_TANZARS_CAGE))
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                pGo->SetGoState(GO_STATE_ACTIVE);
            }
            Start();
            m_bEventStarted = true;
        }
    }
};

bool GossipHello_npc_tanzar_za(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && (pInstance->GetData(TYPE_EVENT_RUN) == IN_PROGRESS || pInstance->GetData(TYPE_EVENT_RUN) == DONE) && pInstance->GetData(TYPE_NALORAKK) == DONE || pPlayer->isGameMaster())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TANZAR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_tanzar_za(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (npc_tanzar_zaAI* pTanzarAI = dynamic_cast<npc_tanzar_zaAI*>(pCreature->AI()))
            pTanzarAI->StartEvent();

        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_tanzar_za(Creature* pCreature)
{
    return new npc_tanzar_zaAI(pCreature);
}

/*######
## npc_kraz_za
######*/

struct MANGOS_DLL_DECL npc_kraz_zaAI : public npc_escortAI
{
    npc_kraz_zaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    bool m_bEventStarted;

    ScriptedInstance* m_pInstance;

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 4:
                m_creature->HandleEmote(EMOTE_STATE_USESTANDING);
                break;
            case 5:
                // TODO: Kraz say ...
                if (GameObject* pKrazsPackage = m_pInstance->GetSingleGameObjectFromStorage(GO_KRAZS_PACKAGE))
                    pKrazsPackage->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                m_creature->HandleEmote(EMOTE_ONESHOT_NONE);
                m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                SetRun(true);
                break;
        }
    }

    void Reset()
    {
        m_bEventStarted = false;
    }

    void StartEvent()
    {
        if (!m_bEventStarted)
        {
            if (GameObject* pGo = m_pInstance->GetSingleGameObjectFromStorage(GO_KRAZS_CAGE))
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                pGo->SetGoState(GO_STATE_ACTIVE);
            }
            Start();
            m_bEventStarted = true;
        }
    }
};

bool GossipHello_npc_kraz_za(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && (pInstance->GetData(TYPE_EVENT_RUN) == IN_PROGRESS || pInstance->GetData(TYPE_EVENT_RUN) == DONE) && pInstance->GetData(TYPE_JANALAI) == DONE || pPlayer->isGameMaster())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KRAZ, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_kraz_za(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (npc_kraz_zaAI* pKrazAI = dynamic_cast<npc_kraz_zaAI*>(pCreature->AI()))
            pKrazAI->StartEvent();

        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_kraz_za(Creature* pCreature)
{
    return new npc_kraz_zaAI(pCreature);
}

/*######
## npc_ashli_za
######*/

struct MANGOS_DLL_DECL npc_ashli_zaAI : public npc_escortAI
{
    npc_ashli_zaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    bool m_bEventStarted;

    ScriptedInstance* m_pInstance;

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 2:
                m_creature->CastSpell(m_creature,SPELL_ASHLIS_FIREBALL,false);
                break;
            case 4:
                m_creature->CastSpell(m_creature,SPELL_ASHLIS_FIREBALL,false);
                break;
            case 7:
                // TODO: Ashli say ...
                m_creature->CastSpell(m_creature,SPELL_ASHLIS_FIREBALL,false);
                if (GameObject* pAshlisBag = m_pInstance->GetSingleGameObjectFromStorage(GO_ASHLIS_BAG))
                    pAshlisBag->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                SetRun(true);
                break;
        }
    }

    void Reset()
    {
        m_bEventStarted = false;
    }

    void StartEvent()
    {
        if (!m_bEventStarted)
        {
            if (GameObject* pGo = m_pInstance->GetSingleGameObjectFromStorage(GO_ASHLIS_CAGE))
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                pGo->SetGoState(GO_STATE_ACTIVE);
            }
            Start();
            m_bEventStarted = true;
        }
    }
};

bool GossipHello_npc_ashli_za(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_EVENT_RUN) == DONE || pPlayer->isGameMaster())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ASHLI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_ashli_za(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (npc_ashli_zaAI* pAshliAI = dynamic_cast<npc_ashli_zaAI*>(pCreature->AI()))
            pAshliAI->StartEvent();

        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_ashli_za(Creature* pCreature)
{
    return new npc_ashli_zaAI(pCreature);
}

/*######
## npc_harkor_za
######*/

enum
{
    SAY_HARKOR_FREED          = -1568086,
    SAY_HARKOR_THANK          = -1568087
};

struct MANGOS_DLL_DECL npc_harkor_zaAI : public npc_escortAI
{
    npc_harkor_zaAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    bool m_bEventStarted;

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        m_bEventStarted = false;
    }

    void WaypointReached(uint32 uiPointId)
    {
        if (!m_pInstance)
            return;

        switch(uiPointId)
        {
            case 0:
                DoScriptText(SAY_HARKOR_FREED, m_creature);
                break;
            case 1:
                DoScriptText(SAY_HARKOR_THANK, m_creature);
                break;
            case 3:
                m_creature->HandleEmote(EMOTE_ONESHOT_KNEEL);
                break;
            case 4:
                if (GameObject* pDwarfHammer = m_pInstance->GetSingleGameObjectFromStorage(GO_DWARF_HAMMER))
                    pDwarfHammer->Delete();
                SetEquipmentSlots(false, EQUIP_ID_HARKORS_WEAPON, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);
                break;
            case 5:
                m_creature->SetFacingTo(0.9948376f);
            case 6:
                m_creature->CastSpell(m_creature, 43255, false); // TODO : Use spell name
                break;
            case 7:
                m_creature->CastSpell(m_creature, 43255, true); // TODO : Use spell name
                m_creature->HandleEmote(EMOTE_ONESHOT_ATTACK2HTIGHT);
                m_creature->PlayDirectSound(677); // Coin Sound
                if (GameObject* pLootBoxDwarf = m_pInstance->GetSingleGameObjectFromStorage(GO_LOOT_BOX_DWARF))
                    pLootBoxDwarf->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                if (GameObject* pHarkorsSatchel = m_pInstance->GetSingleGameObjectFromStorage(GO_HARKORS_SATCHEL))
                    pHarkorsSatchel->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                //  Create 186633(3 times), 186634 TODO : Need core support
                /*Map* map = m_creature->GetMap();
                for (uint8 i = 0; i < 3; ++i)
                {
                    GameObject* pObj = new GameObject;
                    if (pObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), 186633, map, m_creature->GetPositionX()+(rand()%2) ,m_creature->GetPositionY()+(rand()%2) ,m_creature->GetPositionZ(), m_creature->GetOrientation()))
                    {
                        pObj->SetRespawnTime(604800);
                        map->Add(pObj);
                    }
                    else
                        delete pObj;
                }*/
                m_creature->HandleEmote(EMOTE_ONESHOT_NONE);
                m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                SetRun(true);
                break;
        }
    }

    void StartEvent()
    {
        if (!m_bEventStarted)
        {
            if (GameObject* pGo = m_pInstance->GetSingleGameObjectFromStorage(GO_HARKORS_CAGE))
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_KICK);
                pGo->SetGoState(GO_STATE_ACTIVE);
            }
            Start();
            m_bEventStarted = true;
        }
    }
};

bool GossipHello_npc_harkor_za(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && (pInstance->GetData(TYPE_EVENT_RUN) == IN_PROGRESS || pInstance->GetData(TYPE_EVENT_RUN) == DONE) && pInstance->GetData(TYPE_AKILZON) == DONE || pPlayer->isGameMaster())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_HAKOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_harkor_za(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (npc_harkor_zaAI* pHarkorAI = dynamic_cast<npc_harkor_zaAI*>(pCreature->AI()))
            pHarkorAI->StartEvent();

        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI_npc_harkor_za(Creature* pCreature)
{
    return new npc_harkor_zaAI(pCreature);
}

/*######
## go_strange_gong
######*/

//Unsure how this Gong must work. Here we always return false to allow Mangos always process further.
bool GOUse_go_strange_gong(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    pInstance->SetData(TYPE_EVENT_RUN, SPECIAL);

    if (pInstance->GetData(TYPE_EVENT_RUN) == SPECIAL)
    {
        if (Creature* pCreature = pInstance->GetSingleCreatureFromStorage(NPC_HARRISON))
        {
            if (npc_harrison_jones_zaAI* pHarrisonAI = dynamic_cast<npc_harrison_jones_zaAI*>(pCreature->AI()))
                pHarrisonAI->SetHoldState(false);
        }
        else
            error_log("SD2: Instance Zulaman: go_strange_gong failed");

        pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
    }

    return false;
}

void AddSC_zulaman()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_forest_frog";
    pNewScript->GetAI = &GetAI_npc_forest_frog;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_harrison_jones_za";
    pNewScript->GetAI = &GetAI_npc_harrison_jones_za;
    pNewScript->pGossipHello =  &GossipHello_npc_harrison_jones_za;
    pNewScript->pGossipSelect = &GossipSelect_npc_harrison_jones_za;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tanzar_za";
    pNewScript->GetAI = &GetAI_npc_tanzar_za;
    pNewScript->pGossipHello =  &GossipHello_npc_tanzar_za;
    pNewScript->pGossipSelect = &GossipSelect_npc_tanzar_za;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_kraz_za";
    pNewScript->GetAI = &GetAI_npc_kraz_za;
    pNewScript->pGossipHello =  &GossipHello_npc_kraz_za;
    pNewScript->pGossipSelect = &GossipSelect_npc_kraz_za;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_ashli_za";
    pNewScript->GetAI = &GetAI_npc_ashli_za;
    pNewScript->pGossipHello =  &GossipHello_npc_ashli_za;
    pNewScript->pGossipSelect = &GossipSelect_npc_ashli_za;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_harkor_za";
    pNewScript->GetAI = &GetAI_npc_harkor_za;
    pNewScript->pGossipHello =  &GossipHello_npc_harkor_za;
    pNewScript->pGossipSelect = &GossipSelect_npc_harkor_za;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_strange_gong";
    pNewScript->pGOUse = &GOUse_go_strange_gong;
    pNewScript->RegisterSelf();
}
