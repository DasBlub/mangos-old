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

#ifndef SC_DEFINES_H
#define SC_DEFINES_H

#include "../ScriptMgr.h"

// Skill defines

enum TRADESKILLS {
    TRADESKILL_ALCHEMY               = 1,
    TRADESKILL_BLACKSMITHING         = 2,
    TRADESKILL_COOKING               = 3,
    TRADESKILL_ENCHANTING            = 4,
    TRADESKILL_ENGINEERING           = 5,
    TRADESKILL_FIRSTAID              = 6,
    TRADESKILL_HERBALISM             = 7,
    TRADESKILL_LEATHERWORKING        = 8,
    TRADESKILL_POISONS               = 9,
    TRADESKILL_TAILORING             = 10,
    TRADESKILL_MINING                = 11,
    TRADESKILL_FISHING               = 12,
    TRADESKILL_SKINNING              = 13,
    TRADESKILL_JEWELCRAFTING         = 14,
    TRADESKILL_INSCRIPTION           = 15
};

enum TRADESKILL_LEVELS {
    TRADESKILL_LEVEL_NONE            = 0,
    TRADESKILL_LEVEL_APPRENTICE      = 1,
    TRADESKILL_LEVEL_JOURNEYMAN      = 2,
    TRADESKILL_LEVEL_EXPERT          = 3,
    TRADESKILL_LEVEL_ARTISAN         = 4,
    TRADESKILL_LEVEL_MASTER          = 5,
    TRADESKILL_LEVEL_GRAND_MASTER    = 6
};

// Gossip defines

enum GOSSIP_ACTIONS {
    GOSSIP_ACTION_TRADE                 = 1,
    GOSSIP_ACTION_TRAIN                 = 2,
    GOSSIP_ACTION_TAXI                  = 3,
    GOSSIP_ACTION_GUILD                 = 4,
    GOSSIP_ACTION_BATTLE                = 5,
    GOSSIP_ACTION_BANK                  = 6,
    GOSSIP_ACTION_INN                   = 7,
    GOSSIP_ACTION_HEAL                  = 8,
    GOSSIP_ACTION_TABARD                = 9,
    GOSSIP_ACTION_AUCTION               = 10,
    GOSSIP_ACTION_INN_INFO              = 11,
    GOSSIP_ACTION_UNLEARN               = 12,
    GOSSIP_ACTION_INFO_DEF              = 1000
};

enum GOSSIP_SENDERS {
    GOSSIP_SENDER_MAIN                  = 1,
    GOSSIP_SENDER_INN_INFO              = 2,
    GOSSIP_SENDER_INFO                  = 3,
    GOSSIP_SENDER_SEC_PROFTRAIN         = 4,
    GOSSIP_SENDER_SEC_CLASSTRAIN        = 5,
    GOSSIP_SENDER_SEC_BATTLEINFO        = 6
};

static const DWORD DEFAULT_GOSSIP_MESSAGE = 0xffffff;

extern uint32 GetSkillLevel(Player* pPlayer, uint32 uiSkill);

// Defined functions to use with player.

#define ADD_GOSSIP_ITEM(a,b,c,d,e,f)    PlayerTalkClass->GetGossipMenu()->AddMenuItem(a,b,c,d,e,f)
#define SEND_GOSSIP_MENU(a,b)           PlayerTalkClass->SendGossipMenu(a,b)
#define SEND_POI(a,b,c,d,e,f)           PlayerTalkClass->SendPointOfInterest(a,b,c,d,e,f)
#define CLOSE_GOSSIP_MENU()             PlayerTalkClass->CloseGossip();

#define QUEST_DIALOG_STATUS(a,b,c)   GetSession()->getDialogStatus(a,b,c)
#define SEND_QUEST_DETAILS(a,b,c)    PlayerTalkClass->SendQuestDetails(a,b,c)
#define SEND_REQUESTEDITEMS(a,b,c,d) PlayerTalkClass->SendRequestedItems(a,b,c,d)

#define SEND_VENDORLIST(a)         GetSession()->SendListInventory(a)
#define SEND_TRAINERLIST(a)        GetSession()->SendTrainerList(a)
#define SEND_BANKERLIST(a)         GetSession()->SendShowBank(a)
#define SEND_TABARDLIST(a)         GetSession()->SendTabardVendorActivate(a)
#define SEND_AUCTIONLIST(a)        GetSession()->SendAuctionHello(a)
#define SEND_TAXILIST(a)           GetSession()->SendTaxiStatus(a)
#define SEND_SPRESURRECT()         GetSession()->SendSpiritResurrect()
#define GET_HONORRANK()            GetHonorRank()

// -----------------------------------
#endif
