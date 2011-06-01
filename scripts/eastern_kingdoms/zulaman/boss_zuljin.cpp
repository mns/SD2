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

    // Troll Form
    SPELL_WHIRLWIND                 = 17207,
    SPELL_GRIEVOUS_THROW            = 43093,                //removes debuff after full healed

    // Bear Form
    SPELL_CREEPING_PARALYSIS        = 43095,                //should cast on the whole raid
    SPELL_OVERPOWER                 = 43456,                //use after melee attack dodged

    // Eagle Form
    SPELL_ENERGY_STORM              = 43983,                //enemy area aura, trigger 42577
    SPELL_ZAP_INFORM                = 42577,
    SPELL_ZAP_DAMAGE                = 43137,                //1250 damage
    SPELL_SUMMON_CYCLONE            = 43112,                //summon four feather vortex
    CREATURE_FEATHER_VORTEX         = 24136,
    SPELL_CYCLONE_VISUAL            = 43119,                //trigger 43147 visual
    SPELL_CYCLONE_PASSIVE           = 43120,                //trigger 43121 (4y aoe) every second

    // Lynx Form
    SPELL_CLAW_RAGE_HASTE           = 42583,
    SPELL_CLAW_RAGE_TRIGGER         = 43149,                // TODO: Need core fix for direct use (this so cast 43150 too self!)
    SPELL_CLAW_RAGE_DAMAGE          = 43150,
    SPELL_LYNX_RUSH_HASTE           = 43152,
    SPELL_LYNX_RUSH_DAMAGE          = 43153,

    // Dragonhawk Form
    SPELL_FLAME_WHIRL               = 43213,                //trigger two spells
    SPELL_FLAME_BREATH              = 43215,
    SPELL_SUMMON_PILLAR             = 43216,                //summon 24187
    CREATURE_COLUMN_OF_FIRE         = 24187,
    SPELL_PILLAR_TRIGGER            = 43218,                //trigger 43217

    // Cosmetic
    SPELL_SPIRIT_AURA               = 42466,
    SPELL_SIPHON_SOUL               = 43501,

    // Transforms
    SPELL_SHAPE_OF_THE_BEAR         = 42594,
    SPELL_SHAPE_OF_THE_EAGLE        = 42606,
    SPELL_SHAPE_OF_THE_LYNX         = 42607,
    SPELL_SHAPE_OF_THE_DRAGONHAWK   = 42608,

    SPELL_BERSERK                   = 45078,

    WEAPON_ID                       = 33975,

    NPC_AMANISHI_SAVAGE             = 23889,
    MAX_GUARDS                      = 8
};

//coords for going for changing form
const float CENTER_X = 120.148811f;
const float CENTER_Y = 703.713684f;
const float CENTER_Z = 45.111477f;

//Guards starting positions in left hand of Boss
const float GUARD_POS_X_AVERAGE       = 119.5f;
const float GUARD_POS_Y               = 688.175f;
const float GUARD_POS_Z               = 45.1115f;
const float GUARD_ORIENT              = 1.580600f;
const float GUARD_SPACE               = 1.5f;

enum Phases
{
    PHASE_TROLL,
    PHASE_BEAR,
    PHASE_EAGLE,
    PHASE_LYNX,
    PHASE_DRAGONHAWK
};

struct TransformFields
{
    int32  say;
    uint32 spell;
};

static TransformFields Transform[4] =
{
    {SAY_BEAR_TRANSFORM, SPELL_SHAPE_OF_THE_BEAR},
    {SAY_EAGLE_TRANSFORM, SPELL_SHAPE_OF_THE_EAGLE},
    {SAY_LYNX_TRANSFORM, SPELL_SHAPE_OF_THE_LYNX},
    {SAY_DRAGONHAWK_TRANSFORM, SPELL_SHAPE_OF_THE_DRAGONHAWK}
};

struct SpiritInfoFields
{
    uint32 entry;
    float  x, y, z, orient;
};

