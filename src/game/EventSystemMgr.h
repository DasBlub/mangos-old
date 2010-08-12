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

class Player;
class Creature;
class ChatCommand;
class GameEventData;
class BattleGround;
class ArenaTeam;
class Item;
class ItemPosCountVec;

struct EventInfo
{
    uint32 time;

    EventInfo() : time(getMSTime()) {}
};

template <typename U>
struct EventInfoUnit : public EventInfo
{
    const U &subject;

    EventInfoUnit(const U &subject_)
    : EventInfo(), subject(subject_) {}
};
typedef EventInfoUnit<Creature> EventInfoCreature;
typedef EventInfoUnit<Player> EventInfoPlayer;
typedef EventInfoUnit<ArenaTeam> EventInfoArenaTeam;

struct EventInfoArenaTeamStatus : public EventInfoArenaTeam
{
    const Player *originator;

    EventInfoArenaTeamStatus(const ArenaTeam &team_, const Player *originator_)
    : EventInfoArenaTeam(team_), originator(originator_) {}
};

struct EventInfoArenaTeamRating : public EventInfoArenaTeam
{
    uint32 amount;

    EventInfoArenaTeamRating(const ArenaTeam &team_, uint32 amount_)
    : EventInfoArenaTeam(team_), amount(amount_) {}
};

struct EventInfoBattleGround : public EventInfo
{
    const BattleGround &battleGround;
    const ArenaTeam *alliance, *horde;

    EventInfoBattleGround(const BattleGround &battleGround_, const ArenaTeam *alliance_, const ArenaTeam *horde_)
    : EventInfo(), battleGround(battleGround_), alliance(alliance_), horde(horde_) {}
};

struct EventInfoBattleGroundEnded : public EventInfoBattleGround
{
    uint32 winnerFaction;

    EventInfoBattleGroundEnded(const BattleGround &battleGround_, uint32 winnerFaction_,
                               const ArenaTeam *alliance_, const ArenaTeam *horde_)
    : EventInfoBattleGround(battleGround_, alliance_, horde_), winnerFaction(winnerFaction_) {}
};

struct EventInfoCharacter : public EventInfo
{
    const std::string &name;
    uint32 accountId;
    const std::string &ip;

    EventInfoCharacter(const std::string &name_, uint32 accountId_, const std::string &ip_)
    : EventInfo(), name(name_), accountId(accountId_), ip(ip_) {}
};

struct EventInfoCharacterRenamed : public EventInfoCharacter
{
    const std::string &oldname;

    EventInfoCharacterRenamed(const std::string &name_, const std::string &oldname_, uint32 accountId_, const std::string &ip_)
    : EventInfoCharacter(name_, accountId_, ip_), oldname(oldname_) {}
};

struct EventInfoCommand : public EventInfo
{
    const ChatCommand &command;
    uint32 accountId;
    const Player *player;

    EventInfoCommand(const ChatCommand &command_, uint32 accountId_, const Player *player_)
    : EventInfo(), command(command_), accountId(accountId_), player(player_) {}
};

struct EventInfoGameEvent : public EventInfo
{
    uint16 id;
    const GameEventData &gameEvent;

    EventInfoGameEvent(uint16 id_, const GameEventData &gameEvent_)
    : EventInfo(), id(id_), gameEvent(gameEvent_) {}
};

struct EventInfoPlayerLevel : public EventInfoPlayer
{
    uint32 level, increase;

    EventInfoPlayerLevel(const Player &player_, uint32 level_, uint32 increase_)
    : EventInfoPlayer(player_), level(level_), increase(increase_) {}
};

struct EventInfoPlayerItem : public EventInfoPlayer
{
    const Item &item;
    const ItemPosCountVec &position;

    EventInfoPlayerItem(const Player &player_, const Item &item_, const ItemPosCountVec &position_)
    : EventInfoPlayer(player_), item(item_), position(position_) {}
}

class Listener {};

class ListenerArenaTeam : public Listener
{
public:
    virtual void EventArenaTeamCreated(const EventInfoArenaTeamStatus &) {}
    virtual void EventArenaTeamDisbanded(const EventInfoArenaTeamStatus &) {}
    virtual void EventArenaTeamRatingGained(const EventInfoArenaTeamRating &) {}
};

class ListenerBattleGround : public Listener
{
public:
    virtual void EventBattleGroundStarted(const EventInfoBattleGround &) {}
    virtual void EventBattleGroundEnded(const EventInfoBattleGroundEnded &) {}
};

