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
SDName: Boss_Zuljin
SD%Complete: 95
SDComment:
SDCategory: Zul'Aman
EndScriptData */

#include "precompiled.h"
#include "zulaman.h"

enum
{
    SAY_INTRO                       = -1568056,
    SAY_AGGRO                       = -1568057,
    SAY_BEAR_TRANSFORM              = -1568058,
    SAY_EAGLE_TRANSFORM             = -1568059,
    SAY_LYNX_TRANSFORM              = -1568060,
    SAY_DRAGONHAWK_TRANSFORM        = -1568061,
    SAY_FIRE_BREATH                 = -1568062,
    SAY_BERSERK                     = -1568053,
    SAY_KILL1                       = -1568064,
    SAY_KILL2                       = -1568065,
    SAY_DEATH                       = -1568066,

    EMOTE_BEAR_SPIRIT               = -1568082,
    EMOTE_EAGLE_SPIRIT              = -1568083,
    EMOTE_LYNX_SPIRIT               = -1568084,
    EMOTE_DRAGONHAWK_SPIRIT         = -1568085,

    // Troll Form
    SPELL_WHIRLWIND                 = 17207,
    SPELL_GRIEVOUS_THROW            = 43093,                //removes debuff after full healed

    // Bear Form
    SPELL_CREEPING_PARALYSIS        = 43095,                //should cast on the whole raid
    SPELL_OVERPOWER                 = 43456,                //use after melee attack dodged

    // Eagle Form
    SPELL_ENERGY_STORM              = 43983,                //enemy area aura, trigger 42577 on vortexes which cast 43137 on targets
    SPELL_ZAP_INFORM                = 42577,
    SPELL_ZAP_DAMAGE                = 43137,                //1250 damage
    SPELL_SUMMON_CYCLONE            = 43112,                //summon four feather vortex
    NPC_FEATHER_VORTEX              = 24136,                //ToDo: script via ACID
    SPELL_CYCLONE_VISUAL            = 43119,                //trigger 43147 visual
    SPELL_CYCLONE_PASSIVE           = 43120,                //trigger 43121 (4y aoe) every second

    // Lynx Form
    SPELL_CLAW_RAGE_HASTE           = 42583,                // Charges a random target and applies dummy effect 43149 on it
    SPELL_CLAW_RAGE_TRIGGER         = 43149,                // TODO: Need core fix for direct use (this so cast 43150 too self!)
    SPELL_CLAW_RAGE_DAMAGE          = 43150,
    SPELL_LYNX_RUSH_HASTE           = 43152,                // Charges 9 targets in a row - Dummy effect should apply 43153
    SPELL_LYNX_RUSH_DAMAGE          = 43153,

    // Dragonhawk Form
    SPELL_FLAME_WHIRL               = 43213,                //trigger two spells
    SPELL_FLAME_BREATH              = 43215,
    SPELL_SUMMON_PILLAR             = 43216,                //summon 24187
    NPC_COLUMN_OF_FIRE              = 24187,
    SPELL_PILLAR_TRIGGER            = 43218,                //trigger 43217

    // Cosmetic
    SPELL_SPIRIT_DRAINED            = 42520,
    SPELL_SPIRIT_DRAIN              = 42542,

    // Transforms
    SPELL_SHAPE_OF_THE_BEAR         = 42594,
    SPELL_SHAPE_OF_THE_EAGLE        = 42606,
    SPELL_SHAPE_OF_THE_LYNX         = 42607,
    SPELL_SHAPE_OF_THE_DRAGONHAWK   = 42608,

    SPELL_BERSERK                   = 45078,                // Berserk timer or existance is unk

    MAX_VORTEXES                    = 4,
    POINT_ID_CENTER                 = 0,

    PHASE_BEAR                      = 0,
    PHASE_EAGLE                     = 1,
    PHASE_LYNX                      = 2,
    PHASE_DRAGONHAWK                = 3,
    PHASE_TROLL                     = 4,

    NPC_AMANISHI_SAVAGE             = 23889,
    MAX_GUARDS                      = 8
};