static SpiritInfoFields SpiritInfo[4] =
{
    {23878, 137.23f, 725.98f, 45.11f, 3.71f}, //Amani Bear Spirit
    {23880, 104.29f, 726.43f, 45.11f, 5.43f}, //Amani Eagle Spirit
    {23877, 147.87f, 706.51f, 45.11f, 3.04f}, //Amani Lynx Spirit
    {23879, 88.950f, 705.49f, 45.11f, 6.11f}  //Amani Dragonhawk Spirit
};

struct MANGOS_DLL_DECL boss_zuljinAI : public ScriptedAI
{
    boss_zuljinAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    ObjectGuid m_auiSpiritGUIDs[4];
    ObjectGuid m_auiGuardGUIDs[MAX_GUARDS];
    GUIDList m_uiFeatherVortexGUIDs;
    GUIDList m_uiColumnOfFireGUIDs;

    uint8  m_uiPhase;
    bool   m_uiTransforming;
    uint32 m_uiWhirlwindTimer;
    uint32 m_uiTransformTimer;
    uint8  m_uiTransformParts;
    uint32 m_uiGrievousThrowTimer;
    uint32 m_uiCreepingParalysisTimer;
    uint32 m_uiOverpowerTimer;
    uint32 m_uiClawRageTimer;
    uint32 m_uiClawRageIntervalTimer;
    uint8  m_uiClawRageCounter;
    bool   m_uiClawRageFinished;
    uint64 m_uiClawRageVictimGUID;
    uint32 m_uiLynxRushTimer;
    bool   m_uiLynxRushFinished;
    uint32 m_uiLynxRushIntervalTimer;
    uint8  m_uiLynxRushCounter;
    uint64 m_uiLynxRushVictimGUID;
    uint32 m_uiFilameWhirlTimer;
    uint32 m_uiFilameBreathTimer;
    uint32 m_uiSummonPillarTimer;


    void Reset()
    {
        InitializeSpirits();
        DespawnFeatherVortexs();
        DespawnColumnOfFires();

        m_uiPhase = PHASE_TROLL;
        m_uiTransforming = false;
        m_uiWhirlwindTimer = urand(10000,20000);
        m_uiGrievousThrowTimer = 5000;
        m_uiCreepingParalysisTimer = 5000;
        m_uiOverpowerTimer = 0;
        m_uiClawRageTimer = urand(10000, 15000);
        m_uiLynxRushTimer = 40000; //max timer
        m_uiLynxRushVictimGUID = 0;
        m_uiClawRageFinished = true;
        m_uiLynxRushFinished = true;
        m_uiFilameWhirlTimer = urand(15000, 20000);
        m_uiFilameBreathTimer = m_uiFilameWhirlTimer+5000;
        m_uiSummonPillarTimer = 15000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ZULJIN, IN_PROGRESS);

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
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_KILL1 : SAY_KILL2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DespawnColumnOfFires();

        DoScriptText(SAY_DEATH, m_creature);

        if (!m_pInstance)
            return;

        if (Creature* pSpirit = m_creature->GetMap()->GetCreature(m_auiSpiritGUIDs[3]))
            pSpirit->SetStandState(UNIT_STAND_STATE_DEAD);