class ListenerBoss : public Listener
{
public:
    virtual void EventBossAggroed(const EventInfoCreature &) {}
    virtual void EventBossDied(const EventInfoCreature &) {}
    virtual void EventBossEvaded(const EventInfoCreature &) {}
};

class ListenerCharacter : public Listener
{
public:
    virtual void EventCharacterLogin(const EventInfoCharacter &) {}
    virtual void EventCharacterLogout(const EventInfoCharacter &) {}
    virtual void EventCharacterCreated(const EventInfoCharacter &) {}
    virtual void EventCharacterRenamed(const EventInfoCharacterRenamed &) {}
    virtual void EventCharacterDeleted(const EventInfoCharacter &) {}
    virtual void EventCharacterDeletedFinally(const EventInfoCharacter &) {}
};

class ListenerCommand : public Listener
{
public:
    virtual void EventCommandUsed(const EventInfoCommand &) {}
    virtual void EventCommandGMUsed(const EventInfoCommand &) {}
};

class ListenerCreature : public Listener
{
public:
    virtual void EventCreatureSpawned(const EventInfoCreature &) {}
    virtual void EventCreatureDied(const EventInfoCreature &) {}
};

class ListenerGameEvent : public Listener
{
public:
    virtual void EventGameEventStarted(const EventInfoGameEvent &) {}
    virtual void EventGameEventStopped(const EventInfoGameEvent &) {}
};

class ListenerPlayerLevel : public Listener
{
public:
    virtual void EventPlayerLevelReached(const EventInfoPlayerLevel &) {}
//    virtual void EventPlayerSkillLevelReached(const EventInfoPlayerLevel &) {}
    virtual void EventPlayerReputationLevelReached(const EventInfoPlayerLevel &) {}
//    virtual void EventPlayerPersonalArenaRatingGained(const EventInfoPlayerLevel &) {}
    virtual void EventPlayerTalentsReseted(const EventInfoPlayer &) {}
};

class ListenerPlayerItem : public Listener
{
public:
    virtual void EventPlayerItemUsed(const EventInfoPlayerItem &) {}
    virtual void EventPlayerItemEquipped(const EventInfoPlayerItem &) {}
    virtual void EventPlayerItemReceived(const EventInfoPlayerItem &) {}
    virtual void EventPlayerItemColoredReceived(const EventInfoPlayerItem &) {}
}

template<typename L>
struct ListenerSet {
    typedef UNORDERED_SET<L *> Type;
};

template<typename L>
struct EventConnect
{
public:
    inline EventConnect& operator+=(L *listener)
    {
        RegisterListener(listener);
        return *this;
    }

    inline void RegisterListener(L *listener)
    {
        list.insert(listener);
    }

    template<typename S>
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

    void TriggerArenaTeamCreated(const ArenaTeam &team, const Player *originator); // TODO: test
    void TriggerArenaTeamDisbanded(const ArenaTeam &team, const Player *originator); // TODO: test
    void TriggerArenaTeamRatingGained(const ArenaTeam &team, uint32 amount); // TODO: test

//    void TriggerAuctionCreated(); // TODO: support

    void TriggerBattleGroundStarted(const BattleGround &battleGround, const ArenaTeam *alliance = NULL,
                                    const ArenaTeam *horde = NULL); // TODO: test
    void TriggerBattleGroundEnded(const BattleGround &battleGround, uint32 winnerFaction,
                                  const ArenaTeam *alliance = NULL, const ArenaTeam *horde = NULL); // TODO: test

    void TriggerBossAggroed(const Creature &boss);
    void TriggerBossEvaded(const Creature &boss);
    void TriggerBossDied(const Creature &boss);

    void TriggerCharacterLogin(const std::string &name, uint32 accountId, const std::string &ip);
    void TriggerCharacterLogout(const std::string &name, uint32 accountId, const std::string &ip);
    void TriggerCharacterCreated(const std::string &name, uint32 accountId, const std::string &ip);
    void TriggerCharacterRenamed(const std::string &name, const std::string &oldname,
                               uint32 accountId, const std::string &ip);
    void TriggerCharacterDeleted(const std::string &name, uint32 accountId, const std::string &ip);
    void TriggerCharacterDeletedFinally(const std::string &name, uint32 accountId, const std::string &ip);

    void TriggerCommandUsed(const ChatCommand &command, uint32 accountId, const Player *player = NULL);
    void TriggerCommandGMUsed(const ChatCommand &command, uint32 accountId, const Player *player = NULL);

    void TriggerCreatureSpawned(const Creature &creature);
    void TriggerCreatureDied(const Creature &creature);

    void TriggerGameEventStarted(uint16 id, const GameEventData &gameEvent);
    void TriggerGameEventStopped(uint16 id, const GameEventData &gameEvent);