//Guards starting positions in left hand of Boss
const float GUARD_POS_X_AVERAGE       = 119.5f;
const float GUARD_POS_Y               = 688.175f;
const float GUARD_POS_Z               = 45.1115f;
const float GUARD_ORIENT              = 1.580600f;
const float GUARD_SPACE               = 1.5f;

struct BossPhase
{
    uint32 uiSpiritSpellId;
    int32 iYellId, iEmoteId;
    uint32 uiSpiritId;
    uint8 uiPhase;
};

static const BossPhase aZuljinPhases[] =
{
    {SPELL_SHAPE_OF_THE_BEAR,       SAY_BEAR_TRANSFORM,       EMOTE_BEAR_SPIRIT,       NPC_BEAR_SPIRIT,       PHASE_BEAR},
    {SPELL_SHAPE_OF_THE_EAGLE,      SAY_EAGLE_TRANSFORM,      EMOTE_EAGLE_SPIRIT,      NPC_EAGLE_SPIRIT,      PHASE_EAGLE},
    {SPELL_SHAPE_OF_THE_LYNX,       SAY_LYNX_TRANSFORM,       EMOTE_LYNX_SPIRIT,       NPC_LYNX_SPIRIT,       PHASE_LYNX},
    {SPELL_SHAPE_OF_THE_DRAGONHAWK, SAY_DRAGONHAWK_TRANSFORM, EMOTE_DRAGONHAWK_SPIRIT, NPC_DRAGONHAWK_SPIRIT, PHASE_DRAGONHAWK}
};

//coords for going for changing form
static const float fZuljinMoveLoc[3] = {120.148811f, 703.713684f, 45.111477f};

struct MANGOS_DLL_DECL boss_zuljinAI : public ScriptedAI
{
    boss_zuljinAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bHasTaunted = false;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    ObjectGuid m_uiGuardGUIDs[MAX_GUARDS];

    uint8 m_uiPhase;
    uint8 m_uiHealthCheck;

    uint32 m_uiWhirlwindTimer;
    uint32 m_uiGrievousThrowTimer;

    uint32 m_uiParalysisTimer;
    uint32 m_uiOverpowerTimer;

    uint32 m_uiClawRageTimer;
    uint32 m_uiClawRageIntervalTimer;
    uint8  m_uiClawRageCounter;
    bool   m_uiClawRageFinished;
    ObjectGuid m_uiClawRageVictimGUID;
    uint32 m_uiLynxRushTimer;
    bool   m_uiLynxRushFinished;
    uint32 m_uiLynxRushIntervalTimer;
    uint8  m_uiLynxRushCounter;
    ObjectGuid m_uiLynxRushVictimGUID;

    uint32 m_uiFlameWhirlTimer;
    uint32 m_uiFlameBreathTimer;
    uint32 m_uiPillarOfFireTimer;

    bool m_bHasTaunted;
    bool m_bIsInTransition;
    uint32 m_uiTransformTimer;

    GUIDList m_lSummonsList;

    void Reset()
    {
        m_uiHealthCheck         = 80;
        m_uiPhase               = PHASE_TROLL;

        m_uiWhirlwindTimer      = 7000;
        m_uiGrievousThrowTimer  = 8000;

        m_uiParalysisTimer      = 7000;
        m_uiOverpowerTimer      = 0;

        m_uiClawRageTimer       = 5000;
        m_uiLynxRushTimer       = 14000;
        m_uiLynxRushVictimGUID.Clear();
        m_uiClawRageFinished    = true;
        m_uiLynxRushFinished    = true;

        m_uiFlameWhirlTimer     = 7000;
        m_uiFlameBreathTimer    = 15000;
        m_uiPillarOfFireTimer   = 7000;

        m_bIsInTransition       = false;

        SetCombatMovement(true);

        InitializeGuards();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        InitializeGuards();
        AddTreatGuards(pWho);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZULJIN, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZULJIN, FAIL);

        // Despawn all feather vortexes
        DoDespawnVortexes();

