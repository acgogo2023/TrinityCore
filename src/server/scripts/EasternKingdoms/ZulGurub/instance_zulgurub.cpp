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

#include "zulgurub.h"
#include "Creature.h"
#include "InstanceScript.h"
#include "ScriptMgr.h"

DoorData const doorData[] =
{
    { GO_VENOXIS_COIL,                  DATA_VENOXIS,   EncounterDoorBehavior::OpenWhenNotInProgress },
    { GO_ARENA_DOOR_1,                  DATA_MANDOKIR,  EncounterDoorBehavior::OpenWhenNotInProgress },
    { GO_FORCEFIELD,                    DATA_KILNARA,   EncounterDoorBehavior::OpenWhenNotInProgress },
    { GO_ZANZIL_DOOR,                   DATA_ZANZIL,    EncounterDoorBehavior::OpenWhenNotInProgress },
    //{ GO_THE_CACHE_OF_MADNESS_DOOR,     DATA_xxxxxxx,   EncounterStateForOpenDoor::NotInProgress },
    { 0,                                0,              EncounterDoorBehavior::OpenWhenNotInProgress }
};

DungeonEncounterData const encounters[] =
{
    { DATA_VENOXIS, {{ 1178 }} },
    { DATA_MANDOKIR, {{ 1179 }} },
    { DATA_KILNARA, {{ 1180 }} },
    { DATA_ZANZIL, {{ 1181 }} },
    { DATA_JINDO, {{ 1182 }} },
    { DATA_HAZZARAH, {{ 1188 }} },
    { DATA_RENATAKI, {{ 1188 }} },
    { DATA_WUSHOOLAY, {{ 1188 }} },
    { DATA_GRILEK, {{ 1188 }} }
};

class instance_zulgurub : public InstanceMapScript
{
    public:
        instance_zulgurub() : InstanceMapScript(ZGScriptName, 859) { }

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetHeaders(DataHeader);
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
                LoadDungeonEncounterData(encounters);
            }

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                    case NPC_VENOXIS:
                        venoxisGUID = creature->GetGUID();
                        break;
                    case NPC_MANDOKIR:
                        mandokirGUID = creature->GetGUID();
                        break;
                    case NPC_KILNARA:
                        kilnaraGUID = creature->GetGUID();
                        break;
                    case NPC_ZANZIL:
                        zanzilGUID = creature->GetGUID();
                        break;
                    case NPC_JINDO:
                        jindoGUID = creature->GetGUID();
                        break;
                    case NPC_HAZZARAH:
                        hazzarahGUID = creature->GetGUID();
                        break;
                    case NPC_RENATAKI:
                        renatakiGUID = creature->GetGUID();
                        break;
                    case NPC_WUSHOOLAY:
                        wushoolayGUID = creature->GetGUID();
                        break;
                    case NPC_GRILEK:
                        grilekGUID = creature->GetGUID();
                        break;
                    case NPC_JINDO_TRIGGER:
                        jindoTiggerGUID = creature->GetGUID();
                        break;
                    default:
                        break;
                }
            }

            bool SetBossState(uint32 type, EncounterState state) override
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_VENOXIS:
                    case DATA_MANDOKIR:
                    case DATA_KILNARA:
                    case DATA_ZANZIL:
                    case DATA_JINDO:
                    case DATA_HAZZARAH:
                    case DATA_RENATAKI:
                    case DATA_WUSHOOLAY:
                    case DATA_GRILEK:
                        break;
                    default:
                        break;
                }

                return true;
            }

            /*
            void SetData(uint32 type, uint32 data) override
            {
                switch (type)
                {
                }
            }

            uint32 GetData(uint32 type) const override
            {
                switch (type)
                {
                }

                return 0;
            }
            */

            ObjectGuid GetGuidData(uint32 type) const override
            {
                switch (type)
                {
                    case DATA_VENOXIS:
                        return venoxisGUID;
                    case DATA_MANDOKIR:
                        return mandokirGUID;
                    case DATA_KILNARA:
                        return kilnaraGUID;
                    case DATA_ZANZIL:
                        return zanzilGUID;
                    case DATA_JINDO:
                        return jindoGUID;
                    case DATA_HAZZARAH:
                        return hazzarahGUID;
                    case DATA_RENATAKI:
                        return renatakiGUID;
                    case DATA_WUSHOOLAY:
                        return wushoolayGUID;
                    case DATA_GRILEK:
                        return grilekGUID;
                    case DATA_JINDOR_TRIGGER:
                        return jindoTiggerGUID;
                    default:
                        break;
                }

                return ObjectGuid::Empty;
            }

        protected:
            ObjectGuid venoxisGUID;
            ObjectGuid mandokirGUID;
            ObjectGuid kilnaraGUID;
            ObjectGuid zanzilGUID;
            ObjectGuid jindoGUID;
            ObjectGuid hazzarahGUID;
            ObjectGuid renatakiGUID;
            ObjectGuid wushoolayGUID;
            ObjectGuid grilekGUID;
            ObjectGuid jindoTiggerGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();
}
