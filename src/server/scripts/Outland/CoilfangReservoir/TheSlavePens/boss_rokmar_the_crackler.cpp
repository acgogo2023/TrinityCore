/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: boss_rokmar_the_crackler
SD%Complete: 100%
SDComment:
SDCategory: Coilfang Reservoir, The Slave Pens
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "the_slave_pens.h"

enum Spells
{
    SPELL_GRIEVOUS_WOUND            = 31956,
    SPELL_ENSNARING_MOSS            = 31948,
    SPELL_WATER_SPIT                = 35008,
    SPELL_FRENZY                    = 34970
};

enum Events
{
    EVENT_GRIEVOUS_WOUND            = 1,
    EVENT_ENSNARING_MOSS            = 2,
    EVENT_WATER_SPIT                = 3
};

struct boss_rokmar_the_crackler : public BossAI
{
    boss_rokmar_the_crackler(Creature* creature) : BossAI(creature, DATA_ROKMAR_THE_CRACKLER)
    {
        Initialize();
    }

    void Initialize()
    {
        rokmarFrenzy = false;
    }

    void Reset() override
    {
        _Reset();
        Initialize();
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
    }

    void JustEngagedWith(Unit* who) override
    {
        BossAI::JustEngagedWith(who);
        events.ScheduleEvent(EVENT_GRIEVOUS_WOUND, 10s);
        events.ScheduleEvent(EVENT_ENSNARING_MOSS, 20s);
        events.ScheduleEvent(EVENT_WATER_SPIT, 14s);
    }

    void KilledUnit(Unit* /*victim*/) override { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_GRIEVOUS_WOUND:
                    DoCastVictim(SPELL_GRIEVOUS_WOUND, true);
                    events.ScheduleEvent(EVENT_GRIEVOUS_WOUND, 20s, 30s);
                    break;
                case EVENT_ENSNARING_MOSS:
                    DoCastAOE(SPELL_ENSNARING_MOSS);
                    events.ScheduleEvent(EVENT_ENSNARING_MOSS, 20s, 30s);
                    break;
                case EVENT_WATER_SPIT:
                    DoCastAOE(SPELL_WATER_SPIT);
                    events.ScheduleEvent(EVENT_WATER_SPIT, 14s, 18s);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (HealthBelowPct(10) && !rokmarFrenzy)
        {
            DoCast(me, SPELL_FRENZY);
            rokmarFrenzy = true;
        }
    }

private:
    bool rokmarFrenzy;
};

void AddSC_boss_rokmar_the_crackler()
{
    RegisterSlavePensCreatureAI(boss_rokmar_the_crackler);
}