        // Reset all spirits
        for (uint8 i = 0; i < MAX_VORTEXES; ++i)
        {
            if (Creature* pSpirit = m_pInstance->GetSingleCreatureFromStorage(aZuljinPhases[i].uiSpiritId))
            {
                pSpirit->SetStandState(UNIT_STAND_STATE_STAND);
                pSpirit->AI()->EnterEvadeMode();
            }
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_KILL1 : SAY_KILL2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        // drain spirit
        if (Creature* pSpirit = m_pInstance->GetSingleCreatureFromStorage(aZuljinPhases[m_uiPhase].uiSpiritId))
        {
            pSpirit->InterruptNonMeleeSpells(false);
            pSpirit->CastSpell(m_creature, SPELL_SPIRIT_DRAINED, false);
            pSpirit->SetStandState(UNIT_STAND_STATE_DEAD);
        }

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_ZULJIN, DONE);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!m_bHasTaunted && m_creature->IsWithinDistInMap(pWho, 60.0f))
        {
            DoScriptText(SAY_INTRO, m_creature);
            m_bHasTaunted = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void DoDespawnVortexes()
    {
        for (GUIDList::const_iterator itr = m_lSummonsList.begin(); itr != m_lSummonsList.end(); ++itr)
        {
            if (Creature* pVortex = m_creature->GetMap()->GetCreature(*itr))
                pVortex->ForcedDespawn();
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        switch(pSummoned->GetEntry())
        {
            case NPC_FEATHER_VORTEX:
                pSummoned->CastSpell(pSummoned, SPELL_CYCLONE_VISUAL, true);
                pSummoned->CastSpell(pSummoned, SPELL_CYCLONE_PASSIVE, true);
                m_lSummonsList.push_back(pSummoned->GetObjectGuid());
                if (m_creature->getVictim())
                    pSummoned->AI()->AttackStart(m_creature->getVictim());
                break;
            case NPC_COLUMN_OF_FIRE:
                pSummoned->CastSpell(pSummoned, SPELL_PILLAR_TRIGGER, true);
                break;
        }
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId)
    {
        if (uiMotionType != POINT_MOTION_TYPE || uiPointId != POINT_ID_CENTER)
            return;

        // increment phase
        if (m_uiPhase == PHASE_TROLL)
            m_uiPhase = PHASE_BEAR;
        else
            ++m_uiPhase;

        // drain the spirit
        if (Creature* pSpirit = m_pInstance->GetSingleCreatureFromStorage(aZuljinPhases[m_uiPhase].uiSpiritId))
            pSpirit->CastSpell(m_creature, SPELL_SPIRIT_DRAIN, false);
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_SPIRIT_DRAIN)
        {
            DoCastSpellIfCan(m_creature, aZuljinPhases[m_uiPhase].uiSpiritSpellId);
            DoScriptText(aZuljinPhases[m_uiPhase].iYellId, m_creature);
            DoScriptText(aZuljinPhases[m_uiPhase].iEmoteId, m_creature);

            // in eagle phase we don't move
            if (m_uiPhase != PHASE_EAGLE)
            {
                SetCombatMovement(true);
                if (m_creature->getVictim())
                {
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                }
            }
            // In Eagle phase we just cast Energy storm and summon 4 Feather cyclones; Boss doesn't move in this phase
            else
            {
                DoCastSpellIfCan(m_creature, SPELL_ENERGY_STORM, CAST_TRIGGERED);

                // summon 4 vortexes
                for (uint8 i = 0; i < MAX_VORTEXES; ++i)
                    DoCastSpellIfCan(m_creature, SPELL_SUMMON_CYCLONE, CAST_TRIGGERED);
            }

            m_bIsInTransition = false;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() || m_bIsInTransition)
            return;

        if (m_creature->GetHealthPercent() < m_uiHealthCheck && !m_creature->IsNonMeleeSpellCasted(false))
        {
            m_uiHealthCheck -= 20;
            m_bIsInTransition = true;

            SetCombatMovement(false);
            m_creature->GetMotionMaster()->MovePoint(POINT_ID_CENTER, fZuljinMoveLoc[0], fZuljinMoveLoc[1], fZuljinMoveLoc[2]);

            // Despawn vortexes and remvoe the energy storm after eagle phase is complete
            if (m_uiPhase == PHASE_EAGLE)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_ENERGY_STORM);
                DoDespawnVortexes();
            }

            // Reset threat
            DoResetThreat();

            // don't do this after troll phase
            if (m_uiPhase != PHASE_TROLL)
            {
                if (m_creature->HasAura(aZuljinPhases[m_uiPhase].uiSpiritSpellId))
                    m_creature->RemoveAurasDueToSpell(aZuljinPhases[m_uiPhase].uiSpiritSpellId);

                // drain spirit
                if (Creature* pSpirit = m_pInstance->GetSingleCreatureFromStorage(aZuljinPhases[m_uiPhase].uiSpiritId))
                {
                    pSpirit->InterruptNonMeleeSpells(false);
                    pSpirit->CastSpell(m_creature, SPELL_SPIRIT_DRAINED, false);
                    pSpirit->SetStandState(UNIT_STAND_STATE_DEAD);
                }
            }
        }

        switch (m_uiPhase)
        {
            case PHASE_TROLL:

                if(m_uiWhirlwindTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_WHIRLWIND) == CAST_OK)
                        m_uiWhirlwindTimer = urand(15000, 20000);
                }
                else
                    m_uiWhirlwindTimer -= uiDiff;

                if(m_uiGrievousThrowTimer < uiDiff)
                {
                    if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        if (DoCastSpellIfCan(pTarget, SPELL_GRIEVOUS_THROW) == CAST_OK)
                            m_uiGrievousThrowTimer = 10000;
                    }
                }
                else
                    m_uiGrievousThrowTimer -= uiDiff;

                break;
            case PHASE_BEAR:
            {
                if(m_uiParalysisTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_CREEPING_PARALYSIS) == CAST_OK)
                        m_uiParalysisTimer = 27000;
                }
                else
                    m_uiParalysisTimer -= uiDiff;

                if (m_uiOverpowerTimer > 0)
                    m_uiOverpowerTimer -= uiDiff;

                if (!m_creature->getVictim())
                    break;

                uint32 uiTargetHealthTemp = m_creature->getVictim()->GetHealth();

                if (!DoMeleeAttackIfReady())
                    break;

                if (m_uiOverpowerTimer > 0)
                    break;

                if (m_creature->getVictim() && m_creature->getVictim()->GetHealth() == uiTargetHealthTemp)
                {
                    DoCast(m_creature->getVictim(), SPELL_OVERPOWER, false);
                    m_uiOverpowerTimer = 5000; // 5 sec cooldown
                }
                return; // Prevent double DoMeleeAttackIfReady()
            }
            case PHASE_EAGLE:
                // Nothing here; Spells casted just once at the beginning of the phase;
                break;
            case PHASE_LYNX:
                if (m_uiClawRageTimer <= uiDiff)
                {
                    Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);
                    if (!pTarget)
                        pTarget = m_creature->getVictim(); // for solo fight !
                    if (!pTarget) {EnterEvadeMode();return;}
                    m_uiClawRageVictimGUID = pTarget->GetObjectGuid();
                    m_creature->getThreatManager().addThreat(pTarget, 500000.0f);  // for nice graphical orientation and less scripting
                    if (pTarget != m_creature->getVictim())
                    {
                        m_creature->GetMotionMaster()->MoveChase(pTarget);
                        m_creature->CastSpell(pTarget, SPELL_CLAW_RAGE_HASTE, true);
                    }
                    m_uiClawRageIntervalTimer = 1000; // 1sec wait before starting cast SPELL_CLAW_RAGE_DAMAGE
                    m_uiClawRageCounter = 0;
                    m_uiClawRageFinished = false;
                    m_uiClawRageTimer = 40000; //max timer
                    m_uiLynxRushTimer = urand(10000, 20000);
                }else m_uiClawRageTimer -= uiDiff;

                if (!m_uiClawRageFinished)
                {
                    if (m_uiClawRageIntervalTimer <= uiDiff)
                    {
                        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLAW_RAGE_DAMAGE) == CAST_OK)
                            m_uiClawRageCounter++;
                        m_uiClawRageIntervalTimer = 500;
                    }else m_uiClawRageIntervalTimer -= uiDiff;

                    if (m_uiClawRageCounter > 11)
                    {
                        if (m_creature->getVictim()->GetObjectGuid() == m_uiClawRageVictimGUID) //Do not subtract threat if random target is dead.
                            m_creature->getThreatManager().addThreat(m_creature->getVictim(), -500000.0f);
                        if (m_creature->HasAura(SPELL_CLAW_RAGE_HASTE))
                            m_creature->RemoveAurasDueToSpell(SPELL_CLAW_RAGE_HASTE); // This aura prevent melee attacking !
                        m_uiClawRageFinished = true;
                    }
                }

                if (m_uiLynxRushTimer <= uiDiff)
                {
                    m_uiLynxRushIntervalTimer = 0;
                    m_uiLynxRushCounter = 0;
                    m_uiLynxRushFinished = false;
                    m_uiLynxRushTimer = 40000; //max timer
                    m_uiClawRageTimer = urand(10000, 20000);
                }else m_uiLynxRushTimer -= uiDiff;

                if (!m_uiLynxRushFinished && m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
                {
                    if (m_uiLynxRushIntervalTimer <= uiDiff)
                    {
                        Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                        if (!pTarget) {EnterEvadeMode();return;}
                        if (CanCast(pTarget, GetSpellStore()->LookupEntry(SPELL_LYNX_RUSH_DAMAGE), true))
                        {
                            if (m_uiLynxRushVictimGUID)
                            {
                                Unit* pPriorTarget = m_creature->GetMap()->GetPlayer(m_uiLynxRushVictimGUID);
                                if (pPriorTarget && pPriorTarget->isAlive())
                                    m_creature->getThreatManager().addThreat(pPriorTarget, -500000.0f); // Undo high threat
                                m_uiLynxRushVictimGUID.Clear();
                            }

                            Unit* pVictim = m_creature->getVictim();
                            if (pTarget != pVictim)
                            {
                                m_uiLynxRushVictimGUID = pTarget->GetObjectGuid();
                                m_creature->getThreatManager().addThreat(pTarget, 500000.0f);  // for nice graphical orientation and less scripting
                                m_creature->AI()->AttackStart(pTarget);
                            }

                            m_creature->CastSpell(pTarget, SPELL_LYNX_RUSH_DAMAGE, true);
                            m_uiLynxRushCounter++;

                            if (m_uiLynxRushCounter > 8)
                            {
                                if (m_uiLynxRushVictimGUID)
                                {
                                    Unit* pPriorTarget = m_creature->GetMap()->GetPlayer(m_uiLynxRushVictimGUID);
                                    if (pPriorTarget && pPriorTarget->isAlive())
                                        m_creature->getThreatManager().addThreat(pPriorTarget, -500000.0f); // Undo high threat
                                    m_uiLynxRushVictimGUID.Clear();
                                }
                                m_uiLynxRushFinished = true;
                            }

                            m_uiLynxRushIntervalTimer = 500;
                        }
                    }
                    else
                        m_uiLynxRushIntervalTimer -= uiDiff;
                }

                if (!m_uiClawRageFinished && !m_uiLynxRushFinished)
                    return; // Prevent melee attacking when casting spell
                break;
            case PHASE_DRAGONHAWK:

                if(m_uiFlameWhirlTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_FLAME_WHIRL) == CAST_OK)
                        m_uiFlameWhirlTimer = urand(15000, 20000);
                }
                else
                    m_uiFlameWhirlTimer -= uiDiff;

                if(m_uiPillarOfFireTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_SUMMON_PILLAR) == CAST_OK)
                        m_uiPillarOfFireTimer = 10000;
                }
                else
                    m_uiPillarOfFireTimer -= uiDiff;

                if(m_uiFlameBreathTimer < uiDiff)
                {
                    if(Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        if (DoCastSpellIfCan(m_creature, SPELL_FLAME_BREATH) == CAST_OK)
                            m_uiFlameBreathTimer = urand(2000, 10000);
                    }
                }
                else
                    m_uiFlameBreathTimer -= uiDiff;

                break;
        }

        DoMeleeAttackIfReady();
    }

    void InitializeGuards()
    {
        //not if m_creature are dead, so avoid
        if (!m_creature->isAlive())
            return;
        int8 LeftOrRight = 1;
        //summon guards
        for(uint8 i = 0; i < MAX_GUARDS; ++i)
        {
            LeftOrRight *= -1;
            Creature* pGuard = NULL;
            if (!m_uiGuardGUIDs[i].IsEmpty())
            {
                if (m_creature->GetMap()->GetCreature(m_uiGuardGUIDs[i]))
                    continue;
            }
            if (pGuard = m_creature->SummonCreature(NPC_AMANISHI_SAVAGE, GUARD_POS_X_AVERAGE+(GUARD_SPACE*(i+5)*LeftOrRight), GUARD_POS_Y, GUARD_POS_Z, GUARD_ORIENT, TEMPSUMMON_CORPSE_DESPAWN, 0))
                m_uiGuardGUIDs[i] = pGuard->GetObjectGuid();
        }
    }
 
    void AddTreatGuards(Unit* pWho)
    {
        if (!pWho)
            return;
        for(uint8 i = 0; i < MAX_GUARDS; ++i)
        {
            Creature* pGuard = NULL;
            if (!m_uiGuardGUIDs[i].IsEmpty())
                if (pGuard = m_creature->GetMap()->GetCreature(m_uiGuardGUIDs[i]))
                    if (pGuard->isAlive())
                        pGuard->AddThreat(pWho);
        }
    }
};

