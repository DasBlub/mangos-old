/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
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

#include "config.h"
#include "ScriptMgr.h"
#include "../../game/GossipDef.h"
#include "../../game/GameObject.h"
#include "../../game/Player.h"
#include "../../game/Map.h"
#include "../../game/ObjectMgr.h"

//uint8 loglevel = 0;
std::map<uint32, Script*> m_mScripts;

// -- Scripts to be added --
extern void AddSC_default();
// -------------------

MANGOS_DLL_EXPORT
void ScriptsFree()
{                                                           // Free resources before library unload
    for(std::map<uint32, Script*>::iterator itr = m_mScripts.begin(); itr != m_mScripts.end(); ++itr)
        delete itr->second;
}

MANGOS_DLL_EXPORT
void ScriptsInit()
{
    // -- Initialize the Scripts to be Added --
    AddSC_default();
    // ----------------------------------------

}

inline Script* GetScript(uint32 uiScriptId)
{
    return m_mScripts.find(uiScriptId)->second;
}

MANGOS_DLL_EXPORT
char const* ScriptsVersion()
{
    return "Default MaNGOS scripting library";
}

void Script::registerSelf()
{
    int iId = GetScriptId(sName.c_str());
    if(iId != 0)
        m_mScripts.insert(std::pair<uint32, Script*>(iId, this));
}

MANGOS_DLL_EXPORT
bool GossipHello(Player* pPlayer, Creature* pCreature)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pGossipHello) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGossipHello(pPlayer, pCreature);
}

MANGOS_DLL_EXPORT
bool GossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    debug_log("DEBUG: Gossip selection, sender: %d, action: %d", uiSender, uiAction);

    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pGossipSelect) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGossipSelect(pPlayer, pCreature, uiSender, uiAction);
}

MANGOS_DLL_EXPORT
bool GossipSelectWithCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* sCode)
{
    debug_log("DEBUG: Gossip selection, sender: %d, action: %d", uiSender, uiAction);

    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pGossipSelectWithCode) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGossipSelectWithCode(pPlayer, pCreature, uiSender, uiAction, sCode);
}

MANGOS_DLL_EXPORT
bool QuestAccept(Player* pPlayer, Creature* pCreature, Quest* pQuest)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pQuestAccept) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pQuestAccept(pPlayer, pCreature, pQuest);
}

MANGOS_DLL_EXPORT
bool QuestSelect(Player* pPlayer, Creature* pCreature, Quest* pQuest)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pQuestSelect) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pQuestSelect(pPlayer, pCreature, pQuest);
}

MANGOS_DLL_EXPORT
bool QuestComplete(Player* pPlayer, Creature* pCreature, Quest* pQuest)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pQuestComplete) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pQuestComplete(pPlayer, pCreature, pQuest);
}

MANGOS_DLL_EXPORT
bool ChooseReward(Player* pPlayer, Creature* pCreature, Quest* pQuest, uint32 uiOpt)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pChooseReward) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pChooseReward(pPlayer, pCreature, pQuest, uiOpt);
}

MANGOS_DLL_EXPORT
uint32 NPCDialogStatus(Player* pPlayer, Creature* pCreature)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->pNPCDialogStatus) return 100;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pNPCDialogStatus(pPlayer, pCreature);
}

MANGOS_DLL_EXPORT
uint32 GODialogStatus(Player* pPlayer, GameObject* pGO)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pGO->GetGOInfo()->ScriptId);
    if (!pTmpScript || !pTmpScript->pGODialogStatus) return 100;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGODialogStatus(pPlayer, pGO);
}

MANGOS_DLL_EXPORT
bool ItemHello(Player* pPlayer, Item* pItem, Quest* pQuest)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pItem->GetProto()->ScriptId);
    if (!pTmpScript || !pTmpScript->pItemHello) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pItemHello(pPlayer, pItem, pQuest);
}

MANGOS_DLL_EXPORT
bool ItemQuestAccept(Player* pPlayer, Item* pItem, Quest* pQuest)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pItem->GetProto()->ScriptId);
    if (!pTmpScript || !pTmpScript->pItemQuestAccept) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pItemQuestAccept(pPlayer, pItem, pQuest);
}

MANGOS_DLL_EXPORT
bool GOHello(Player* pPlayer, GameObject* pGO)
{
    Script *pTmpScript = NULL;

    pTmpScript = GetScript(pGO->GetGOInfo()->ScriptId);
    if (!pTmpScript || !pTmpScript->pGOHello) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGOHello(pPlayer, pGO);
}

MANGOS_DLL_EXPORT
bool GOQuestAccept(Player* pPlayer, GameObject* pGO, Quest* pQuest)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pGO->GetGOInfo()->ScriptId);
    if (!pTmpScript || !pTmpScript->pGOQuestAccept) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGOQuestAccept(pPlayer, pGO, pQuest);
}

