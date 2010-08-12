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
enum EventType
{
    EVENT_COMMAND_USED,
    EVENT_COMMAND_GM_USED,

    EVENT_CHARACTER_CREATED,
    EVENT_CHARACTER_RENAMED,
    EVENT_CHARACTER_DELETED,
    EVENT_CHARACTER_DELETED_FINALLY,

    EVENT_CREATURE_SPAWNED,
    EVENT_CREATURE_DIED,

    EVENT_BOSS_AGGRO,
    EVENT_BOSS_EVADED,
    EVENT_BOSS_DIED,

    EVENT_GAMEEVENT_STARTED,
    EVENT_GAMEEVENT_STOPPED,

    EVENT_BATTLEGROUND_STARTED, // TODO: test
    EVENT_BATTLEGROUND_ENDED, // TODO: test

    EVENT_PLAYER_LOGIN,
    EVENT_PLAYER_LOGOUT,

    EVENT_PLAYER_LEVEL_REACHED,
//    EVENT_PLAYER_SKILL_LEVEL_REACHED,
    EVENT_PLAYER_REPUTATION_LEVEL_REACHED,
//    EVENT_PLAYER_PERSONAL_ARENA_RATING_GAINED,
    EVENT_PLAYER_TALENT_RESET,

//    EVENT_PLAYER_SPELL_CAST,
    EVENT_PLAYER_SPELL_LEARNED, // TODO: support
    EVENT_PLAYER_DAMAGE_DEALT, // TODO: support

    EVENT_PLAYER_TELEPORTED, // TODO: support
//    EVENT_PLAYER_FLIGHT_PATH_TAKEN,
    EVENT_PLAYER_INSTANCE_ENTERED, // TODO: support
    EVENT_PLAYER_INSTANCE_LEAVED, // TODO: support
    EVENT_PLAYER_INSTANCE_ID_RECEIVED, // TODO: support

    EVENT_PLAYER_REVIVED, // TODO: support
    EVENT_PLAYER_DIED, // TODO: support
    EVENT_PLAYER_KILLED_BY_PLAYER, // TODO: support
    EVENT_PLAYER_KILLED_BY_CREATURE, // TODO: support
    EVENT_PLAYER_KILLED_OTHER_PLAYER, // TODO: support
    EVENT_PLAYER_KILLED_OTHER_CREATURE, // TODO: support

    EVENT_PLAYER_ITEM_USED, // TODO: support
    EVENT_PLAYER_ITEM_EQUIPED, // TODO: support
    EVENT_PLAYER_ITEM_RECEIVED, // TODO: support
    EVENT_PLAYER_ITEM_COLORED_RECEIVED, // TODO: support

    EVENT_PLAYER_QUEST_COMPLETED, // TODO: support
    EVENT_PLAYER_QUEST_ABANDONED, // TODO: support
    EVENT_PLAYER_QUEST_ITEM_COLLECTED, // TODO: support

    EVENT_PLAYER_BATTLEGROUND_JOINED, // TODO: support
    EVENT_PLAYER_BATTLEGROUND_LEAVED, // TODO: support
    EVENT_PLAYER_BATTLEGROUND_WON, // TODO: support
    EVENT_PLAYER_BATTLEGROUND_LOST, // TODO: support
    EVENT_PLAYER_DUELL_WON, // TODO: support
    EVENT_PLAYER_DUELL_LOST, // TODO: support
    EVENT_PLAYER_ARENA_TEAM_JOINED, // TODO: support
    EVENT_PLAYER_ARENA_TEAM_LEAVED, // TODO: support

//    EVENT_PLAYER_GAMEOBJECT_USED,
    EVENT_PLAYER_MAIL_SEND, // TODO: support
    EVENT_PLAYER_TRADE_ACCEPTED, // TODO: support
    EVENT_PLAYER_TRADE_SPECIAL_ACCEPTED, // TODO: support
    EVENT_PLAYER_MERCHANT_TRADED, // TODO: support

    EVENT_PLAYER_MONEY_GAINED, // TODO: support
    EVENT_PLAYER_MONEY_LOOTED, // TODO: support

    EVENT_LOOT_ITEM_EPIC_DROPPED, // TODO: support

    EVENT_RAID_CREATED, // TODO: support
    EVENT_RAID_DISBANDED, // TODO: support

    EVENT_ARENA_TEAM_CREATED, // TODO: test
    EVENT_ARENA_TEAM_DISBANDED, // TODO: test
    EVENT_ARENA_TEAM_RATING_GAINED, // TODO: test

//    EVENT_AUCTION_CREATED,
    // =============
    EVENT_MARKER_END
};