CreatureAI* GetAI_boss_zuljin(Creature* pCreature)
{
    return new boss_zuljinAI(pCreature);
}
 
struct MANGOS_DLL_DECL mob_zuljin_vortexAI : public ScriptedAI
{
    mob_zuljin_vortexAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (pWho->GetTypeId() != TYPEID_PLAYER)
            return;
        if (m_creature->GetDistance(pWho)<=4.0f)
            AttackStart(pWho);
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (caster->GetTypeId() != TYPEID_PLAYER)
            return;
        if (spell->Id == SPELL_ZAP_INFORM)
        {
            AttackStart(caster);
            m_creature->CastSpell(caster, SPELL_ZAP_DAMAGE, true);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
            m_creature->GetMotionMaster()->MovePoint(0, urand(100, 140), urand(696, 730), 45.111477f);
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, false))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);
        }
    }
};

CreatureAI* GetAI_mob_zuljin_vortex(Creature* pCreature)
{
    return new mob_zuljin_vortexAI(pCreature);
}

struct MANGOS_DLL_DECL mob_zuljin_column_of_fireAI : public ScriptedAI
{
    mob_zuljin_column_of_fireAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (pWho->GetTypeId() != TYPEID_PLAYER && pWho->GetOwner() && pWho->GetOwner()->GetTypeId() != TYPEID_PLAYER)
            return;
        if (m_creature->GetDistance(pWho)<=4.0f)
            AttackStart(pWho);
    }

    void UpdateAI(const uint32 uiDiff){}

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, false))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);
        }
    }
};

CreatureAI* GetAI_mob_zuljin_column_of_fire(Creature* pCreature)
{
    return new mob_zuljin_column_of_fireAI(pCreature);
}

void AddSC_boss_zuljin()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_zuljin";
    pNewScript->GetAI = &GetAI_boss_zuljin;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_zuljin_vortex";
    pNewScript->GetAI = &GetAI_mob_zuljin_vortex;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_zuljin_column_of_fire";
    pNewScript->GetAI = &GetAI_mob_zuljin_column_of_fire;
    pNewScript->RegisterSelf();
}