    void TriggerLootItemColoredDropped(const Player &player); // TODO: suuport
    void TriggerLootItemQuestDropped(const Player &player); // TODO: support

    void TriggerPlayerLevelReached(const Player &player, uint32 level, uint32 increase);
//    void TriggerPlayerSkillLevelReached(const Player &player, uint32 level, uint32 increase);
    void TriggerPlayerReputationLevelReached(const Player &player, uint32 level, uint32 increase);
//    void TriggerPlayerPersonalArenaRatingGained(const Player &player, uint32 level, uint32 increase);

    void TriggerPlayerTalentsReseted(const Player &player);

    void TriggerPlayerSpellLearned(const Player &player); // TODO: support

    void TriggerPlayerSpellCasted(const Player &player); // TODO: support
    void TriggerPlayerDamageDealt(const Player &player); // TODO: support

    void TriggerPlayerTeleported(const Player &player); // TODO: support
    void TriggerPlayerFlightPathTaken(const Player &player); // TODO: support

    void TriggerPlayerInstanceEntered(const Player &player); // TODO: support
    void TriggerPlayerInstanceLeaved(const Player &player); // TODO: support
    void TriggerPlayerInstanceIdReceived(const Player &player); // TODO: support

    void TriggerPlayerRevived(const Player &player); // TODO: support
    void TriggerPlayerDied(const Player &player); // TODO: support

    void TriggerPlayerKilledByPlayer(const Player &player); // TODO: support
    void TriggerPlayerKilledByCreature(const Player &player); // TODO: support
    void TriggerPlayerKilledOtherPlayer(const Player &player); // TODO: support
    void TriggerPlayerKilledOtherCreature(const Player &player); // TODO: support

    void TriggerPlayerItemUsed(const Player &player, const Item &item, const ItemPosCountVec &position); // TODO: support
    void TriggerPlayerItemEquipped(const Player &player, const Item &item, const ItemPosCountVec &position); // TODO: support
    void TriggerPlayerItemReceived(const Player &player, const Item &item, const ItemPosCountVec &position); // TODO: test
    void TriggerPlayerItemColoredReceived(const Player &player, const Item &item, const ItemPosCountVec &position); // TODO: test

    void TriggerPlayerQuestCompleted(const Player &player); // TODO: support
    void TriggerPlayerQuestAbandoned(const Player &player); // TODO: support
    void TriggerPlayerQuestItemCollected(const Player &player); // TODO: support

    void TriggerPlayerBattleGroundJoined(const Player &player); // TODO: support
    void TriggerPlayerBattleGroundLeaved(const Player &player); // TODO: support

    void TriggerPlayerBattleGroundWon(const Player &player); // TODO: support
    void TriggerPlayerBattleGroundLost(const Player &player); // TODO: support
    void TriggerPlayerDuellWon(const Player &player); // TODO: support
    void TriggerPlayerDuellLost(const Player &player); // TODO: support

    void TriggerPlayerArenaTeamJoined(const Player &player); // TODO: support
    void TriggerPlayerArenaTeamLeaved(const Player &player); // TODO: support

//    void TriggerPlayerGameObjectUsed(const Player &player); // TODO: support

    void TriggerPlayerMailSend(const Player &player); // TODO: support
    void TriggerPlayerTradeAccepted(const Player &player); // TODO: support
    void TriggerPlayerTradeSpecialAccepted(const Player &player); // TODO: support
    void TriggerPlayerMerchantTraded(const Player &player); // TODO: support

    void TriggerPlayerMoneyGained(const Player &player); // TODO: support
    void TriggerPlayerMoneyLooted(const Player &player); // TODO: support

    void TriggerRaidCreated(const Player &player); // TODO: support
    void TriggerRaidDisbanded(const Player &player); // TODO: support

    std::string NameOfEventType(EventType type) const;

    EventConnect<ListenerArenaTeam> ArenaTeamEvents;
    EventConnect<ListenerBattleGround> BattleGroundEvents;
    EventConnect<ListenerBoss> BossEvents;
    EventConnect<ListenerCharacter> CharacterEvents;
    EventConnect<ListenerCommand> CommandEvents;
    EventConnect<ListenerCreature> CreatureEvents;
    EventConnect<ListenerGameEvent> GameEventEvents;
    EventConnect<ListenerPlayerLevel> PlayerLevelEvents;
    EventConnect<ListenerPlayerItem> PlayerItemEvents;
};

#define sEventSystemMgr MaNGOS::Singleton<EventSystemMgr>::Instance()

#endif // __EVENTSYSTEMMGR_H__