MANGOS_DLL_EXPORT
bool GOChooseReward(Player* pPlayer, GameObject* pGO, Quest* pQuest, uint32 uiOpt)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pGO->GetGOInfo()->ScriptId);
    if (!pTmpScript || !pTmpScript->pGOChooseReward) return false;

    pPlayer->PlayerTalkClass->ClearMenus();
    return pTmpScript->pGOChooseReward(pPlayer, pGO, pQuest, uiOpt);
}

MANGOS_DLL_EXPORT
bool AreaTrigger(Player* pPlayer, AreaTriggerEntry* pAtEntry)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(GetAreaTriggerScriptId(pAtEntry->id));
    if (!pTmpScript || !pTmpScript->pAreaTrigger) return false;

    return pTmpScript->pAreaTrigger(pPlayer, pAtEntry);
}

MANGOS_DLL_EXPORT
bool ItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& spcTargets)
{
    Script* pTmpScript = NULL;

    pTmpScript = GetScript(pItem->GetProto()->ScriptId);
    if (!pTmpScript || !pTmpScript->pItemUse) return false;

    return pTmpScript->pItemUse(pPlayer, pItem, spcTargets);
}

MANGOS_DLL_EXPORT
CreatureAI* GetAI(Creature* pCreature)
{
    Script* pTmpScript = GetScript(pCreature->GetScriptId());
    if (!pTmpScript || !pTmpScript->GetAI) return NULL;

    return pTmpScript->GetAI(pCreature);
}

MANGOS_DLL_EXPORT
InstanceData* CreateInstanceData(Map* pMap)
{
    if (!pMap->IsDungeon()) return NULL;

    Script* pTmpScript = GetScript(((InstanceMap*)pMap)->GetScriptId());
    if (!pTmpScript || !pTmpScript->GetInstanceData) return NULL;

    return pTmpScript->GetInstanceData(pMap);
}

MANGOS_DLL_EXPORT
bool EffectDummyGameObj(Unit* pCaster, uint32 uiSpellId, uint32 uiEffIndex, GameObject* pGameObjTarget)
{
    Script* pTmpScript = GetScript(pGameObjTarget->GetGOInfo()->ScriptId);
    if (!pTmpScript || !pTmpScript->pEffectDummyGameObj) return false;

    return pTmpScript->pEffectDummyGameObj(pCaster, uiSpellId, uiEffIndex, pGameObjTarget);
}

MANGOS_DLL_EXPORT
bool EffectDummyCreature(Unit* pCaster, uint32 uiSpellId, uint32 uiEffIndex, Creature* pCreatureTarget)
{
    Script* pTmpScript = GetScript(pCreatureTarget->GetScriptId());
    if (!pTmpScript || !pTmpScript->pEffectDummyCreature) return false;

    return pTmpScript->pEffectDummyCreature(pCaster, uiSpellId, uiEffIndex, pCreatureTarget);
}

MANGOS_DLL_EXPORT
bool EffectDummyItem(Unit* pCaster, uint32 uiSpellId, uint32 uiEffIndex, Item* pItemTarget)
{
    Script* pTmpScript = GetScript(pItemTarget->GetProto()->ScriptId);
    if (!pTmpScript || !pTmpScript->pEffectDummyItem) return false;

    return pTmpScript->pEffectDummyItem(pCaster, uiSpellId, uiEffIndex, pItemTarget);
}

void ScriptedAI::UpdateAI(const uint32 uiDiff)
{
    //Check if we have a current target
    if (m_creature->isAlive() && m_creature->SelectHostilTarget() && m_creature->getVictim())
    {
        //If we are within range melee the target
        if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
        {
            if (m_creature->isAttackReady())
            {
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();
            }
        }
    }
}

void ScriptedAI::EnterEvadeMode()
{
    m_creature->CombatStop(true);
    if (m_creature->isAlive())
        DoGoHome();
}

void ScriptedAI::DoStartAttack(Unit* pVictim)
{
    if (m_creature->Attack(pVictim, true))
        m_creature->GetMotionMaster()->MoveChase(pVictim);
}

void ScriptedAI::DoStopAttack()
{
    if (m_creature->getVictim())
        m_creature->AttackStop();
}

void ScriptedAI::DoCast(Unit* pVictim, uint32 uiSpellId)
{
    m_creature->CastSpell(pVictim, uiSpellId, true);
}

void ScriptedAI::DoCastSpell(Unit* pVictim, SpellEntry* pSpellInfo)
{
    m_creature->CastSpell(pVictim, pSpellInfo, true);
}

void ScriptedAI::DoSay(int32 iTextId, uint32 uiLanguage)
{
    m_creature->Say(iTextId, uiLanguage, 0);
}

void ScriptedAI::DoGoHome()
{
    if (!m_creature->getVictim() && m_creature->isAlive())
        m_creature->GetMotionMaster()->MoveTargetedHome();
}