        m_pInstance->SetData(TYPE_ZULJIN, DONE);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == CREATURE_FEATHER_VORTEX)
            m_uiFeatherVortexGUIDs.push_back(pSummoned->GetGUID());

        if (pSummoned->GetEntry() == CREATURE_COLUMN_OF_FIRE)
            m_uiColumnOfFireGUIDs.push_back(pSummoned->GetGUID());
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //wait if already casting
        if (!m_creature->IsNonMeleeSpellCasted(false))
             ChangePhaseIfNeed();

        if (m_uiTransforming)
        {
            if (m_uiTransformTimer > diff)
            {
                m_uiTransformTimer -= diff;
                return;
            }

            switch(m_uiTransformParts)
            {
                case 0:
                    if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE) // Moving to center
                    {
                        m_uiTransformParts++;
                        m_uiTransformTimer = 1000;
                    }
                break;
                case 1:
                    if (Creature* pSpirit = m_creature->GetMap()->GetCreature(m_auiSpiritGUIDs[m_uiPhase-1]))
                    {
                        m_creature->SetInFront(pSpirit);
                        pSpirit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); // For can cast siphon soul
                        m_creature->CastSpell(pSpirit, SPELL_SIPHON_SOUL, true);
                        pSpirit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    }
                    DoScriptText(Transform[m_uiPhase-1].say, m_creature);
                    m_uiTransformTimer = 2000;
                    m_uiTransformParts++;
                break;
                case 2:
                    m_creature->CastSpell(m_creature, Transform[m_uiPhase-1].spell, false);
                    m_uiTransformTimer = 1000;
                    m_uiTransformParts++;
                break;
                case 3:
                    DoResetThreat();
                    m_uiTransforming = false;
                    if (m_uiPhase == PHASE_EAGLE)
                    {
                        m_creature->CastSpell(m_creature, SPELL_ENERGY_STORM, true);
                        m_creature->CastSpell(m_creature, SPELL_SUMMON_CYCLONE, true);
                    }
                    else
                    {
                        Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                        if (!pTarget) {EnterEvadeMode();return;}
                        m_creature->GetMotionMaster()->MoveChase(pTarget);
                        AttackStart(pTarget);
                    }
                break;
            }
            return;
        }

        switch(m_uiPhase)
        {
            case PHASE_TROLL:
                if (m_uiWhirlwindTimer <= diff)
                {
                    DoCast(m_creature, SPELL_WHIRLWIND);
                    m_uiWhirlwindTimer = 10000 + urand(0,20000);
                }else m_uiWhirlwindTimer -= diff;

                if (m_uiGrievousThrowTimer <= diff)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        DoCast(pTarget, SPELL_GRIEVOUS_THROW, false);
                    m_uiGrievousThrowTimer = 10000;
                }else m_uiGrievousThrowTimer -= diff;

                DoMeleeAttackIfReady();
            break;
            case PHASE_BEAR:
            {
                if (m_uiCreepingParalysisTimer <= diff)
                {
                    DoCast(m_creature, SPELL_CREEPING_PARALYSIS);
                    m_uiCreepingParalysisTimer = 20000;
                }else m_uiCreepingParalysisTimer -= diff;

                if (m_uiOverpowerTimer > 0)
                    m_uiOverpowerTimer -= diff;

                if (!m_creature->getVictim())
                    break;

                uint32 TargetHealthTemp = m_creature->getVictim()->GetHealth();

                if (!DoMeleeAttackIfReady())
                    break;

                if (m_uiOverpowerTimer > 0)
                    break;

                if (m_creature->getVictim() && m_creature->getVictim()->GetHealth() == TargetHealthTemp)
                {
                    DoCast(m_creature->getVictim(), SPELL_OVERPOWER, false);
                    m_uiOverpowerTimer = 5000; // 5 sec cooldown
                }
            }
            break;
            case PHASE_LYNX:
                if (m_uiClawRageTimer <= diff)
                {
                    Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);
                    if (!pTarget)
                        pTarget = m_creature->getVictim(); // for solo fight !
                    if (!pTarget) {EnterEvadeMode();return;}
                    m_uiClawRageVictimGUID = pTarget->GetGUID();
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
                }else m_uiClawRageTimer -= diff;

                if (!m_uiClawRageFinished)
                {
                    if (m_uiClawRageIntervalTimer <= diff)
                    {
                        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLAW_RAGE_DAMAGE) == CAST_OK)
                            m_uiClawRageCounter++;
                        m_uiClawRageIntervalTimer = 500;
                    }else m_uiClawRageIntervalTimer -= diff;

                    if (m_uiClawRageCounter > 11)
                    {
                        if (m_creature->getVictim()->GetGUID() == m_uiClawRageVictimGUID) //Do not subtract threat if random target is dead.
                            m_creature->getThreatManager().addThreat(m_creature->getVictim(), -500000.0f);
                        if (m_creature->HasAura(SPELL_CLAW_RAGE_HASTE))
                            m_creature->RemoveAurasDueToSpell(SPELL_CLAW_RAGE_HASTE); // This aura prevent melee attacking !
                        m_uiClawRageFinished = true;
                    }
                }

                if (m_uiLynxRushTimer <= diff)
                {
                    m_uiLynxRushIntervalTimer = 0;
                    m_uiLynxRushCounter = 0;
                    m_uiLynxRushFinished = false;
                    m_uiLynxRushTimer = 40000; //max timer
                    m_uiClawRageTimer = urand(10000, 20000);
                }else m_uiLynxRushTimer -= diff;

                if (!m_uiLynxRushFinished && m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
                {
                    if (m_uiLynxRushIntervalTimer <= diff)
                    {
                        Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                        if (!pTarget) {EnterEvadeMode();return;}
                        if (CanCast(pTarget, GetSpellStore()->LookupEntry(SPELL_LYNX_RUSH_DAMAGE), true))
                        {
                            if (m_uiLynxRushVictimGUID)
                            {
                                Unit* PriorTarget = m_creature->GetMap()->GetPlayer(m_uiLynxRushVictimGUID);
                                if (PriorTarget && PriorTarget->isAlive())
                                    m_creature->getThreatManager().addThreat(PriorTarget, -500000.0f); // Undo high threat
                                m_uiLynxRushVictimGUID = 0;
                            }

                            Unit* pVictim = m_creature->getVictim();
                            if (pTarget != pVictim)
                            {
                                m_uiLynxRushVictimGUID = pTarget->GetGUID();
                                m_creature->getThreatManager().addThreat(pTarget, 500000.0f);  // for nice graphical orientation and less scripting
                                m_creature->AI()->AttackStart(pTarget);
                            }

                            m_creature->CastSpell(pTarget, SPELL_LYNX_RUSH_DAMAGE, true);
                            m_uiLynxRushCounter++;

                            if (m_uiLynxRushCounter > 8)
                            {
                                if (m_uiLynxRushVictimGUID)
                                {
                                    Unit* PriorTarget = m_creature->GetMap()->GetPlayer(m_uiLynxRushVictimGUID);
                                    if (PriorTarget && PriorTarget->isAlive())
                                        m_creature->getThreatManager().addThreat(PriorTarget, -500000.0f); // Undo high threat
                                    m_uiLynxRushVictimGUID = 0;
                                }
                                m_uiLynxRushFinished = true;
                            }

                            m_uiLynxRushIntervalTimer = 500;
                        }
                    }else m_uiLynxRushIntervalTimer -= diff;
                }

                if (m_uiClawRageFinished && m_uiLynxRushFinished)
                    DoMeleeAttackIfReady();
            break;
            case PHASE_DRAGONHAWK:
                if (m_uiFilameWhirlTimer <= diff)
                {
                    m_creature->CastSpell(m_creature, SPELL_FLAME_WHIRL, false);
                    m_uiFilameWhirlTimer = urand(15000, 20000);
                }else m_uiFilameWhirlTimer -= diff;

                if (m_uiFilameBreathTimer <= diff)
                {
                    m_creature->CastSpell(m_creature->getVictim(), SPELL_FLAME_BREATH, true);
                    m_uiFilameBreathTimer = urand(2000, 10000);
                }else m_uiFilameBreathTimer -= diff;

                if (m_uiSummonPillarTimer <= diff)
                {
                    m_creature->CastSpell(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_SUMMON_PILLAR, true);
                    m_uiSummonPillarTimer = 10000;
                }else m_uiSummonPillarTimer -= diff;

                DoMeleeAttackIfReady();
            break;
        }
    }

    void ChangePhaseIfNeed()
    {
        if (m_uiPhase == PHASE_DRAGONHAWK)
            return;

        if (m_creature->GetHealthPercent() > (4 - m_uiPhase) * 20.0f)
            return;

        m_uiTransforming = true;
        m_uiTransformParts = 0;
        m_uiTransformTimer = 0;

        if (Creature* pSpirit = m_creature->GetMap()->GetCreature(m_auiSpiritGUIDs[m_uiPhase-1]))
            pSpirit->SetStandState(UNIT_STAND_STATE_DEAD);

        if (m_uiPhase != PHASE_TROLL)
            m_creature->RemoveAurasDueToSpell(Transform[m_uiPhase - 1].spell);

        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(0, CENTER_X, CENTER_Y, CENTER_Z);

        m_uiPhase++;

        if (m_uiPhase == PHASE_LYNX)
        {
            m_creature->RemoveAurasDueToSpell(SPELL_ENERGY_STORM);
            DespawnFeatherVortexs();
        }
    }

    void InitializeSpirits()
    {
        //not if m_creature are dead, so avoid
        if (!m_creature->isAlive())
            return;

        //summon or revive mobs from the list
        for(uint8 i = 0; i < 4; ++i)
        {
            Creature* pSpirit = NULL;
            if (pSpirit = m_creature->GetMap()->GetCreature(m_auiSpiritGUIDs[i]))
            {
                // revive
                if (pSpirit->getStandState() == UNIT_STAND_STATE_DEAD)
                    pSpirit->SetStandState(UNIT_STAND_STATE_STAND);
                continue;
            }
            if (pSpirit = m_creature->SummonCreature(SpiritInfo[i].entry, SpiritInfo[i].x, SpiritInfo[i].y, SpiritInfo[i].z, SpiritInfo[i].orient, TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                m_auiSpiritGUIDs[i] = pSpirit->GetObjectGuid();
                pSpirit->CastSpell(pSpirit, SPELL_SPIRIT_AURA, true);
                pSpirit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }
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
            if (!m_auiGuardGUIDs[i].IsEmpty())
            {
                if (m_creature->GetMap()->GetCreature(m_auiGuardGUIDs[i]))
                    continue;
            }
            if (pGuard = m_creature->SummonCreature(NPC_AMANISHI_SAVAGE, GUARD_POS_X_AVERAGE+(GUARD_SPACE*(i+5)*LeftOrRight), GUARD_POS_Y, GUARD_POS_Z, GUARD_ORIENT, TEMPSUMMON_CORPSE_DESPAWN, 0))
                m_auiGuardGUIDs[i] = pGuard->GetObjectGuid();
        }
    }

    void AddTreatGuards(Unit* pWho)
    {
        if (!pWho)
            return;
        for(uint8 i = 0; i < MAX_GUARDS; ++i)
        {
            Creature* pGuard = NULL;
            if (!m_auiGuardGUIDs[i].IsEmpty())
                if (pGuard = m_creature->GetMap()->GetCreature(m_auiGuardGUIDs[i]))
                    if (pGuard->isAlive())
                        pGuard->AddThreat(pWho);
        }
    }

    void DespawnFeatherVortexs()
    {
        for(GUIDList::iterator itr = m_uiFeatherVortexGUIDs.begin(); itr != m_uiFeatherVortexGUIDs.end(); ++itr)
        {
            if (Creature* pFeatherVortex = m_creature->GetMap()->GetCreature((*itr)))
                pFeatherVortex->ForcedDespawn();
        }
        m_uiFeatherVortexGUIDs.clear();
    }

    void DespawnColumnOfFires()
    {
        for(GUIDList::iterator itr = m_uiColumnOfFireGUIDs.begin(); itr != m_uiColumnOfFireGUIDs.end(); ++itr)
        {
            if (Creature* pColumnOfFire = m_creature->GetMap()->GetCreature((*itr)))
                pColumnOfFire->ForcedDespawn();
        }
        m_uiColumnOfFireGUIDs.clear();
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
        m_creature->CastSpell(m_creature, SPELL_CYCLONE_PASSIVE, true);
        m_creature->CastSpell(m_creature, SPELL_CYCLONE_VISUAL, true);
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
            m_creature->GetMotionMaster()->MovePoint(0, urand(100, 140), urand(696, 730), CENTER_Z);
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
        m_creature->CastSpell(m_creature, SPELL_PILLAR_TRIGGER, true);
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
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_zuljin";
    newscript->GetAI = &GetAI_boss_zuljin;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_zuljin_vortex";
    newscript->GetAI = &GetAI_mob_zuljin_vortex;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_zuljin_column_of_fire";
    newscript->GetAI = &GetAI_mob_zuljin_column_of_fire;
    newscript->RegisterSelf();
}
