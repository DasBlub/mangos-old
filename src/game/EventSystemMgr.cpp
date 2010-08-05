/*
 *  EventSystemMgr.cpp
 *  MaNGOS
 *
 *  Created by cipherCOM on 03.08.10.
 *  Copyright 2010 Back2Basics. All rights reserved.
 *
 */

#include "EventSystemMgr.h"

#include "Policies/SingletonImp.h"
#include "Object.h"

INSTANTIATE_SINGLETON_1(EventSystemMgr);

uint32 EventSystemMgr::_eventIdCounter = 0;

EventSystemMgr::EventSystemMgr() {}

EventSystemMgr::~EventSystemMgr() {}

uint32 EventSystemMgr::TriggerEvent(EventType type, uint32 val1, uint32 val2,
                                    WorldObject* obj1, WorldObject* obj2, uint32 time) {
    const ListenerSet& list = _listenerMap[type];
    uint32 id = _eventIdCounter++;
    EventInfo event(id, type, val1, val2, obj1, obj2, time);

    for (ListenerSet::const_iterator it = list.begin(); it != list.end(); ++it) {
        (*it)->EventOccured(event);
    }

    PrintEventToLog(event);

    return id;
}

void EventSystemMgr::RegisterListenerForEvent(EventType type, EventListener* listener) {
    ListenerSet& list = _listenerMap[type];
    list.insert(listener);
}

