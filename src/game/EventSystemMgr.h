/*
 *  EventSystemMgr.h
 *  MaNGOS
 *
 *  Created by cipherCOM on 03.08.10.
 *  Copyright 2010 Back2Basics. All rights reserved.
 *
 */

#ifndef __EVENTSYSTEMMGR_H__
#define __EVENTSYSTEMMGR_H__

#include "Policies/Singleton.h"
#include "Utilities/UnorderedMap.h"
#include "Utilities/UnorderedSet.h"
#include "Timer.h"

// Don't forget to keep the naming function in sync!
enum EventType {
    // 0
    EVENT_COMMAND_USED, // TODO: support this one
    EVENT_COMMAND_GM_USED, // TODO: support this one
    // 2
    EVENT_CHARACTER_DELETED, // TODO: support this one
    EVENT_CHARACTER_CREATED, // TODO: support this one
    // 4
    EVENT_CREATURE_SPAWNED, // 4
    EVENT_CREATURE_DIED, // 5
    EVENT_CREATURE_EVADED, // 6
    // 7
    EVENT_BOSS_EVENT_STARTED, // 7
    EVENT_BOSS_KILLED, // 8
    // 9
    EVENT_BG_STARTED, // TODO: support this one
    EVENT_BG_ENDED, // TODO: support this one
    EVENT_ARENA_STARTED, // TODO: support this one
    EVENT_ARENA_ENDED, // TODO: support this one
    EVENT_ARENA_RATED_STARTED, // TODO: support this one
    EVENT_ARENA_RATED_ENDED, // TODO: support this one
    // 15
    EVENT_PLAYER_LEVEL_REACHED, // TODO: support this one
    EVENT_PLAYER_SKILL_LEVEL_REACHED, // TODO: support this one
    EVENT_PLAYER_REPUTATION_LEVEL_REACHED, // TODO: support this one
    EVENT_PLAYER_TEAM_RATING_GAINED, // TODO: support this one
    EVENT_PLAYER_TALENT_RESET, // TODO: support this one
    EVENT_PLAYER_PVP_TITLE_GAINED, // TODO: support this one
    // 21
    EVENT_PLAYER_SPELL_CAST, // TODO: support this one
    EVENT_PLAYER_SPELL_LEARNED, // TODO: support this one
    EVENT_PLAYER_DAMAGE_DEALT, // TODO: support this one
    // 24
    EVENT_PLAYER_TELEPORTED, // TODO: support this one
    EVENT_PLAYER_FLIGHT_PATH_TAKEN, // TODO: support this one
    // 26
    EVENT_PLAYER_REVIVED, // 26
    EVENT_PLAYER_DIED, // 27
    EVENT_PLAYER_KILLED_BY_PLAYER, // 28
    EVENT_PLAYER_KILLED_BY_CREATURE, // 29
    EVENT_PLAYER_KILLED_OTHER_PLAYER, // 30
    EVENT_PLAYER_KILLED_OTHER_CREATURE, // 31
    // 32
    EVENT_PLAYER_ITEM_USED, // TODO: support this one
    EVENT_PLAYER_ITEM_EQUIPED, // TODO: support this one
    EVENT_PLAYER_ITEM_RECEIVED, // TODO: support this one
    EVENT_PLAYER_ITEM_EPIC_RECEIVED, // TODO: support this one

    EVENT_PLAYER_QUEST_COMPLETED, // TODO: support this one
    EVENT_PLAYER_QUEST_ABANDONED, // TODO: support this one
    EVENT_PLAYER_QUEST_DAILY_COMPLETED, // TODO: support this one
    EVENT_PLAYER_QUEST_ITEM_RECEIVED, // TODO: support this one

    EVENT_PLAYER_BG_STARTED, // TODO: support this one
    EVENT_PLAYER_BG_WON, // TODO: support this one
    EVENT_PLAYER_ARENA_STARTED, // TODO: support this one
    EVENT_PLAYER_ARENA_WON, // TODO: support this one
    EVENT_PLAYER_ARENA_RATED_STARTED, // TODO: support this one
    EVENT_PLAYER_ARENA_RATED_WON, // TODO: support this one
    EVENT_PLAYER_DUELL_LOST, // TODO: support this one
    EVENT_PLAYER_DUELL_WON, // TODO: support this one

    EVENT_PLAYER_RAID_COMPLETED, // TODO: support this one
    EVENT_PLAYER_GAMEOBJECT_USED, // TODO: support this one
    EVENT_PLAYER_MAIL_SEND, // TODO: support this one

    EVENT_PLAYER_MONEY_GAINED, // TODO: support this one
    EVENT_PLAYER_MONEY_LOOTED, // TODO: support this one

    EVENT_LOOT_ITEM_EPIC_DROPPED, // TODO: support this one

    EVENT_AUCTION_CREATED, // TODO: support this one
    // =============
    EVENT_MARKER_END
};

class WorldObject;

struct EventInfo {
    uint32 id;
    EventType type;
    uint32 val1;
    uint32 val2;
    WorldObject* obj1;
    WorldObject* obj2;
    uint32 time;

    EventInfo(uint32 id_, EventType type_, uint32 val1_ = 0, uint32 val2_ = 0,
              WorldObject* obj1_ = NULL, WorldObject* obj2_ = NULL, uint32 time_ = getMSTime())
    : id(id_), type(type_), val1(val1_), val2(val2_), obj1(obj1_), obj2(obj2_), time(time_) {}
};

class EventListener {
public:
    virtual void EventOccured(const EventInfo& event) = 0;
};

typedef UNORDERED_SET<EventListener*> ListenerSet;
typedef UNORDERED_MAP<uint32, ListenerSet> EventListenerMap;

class EventSystemMgr {
public:
    EventSystemMgr();
    virtual ~EventSystemMgr();

    uint32 TriggerEvent(EventType type, uint32 val1 = 0, uint32 val2 = 0,
                        WorldObject* obj1 = NULL, WorldObject* obj2 = NULL, uint32 time = getMSTime());

    void RegisterListenerForEvent(EventType type, EventListener* listener);
    std::string NameOfEventType(EventType type) const;

private:
    EventListenerMap _listenerMap;
    static uint32 _eventIdCounter;

    void PrintEventToLog(const EventInfo& event) const;
};

#define sEventSystemMgr MaNGOS::Singleton<EventSystemMgr>::Instance()

#endif // __EVENTSYSTEMMGR_H__
