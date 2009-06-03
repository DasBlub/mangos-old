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

#include "sc_defines.h"

bool GossipHello_default(Player* /*pPlayer*/, Creature* /*pCreature*/)
{
    return false;
}

bool GossipSelect_default(Player* /*pPlayer*/, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 /*action*/ )
{
    return false;
}

bool GossipSelectWithCode_default( Player* /*pPlayer*/, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 /*uiAction*/, const char* /*sCode*/ )
{
    return false;
}

bool QuestAccept_default(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool QuestSelect_default(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool QuestComplete_default(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool ChooseReward_default(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/, uint32 /*uiOpt*/ )
{
    return false;
}

uint32 NPCDialogStatus_default(Player* /*pPlayer*/, Creature* /*pCreature*/ )
{
    return 128;
}

uint32 GODialogStatus_default(Player* /*pPlayer*/, GameObject* /*pGO*/ )
{
    return 128;
}

bool ItemHello_default(Player* /*pPlayer*/, Item* /*pItem*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool ItemQuestAccept_default(Player* /*pPlayer*/, Item* /*pItem*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool GOHello_default(Player* /*pPlayer*/, GameObject* /*pGO*/ )
{
    return false;
}

bool GOQuestAccept_default(Player* /*pPlayer*/, GameObject* /*pGO*/, Quest const* /*pQuest*/ )
{
    return false;
}

bool GOChooseReward_default(Player* /*pPlayer*/, GameObject* /*pGO*/, Quest const* /*pQuest*/, uint32 /*uiOpt*/ )
{
    return false;
}

bool AreaTrigger_default(Player* /*pPlayer*/, AreaTriggerEntry* /*atEntry*/ )
{
    return false;
}

void AddSC_default()
{
    Script* pNewscript;

    pNewscript = new Script;
    pNewscript->sName="default";
    pNewscript->pGossipHello          = &GossipHello_default;
    pNewscript->pQuestAccept          = &QuestAccept_default;
    pNewscript->pGossipSelect         = &GossipSelect_default;
    pNewscript->pGossipSelectWithCode = &GossipSelectWithCode_default;
    pNewscript->pQuestSelect          = &QuestSelect_default;
    pNewscript->pQuestComplete        = &QuestComplete_default;
    pNewscript->pNPCDialogStatus      = &NPCDialogStatus_default;
    pNewscript->pGODialogStatus       = &GODialogStatus_default;
    pNewscript->pChooseReward         = &ChooseReward_default;
    pNewscript->pItemHello            = &ItemHello_default;
    pNewscript->pGOHello              = &GOHello_default;
    pNewscript->pAreaTrigger          = &AreaTrigger_default;
    pNewscript->pItemQuestAccept      = &ItemQuestAccept_default;
    pNewscript->pGOQuestAccept        = &GOQuestAccept_default;
    pNewscript->pGOChooseReward       = &GOChooseReward_default;

    pNewscript->registerSelf();
}