std::string EventSystemMgr::NameOfEventType(EventType type) const {
    switch (type) {
        case EVENT_COMMAND_USED: return "EVENT_COMMAND_USED";
        case EVENT_COMMAND_GM_USED: return "EVENT_COMMAND_GM_USED";

        case EVENT_CHARACTER_DELETED: return "EVENT_CHARACTER_DELETED";
        case EVENT_CHARACTER_CREATED: return "EVENT_CHARACTER_CREATED";

        case EVENT_CREATURE_SPAWNED: return "EVENT_CREATURE_SPAWNED";
        case EVENT_CREATURE_DIED: return "EVENT_CREATURE_DIED";
        case EVENT_CREATURE_EVADED: return "EVENT_CREATURE_EVADED";

        case EVENT_BOSS_EVENT_STARTED: return "EVENT_BOSS_EVENT_STARTED";
        case EVENT_BOSS_KILLED: return "EVENT_BOSS_KILLED";

        case EVENT_BG_STARTED: return "EVENT_BG_STARTED";
        case EVENT_BG_ENDED: return "EVENT_BG_ENDED";
        case EVENT_ARENA_STARTED: return "EVENT_ARENA_STARTED";
        case EVENT_ARENA_ENDED: return "EVENT_ARENA_ENDED";
        case EVENT_ARENA_RATED_STARTED: return "EVENT_ARENA_RATED_STARTED";
        case EVENT_ARENA_RATED_ENDED: return "EVENT_ARENA_RATED_ENDED";

        case EVENT_PLAYER_LEVEL_REACHED: return "EVENT_PLAYER_LEVEL_REACHED";
        case EVENT_PLAYER_SKILL_LEVEL_REACHED: return "EVENT_PLAYER_SKILL_LEVEL_REACHED";
        case EVENT_PLAYER_REPUTATION_LEVEL_REACHED: return "EVENT_PLAYER_REPUTATION_LEVEL_REACHED";
        case EVENT_PLAYER_TEAM_RATING_GAINED: return "EVENT_PLAYER_TEAM_RATING_GAINED";
        case EVENT_PLAYER_TALENT_RESET: return "EVENT_PLAYER_TALENT_RESET";
        case EVENT_PLAYER_PVP_TITLE_GAINED: return "EVENT_PLAYER_PVP_TITLE_GAINED";

        case EVENT_PLAYER_SPELL_CAST: return "EVENT_PLAYER_SPELL_CAST";
        case EVENT_PLAYER_SPELL_LEARNED: return "EVENT_PLAYER_SPELL_LEARNED";
        case EVENT_PLAYER_DAMAGE_DEALT: return "EVENT_PLAYER_DAMAGE_DEALT";

        case EVENT_PLAYER_TELEPORTED: return "EVENT_PLAYER_TELEPORTED";
        case EVENT_PLAYER_FLIGHT_PATH_TAKEN: return "EVENT_PLAYER_FLIGHT_PATH_TAKEN";

        case EVENT_PLAYER_REVIVED: return "EVENT_PLAYER_REVIVED";
        case EVENT_PLAYER_DIED: return "EVENT_PLAYER_DIED";
        case EVENT_PLAYER_KILLED_BY_PLAYER: return "EVENT_PLAYER_KILLED_BY_PLAYER";
        case EVENT_PLAYER_KILLED_BY_CREATURE: return "EVENT_PLAYER_KILLED_BY_CREATURE";
        case EVENT_PLAYER_KILLED_OTHER_PLAYER: return "EVENT_PLAYER_KILLED_OTHER_PLAYER";
        case EVENT_PLAYER_KILLED_OTHER_CREATURE: return "EVENT_PLAYER_KILLED_OTHER_CREATURE";

        case EVENT_PLAYER_ITEM_USED: return "EVENT_PLAYER_ITEM_USED";
        case EVENT_PLAYER_ITEM_EQUIPED: return "EVENT_PLAYER_ITEM_EQUIPED";
        case EVENT_PLAYER_ITEM_RECEIVED: return "EVENT_PLAYER_ITEM_RECEIVED";
        case EVENT_PLAYER_ITEM_EPIC_RECEIVED: return "EVENT_PLAYER_ITEM_EPIC_RECEIVED";

        case EVENT_PLAYER_QUEST_COMPLETED: return "EVENT_PLAYER_QUEST_COMPLETED";
        case EVENT_PLAYER_QUEST_ABANDONED: return "EVENT_PLAYER_QUEST_ABANDONED";
        case EVENT_PLAYER_QUEST_DAILY_COMPLETED: return "EVENT_PLAYER_QUEST_DAILY_COMPLETED";
        case EVENT_PLAYER_QUEST_ITEM_RECEIVED: return "EVENT_PLAYER_QUEST_ITEM_RECEIVED";

        case EVENT_PLAYER_BG_STARTED: return "EVENT_PLAYER_BG_STARTED";
        case EVENT_PLAYER_BG_WON: return "EVENT_PLAYER_BG_WON";
        case EVENT_PLAYER_ARENA_STARTED: return "EVENT_PLAYER_ARENA_STARTED";
        case EVENT_PLAYER_ARENA_WON: return "EVENT_PLAYER_ARENA_WON";
        case EVENT_PLAYER_ARENA_RATED_STARTED: return "EVENT_PLAYER_ARENA_RATED_STARTED";
        case EVENT_PLAYER_ARENA_RATED_WON: return "EVENT_PLAYER_ARENA_RATED_WON";
        case EVENT_PLAYER_DUELL_LOST: return "EVENT_PLAYER_DUELL_LOST";
        case EVENT_PLAYER_DUELL_WON: return "EVENT_PLAYER_DUELL_WON";

        case EVENT_PLAYER_RAID_COMPLETED: return "EVENT_PLAYER_RAID_COMPLETED";
        case EVENT_PLAYER_GAMEOBJECT_USED: return "EVENT_PLAYER_GAMEOBJECT_USED";
        case EVENT_PLAYER_MAIL_SEND: return "EVENT_PLAYER_MAIL_SEND";

        case EVENT_PLAYER_MONEY_GAINED: return "EVENT_PLAYER_MONEY_GAINED";
        case EVENT_PLAYER_MONEY_LOOTED: return "EVENT_PLAYER_MONEY_LOOTED";

        case EVENT_LOOT_ITEM_EPIC_DROPPED: return "EVENT_LOOT_ITEM_EPIC_DROPPED";

        case EVENT_AUCTION_CREATED: return "EVENT_AUCTION_CREATED";

        default: return "Eventname unknown";
    }
    return "Eventname unknown";
}

void EventSystemMgr::PrintEventToLog(const EventInfo& event) const {
    WorldObject *obj1 = event.obj1, *obj2 = event.obj2;
    sLog.outString("====================");
    sLog.outString("Event occured: type=%s[%d] val1=%d val2=%d obj1=%s[%s%d] obj2=%s[%s%d] time=%d",
                   NameOfEventType(event.type).c_str(), event.id, event.val1, event.val2,
                   obj1 ? obj1->GetName() : "NULL", obj1 ? (obj1->GetTypeId() == TYPEID_PLAYER ? "P#":"C#") : "", obj1 ? obj1->GetGUIDLow() : 0,
                   obj2 ? obj2->GetName() : "NULL", obj2 ? (obj2->GetTypeId() == TYPEID_PLAYER ? "P#":"C#") : "", obj2 ? obj2->GetGUIDLow() : 0,
                   event.time);
}