class Player;
class Creature;
class ChatCommand;
class GameEventData;
class BattleGround;
class ArenaTeam;

struct EventInfo
{
    EventType type;
    uint32 time;

    EventInfo(EventType type_, uint32 time_ = getMSTime())
    : type(type_), time(time_) {}
};

struct EventInfoCommand : public EventInfo
{
    const ChatCommand &command;
    uint32 accountId;
    const Player *player;

    EventInfoCommand(EventType type_, const ChatCommand &command_, uint32 accountId_, const Player *player_, uint32 time_)
    : EventInfo(type_, time_), command(command_), accountId(accountId_), player(player_) {}
};

template <typename U>
struct EventInfoUnit : public EventInfo
{
    const U &unit;

    EventInfoUnit(EventType type_, const U &unit_, uint32 time_ = getMSTime())
    : EventInfo(type_, time_), unit(unit_) {}
};
typedef EventInfoUnit<Creature> EventInfoCreature;
typedef EventInfoUnit<Player> EventInfoPlayer;

struct EventInfoCharacter : public EventInfo
{
    const std::string &name, &oldname;
    uint32 accountId;
    const std::string &ip;

    EventInfoCharacter(EventType type_, const std::string &name_, uint32 accountId_, const std::string &ip_,
                   const std::string &oldname_, uint32 time_)
    : EventInfo(type_, time_), name(name_), oldname(oldname_), accountId(accountId_), ip(ip_) {}
};

struct EventInfoGameEvent : public EventInfo
{
    uint16 id;
    const GameEventData &gameEvent;

    EventInfoGameEvent(EventType type_, uint16 id_, const GameEventData &gameEvent_, uint32 time_)
    : EventInfo(type_, time_), id(id_), gameEvent(gameEvent_) {}
};

struct EventInfoBattleGround : public EventInfo
{
    const BattleGround &battleGround;
    uint32 winnerFaction;
    const ArenaTeam *alliance, *horde;

    EventInfoBattleGround(EventType type_, const BattleGround &battleGround_, uint32 winnerFaction_,
                      const ArenaTeam *alliance_, const ArenaTeam *horde_, uint32 time_)
    : EventInfo(type_, time_), battleGround(battleGround_), winnerFaction(winnerFaction_),
      alliance(alliance_), horde(horde_) {}
};

struct EventInfoPlayerLevel : public EventInfoPlayer
{
    uint32 level, increase;

    EventInfoPlayerLevel(EventType type_, const Player &player_, uint32 level_, uint32 increase_, uint32 time_)
    : EventInfoPlayer(type_, player_, time_), level(level_), increase(increase_) {}
};

struct EventInfoArenaTeam : public EventInfo
{
    const ArenaTeam &team;
    const Player *player;
    uint32 increase;

    EventInfoArenaTeam(EventType type_, const ArenaTeam &team_, const Player *player_, uint32 increase_, uint32 time_)
    : EventInfo(type_, time_), team(team_), player(player_), increase(increase_) {}
};

class Listener {};

class ListenerCommand : public Listener {
public:
    virtual void EventCommandUsed(const EventInfoCommand &) {}
    virtual void EventCommandGMUsed(const EventInfoCommand &) {}
};

class ListenerBoss : public Listener
{
public:
    virtual void EventBossAggro(const EventInfoCreature &) {}
    virtual void EventBossDied(const EventInfoCreature &) {}
    virtual void EventBossEvaded(const EventInfoCreature &) {}
};

class ListenerCreature : public Listener
{
public:
    virtual void EventCreatureSpawned(const EventInfoCreature &) {}
    virtual void EventCreatureDied(const EventInfoCreature &) {}
};

class ListenerCharacter : public Listener {
public:
    virtual void EventCharacterCreated(const EventInfoCharacter &) {}
    virtual void EventCharacterRenamed(const EventInfoCharacter &) {}
    virtual void EventCharacterDeleted(const EventInfoCharacter &) {}
    virtual void EventCharacterDeletedFinally(const EventInfoCharacter &) {}
};

class ListenerPlayerLoginout : public Listener {
public:
    virtual void EventPlayerLogin(const EventInfoCharacter &) {}
    virtual void EventPlayerLogout(const EventInfoCharacter &) {}
};

