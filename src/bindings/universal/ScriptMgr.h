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

#ifndef SCRIPTMGR_H
#define SCRIPTMGR_H

//Only required includes
#include "../../game/CreatureAI.h"
#include "../../game/Creature.h"
#include "../../game/InstanceData.h"

class Player;
class Creature;
class Quest;
class Item;
class GameObject;
class SpellCastTargets;
class Map;

#define MAX_SCRIPTS 1000
#define MAX_INSTANCE_SCRIPTS 1000

struct Script
{
public:
    Script() :
        pGossipHello(NULL), pQuestAccept(NULL), pGossipSelect(NULL), pGossipSelectWithCode(NULL),
        pQuestSelect(NULL), pQuestComplete(NULL), pNPCDialogStatus(NULL), pGODialogStatus(NULL), pChooseReward(NULL),
        pItemHello(NULL), pGOHello(NULL), pAreaTrigger(NULL), pItemQuestAccept(NULL), pGOQuestAccept(NULL),
        pGOChooseReward(NULL), pItemUse(NULL), pEffectDummyGameObj(NULL), pEffectDummyCreature(NULL),
        pEffectDummyItem(NULL), GetAI(NULL)
    {}

    std::string sName;

    // -- Quest/gossip Methods to be scripted --
    bool (*pGossipHello         )(Player* pPlayer, Creature* pCreature);
    bool (*pQuestAccept         )(Player* pPlayer, Creature* pCreature, Quest const* pQuest );
    bool (*pGossipSelect        )(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction );
    bool (*pGossipSelectWithCode)(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* sCode );
    bool (*pQuestSelect         )(Player* pPlayer, Creature* pCreature, Quest const* pQuest );
    bool (*pQuestComplete       )(Player* pPlayer, Creature* pCreature, Quest const* pQuest );
    uint32 (*pNPCDialogStatus   )(Player* pPlayer, Creature* pCreature );
    uint32 (*pGODialogStatus    )(Player* pPlayer, GameObject* pGO );
    bool (*pChooseReward        )(Player* pPlayer, Creature* pCreature, Quest const* pQuest, uint32 opt );
    bool (*pItemHello           )(Player* pPlayer, Item* pItem, Quest const* pQuest );
    bool (*pGOHello             )(Player* pPlayer, GameObject* pGO );
    bool (*pAreaTrigger         )(Player* pPlayer, AreaTriggerEntry* pAt);
    bool (*pItemQuestAccept     )(Player* pPlayer, Item* pItem, Quest const*pQuest );
    bool (*pGOQuestAccept       )(Player* pPlayer, GameObject *pGO, Quest const*pQuest );
    bool (*pGOChooseReward      )(Player* pPlayer, GameObject *pGO, Quest const*pQuest, uint32 uiOpt );
    bool (*pItemUse             )(Player* pPlayer, Item* pItem, SpellCastTargets const& spcTargets);
    bool (*pEffectDummyGameObj  )(Unit*, uint32, uint32, GameObject* );
    bool (*pEffectDummyCreature )(Unit*, uint32, uint32, Creature* );
    bool (*pEffectDummyItem     )(Unit*, uint32, uint32, Item* );

    CreatureAI* (*GetAI)(Creature* pCreature);
    InstanceData* (*GetInstanceData)(Map*);
    // -----------------------------------------

    void registerSelf();
};

const float VISIBLE_RANGE = 50.0f;

// Read function descriptions in CreatureAI
class MANGOS_DLL_DECL ScriptedAI : public CreatureAI
{
public:
    explicit ScriptedAI(Creature* pCreature) : CreatureAI(pCreature) {}
    ~ScriptedAI() {}

    // Called at stopping attack by any attacker
    void EnterEvadeMode();

    // Is unit visible for MoveInLineOfSight
    bool IsVisible(Unit* pWho) const
    {
        return !pWho->HasStealthAura() && m_creature->IsWithinDist(pWho, VISIBLE_RANGE);
    }

    // Called at World update tick
    void UpdateAI(const uint32 uiDiff);

    //= Some useful helpers =========================

    // Start attack of victim and go to him
    void DoStartAttack(Unit* pVictim);

    // Stop attack of current victim
    void DoStopAttack();

    // Cast spell
    void DoCast(Unit* pVictim, uint32 uiSpellId);
    void DoCastSpell(Unit* pVictim, SpellEntry* pSpellInfo);

    void DoSay(int32 iTextId, uint32 uiLanguage);

    void DoGoHome();
};

#endif