class ListenerGameEvent : public Listener {
public:
    virtual void EventGameEventStarted(const EventInfoGameEvent &) {}
    virtual void EventGameEventStopped(const EventInfoGameEvent &) {}
};

class ListenerBattleGround : public Listener {
public:
    virtual void EventBattleGroundStarted(const EventInfoBattleGround &) {}
    virtual void EventBattleGroundEnded(const EventInfoBattleGround &) {}
};

class ListenerPlayerLevel : public Listener {
public:
    virtual void EventPlayerLevelReached(const EventInfoPlayerLevel &) {}
//    virtual void EventPlayerSkillLevelReached(const EventInfoPlayerLevel &) {}
    virtual void EventPlayerReputationLevelReached(const EventInfoPlayerLevel &) {}
//    virtual void EventPlayerPersonalArenaRatingGained(const EventInfoPlayerLevel &) {}
    virtual void EventPlayerTalentReset(const EventInfoPlayerLevel &) {}
};

class ListenerArenaTeam : public Listener {
public:
    virtual void EventArenaTeamCreated(const EventInfoArenaTeam &) {}
    virtual void EventArenaTeamDisbanded(const EventInfoArenaTeam &) {}
    virtual void EventArenaTeamRatingGained(const EventInfoArenaTeam &) {}
};

template<typename L>
struct ListenerSet {
    typedef UNORDERED_SET<L *> Type;
};

template<typename L, typename S>
struct EventConnect
{
public:
    inline EventConnect& operator+=(L *listener)
    {
        RegisterListener(listener);
        return this;
    }

    inline void RegisterListener(L *listener)
    {
        list.insert(listener);
    }

    void InformListener(const S &event, void (L::*func)(const S&))
    {
        for (typename ListenerSet<L>::Type::const_iterator it = list.begin(); it != list.end(); ++it)
        {
            ((*it)->*func)(event);
        }
    }
private:
    typename ListenerSet<L>::Type list;
};

class EventSystemMgr
{
public:
    EventSystemMgr();
    virtual ~EventSystemMgr();

    void TriggerCommandEvent(EventType type, const ChatCommand &command, uint32 accountId,
                             const Player *player = NULL, uint32 time = getMSTime());
    void TriggerBossEvent(EventType type, const Creature &boss, uint32 time = getMSTime());
    void TriggerCreatureEvent(EventType type, const Creature &creature, uint32 time = getMSTime());
    void TriggerCharacterEvent(EventType type, const std::string &name, uint32 accountId, const std::string &ip,
                               const std::string &oldname = "", uint32 time = getMSTime());
    void TriggerPlayerLoginoutEvent(EventType type, const std::string &name, uint32 accountId,
                                    const std::string &ip, uint32 time = getMSTime());
    void TriggerGameEventEvent(EventType type, uint16 id, const GameEventData &gameEvent, uint32 time = getMSTime());
    void TriggerBattleGroundEvent(EventType type, const BattleGround &battleGround, uint32 winnerFaction = 0,
                                  const ArenaTeam *alliance = NULL, const ArenaTeam *horde = NULL, uint32 time = getMSTime());
    void TriggerPlayerLevelEvent(EventType type, const Player &player, uint32 level = 0,
                                 uint32 increase = 0, uint32 time = getMSTime());
    void TriggerArenaTeamEvent(EventType type, const ArenaTeam &team, const Player *player = NULL,
                               uint32 increase = 0, uint32 time = getMSTime());

    std::string NameOfEventType(EventType type) const;

    EventConnect<ListenerCommand, EventInfoCommand> CommandEvents;
    EventConnect<ListenerBoss, EventInfoCreature> BossEvents;
    EventConnect<ListenerCreature, EventInfoCreature> CreatureEvents;
    EventConnect<ListenerCharacter, EventInfoCharacter> CharacterEvents;
    EventConnect<ListenerPlayerLoginout, EventInfoCharacter> PlayerLoginoutEvents;
    EventConnect<ListenerGameEvent, EventInfoGameEvent> GameEventEvents;
    EventConnect<ListenerBattleGround, EventInfoBattleGround> BattleGroundEvents;
    EventConnect<ListenerPlayerLevel, EventInfoPlayerLevel> PlayerLevelEvents;
    EventConnect<ListenerArenaTeam, EventInfoArenaTeam> ArenaTeamEvents;

private:
    void PrintEventToLog(const EventInfo& event) const;
};

#define sEventSystemMgr MaNGOS::Singleton<EventSystemMgr>::Instance()

#endif // __EVENTSYSTEMMGR_H__
