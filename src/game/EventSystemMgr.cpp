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

EventSystemMgr::EventSystemMgr() {}

EventSystemMgr::~EventSystemMgr() {}

void EventSystemMgr::TriggerArenaTeamCreated(const ArenaTeam &team, const Player *originator)
{
    EventInfoArenaTeamStatus event(team, originator);
    ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamCreated);
}

void EventSystemMgr::TriggerArenaTeamDisbanded(const ArenaTeam &team, const Player *originator)
{
    EventInfoArenaTeamStatus event(team, originator);
    ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamDisbanded);
}

void EventSystemMgr::TriggerArenaTeamRatingGained(const ArenaTeam &team, uint32 amount)
{
    EventInfoArenaTeamRating event(team, amount);
    ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamRatingGained);
}

void EventSystemMgr::TriggerBattleGroundStarted(const BattleGround &battleGround,
                                                const ArenaTeam *alliance, const ArenaTeam *horde)
{
    EventInfoBattleGround event(battleGround, alliance, horde);
    BattleGroundEvents.InformListener(event, &ListenerBattleGround::EventBattleGroundStarted);
}

void EventSystemMgr::TriggerBattleGroundEnded(const BattleGround &battleGround, uint32 winnerFaction,
                                              const ArenaTeam *alliance, const ArenaTeam *horde)
{
    EventInfoBattleGroundEnded event(battleGround, winnerFaction, alliance, horde);
    BattleGroundEvents.InformListener(event, &ListenerBattleGround::EventBattleGroundEnded);
}

void EventSystemMgr::TriggerBossAggroed(const Creature &boss)
{
    EventInfoCreature event(boss);
    BossEvents.InformListener(event, &ListenerBoss::EventBossAggroed);
}

void EventSystemMgr::TriggerBossEvaded(const Creature &boss)
{
    EventInfoCreature event(boss);
    BossEvents.InformListener(event, &ListenerBoss::EventBossEvaded);
}

void EventSystemMgr::TriggerBossDied(const Creature &boss)
{
    EventInfoCreature event(boss);
    BossEvents.InformListener(event, &ListenerBoss::EventBossDied);
}

void EventSystemMgr::TriggerCharacterLogin(const std::string &name, uint32 accountId, const std::string &ip)
{
    EventInfoCharacter event(name, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterLogin);
}

void EventSystemMgr::TriggerCharacterLogout(const std::string &name, uint32 accountId, const std::string &ip)
{
    EventInfoCharacter event(name, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterLogout);
}

void EventSystemMgr::TriggerCharacterCreated(const std::string &name, uint32 accountId, const std::string &ip)
{
    EventInfoCharacter event(name, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterCreated);
}

void EventSystemMgr::TriggerCharacterRenamed(const std::string &name, const std::string &oldname,
                           uint32 accountId, const std::string &ip)
{
    EventInfoCharacterRenamed event(name, oldname, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterRenamed);
}

void EventSystemMgr::TriggerCharacterDeleted(const std::string &name, uint32 accountId, const std::string &ip)
{
    EventInfoCharacter event(name, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterDeleted);
}

void EventSystemMgr::TriggerCharacterDeletedFinally(const std::string &name, uint32 accountId, const std::string &ip)
{
    EventInfoCharacter event(name, accountId, ip);
    CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterDeletedFinally);
}

void EventSystemMgr::TriggerCommandUsed(const ChatCommand &command, uint32 accountId, const Player *player)
{
    EventInfoCommand event(command, accountId, player);
    CommandEvents.InformListener(event, &ListenerCommand::EventCommandUsed);
}

void EventSystemMgr::TriggerCommandGMUsed(const ChatCommand &command, uint32 accountId, const Player *player)
{
    EventInfoCommand event(command, accountId, player);
    CommandEvents.InformListener(event, &ListenerCommand::EventCommandGMUsed);
}

void EventSystemMgr::TriggerCreatureSpawned(const Creature &creature)
{
    EventInfoCreature event(creature);
    CreatureEvents.InformListener(event, &ListenerCreature::EventCreatureSpawned);
}

void EventSystemMgr::TriggerCreatureDied(const Creature &creature)
{
    EventInfoCreature event(creature);
    CreatureEvents.InformListener(event, &ListenerCreature::EventCreatureDied);
}

void EventSystemMgr::TriggerGameEventStarted(uint16 id, const GameEventData &gameEvent)
{
    EventInfoGameEvent event(id, gameEvent);
    GameEventEvents.InformListener(event, &ListenerGameEvent::EventGameEventStarted);
}

void EventSystemMgr::TriggerGameEventStopped(uint16 id, const GameEventData &gameEvent)
{
    EventInfoGameEvent event(id, gameEvent);
    GameEventEvents.InformListener(event, &ListenerGameEvent::EventGameEventStopped);
}

void EventSystemMgr::TriggerLootItemColoredDropped(const Player &player)
{
    EventInfoLootItem event();
    LootItemEvents.InformListener(event, &ListenerLootItem::EventLootItemColoredDropped);
}

void EventSystemMgr::TriggerLootItemQuestDropped(const Player &player)
{
    EventInfoLootItem event();
    LootItemEvents.InformListener(event, &ListenerLootItem::EventLootItemQuestDropped);
}

void EventSystemMgr::TriggerPlayerLevelReached(const Player &player, uint32 level, uint32 increase)
{
    EventInfoPlayerLevel event(player, level, increase);
    PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerLevelReached);
}

//    void EventSystemMgr::TriggerPlayerSkillLevelReached(const Player &player, uint32 level, uint32 increase) { sLog.outDebug("============EventSystemMgr::TriggerPlayerSkillLevelReached============"); }

void EventSystemMgr::TriggerPlayerReputationLevelReached(const Player &player, uint32 level, uint32 increase)
{
    EventInfoPlayerLevel event(player, level, increase);
    PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerReputationLevelReached);
}

//    void EventSystemMgr::TriggerPlayerPersonalArenaRatingGained(const Player &player, uint32 level, uint32 increase) { sLog.outDebug("============EventSystemMgr::TriggerPlayerPersonalArenaRatingGained============"); }

void EventSystemMgr::TriggerPlayerTalentsReseted(const Player &player)
{
    EventInfoPlayer event(player);
    PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerTalentsReseted);
}

void EventSystemMgr::TriggerPlayerItemUsed(const Player &player, const Item &item, const ItemPosCountVec &position)
{
    EventInfoPlayerItem event(player, item, position);
    PlayerItemEvents.InformListener(event, &ListenerPlayerItem::EventPlayerItemUsed);
}

void EventSystemMgr::TriggerPlayerItemEquipped(const Player &player, const Item &item, const ItemPosCountVec &position)
{
    EventInfoPlayerItem event(player, item, position);
    PlayerItemEvents.InformListener(event, &ListenerPlayerItem::EventPlayerItemEquipped);
}

void EventSystemMgr::TriggerPlayerItemReceived(const Player &player, const Item &item, const ItemPosCountVec &position)
{
    EventInfoPlayerItem event(player, item, position);
    PlayerItemEvents.InformListener(event, &ListenerPlayerItem::EventPlayerItemReceived);
}

void EventSystemMgr::TriggerPlayerItemColoredReceived(const Player &player, const Item &item, const ItemPosCountVec &position)
{
    EventInfoPlayerItem event(player, item, position);
    PlayerItemEvents.InformListener(event, &ListenerPlayerItem::EventPlayerItemColoredReceived);
}

// Debug purposes:
// Regex for creation: (void ([^(]+)[^\{]+\{)\}    ->    \1 sLog.outDebug("============\\n\2"); }
class PrintEvents : public ListenerArenaTeam, public ListenerBattleGround, public ListenerBoss, public ListenerCharacter,
public ListenerCommand, public ListenerCreature, public ListenerGameEvent, public ListenerPlayerLevel
{
public:
    PrintEvents()
    {
        sEventSystemMgr.ArenaTeamEvents += this;
        sEventSystemMgr.BattleGroundEvents += this;
        sEventSystemMgr.BossEvents += this;
        sEventSystemMgr.CharacterEvents += this;
        sEventSystemMgr.CommandEvents += this;
        sEventSystemMgr.CreatureEvents += this;
        sEventSystemMgr.GameEventEvents += this;
        sEventSystemMgr.PlayerLevelEvents += this;
        sEventSystemMgr.PlayerItemEvents += this;
    }
    void EventArenaTeamCreated(const EventInfoArenaTeamStatus &) { sLog.outDebug("============EventArenaTeamCreated============"); }
    void EventArenaTeamDisbanded(const EventInfoArenaTeamStatus &) { sLog.outDebug("============EventArenaTeamDisbanded============"); }
    void EventArenaTeamRatingGained(const EventInfoArenaTeamRating &) { sLog.outDebug("============EventArenaTeamRatingGained============"); }
    void EventBattleGroundStarted(const EventInfoBattleGround &) { sLog.outDebug("============EventBattleGroundStarted============"); }
    void EventBattleGroundEnded(const EventInfoBattleGroundEnded &) { sLog.outDebug("============EventBattleGroundEnded============"); }
    void EventBossAggroed(const EventInfoCreature &) { sLog.outDebug("============EventBossAggroed============"); }
    void EventBossDied(const EventInfoCreature &) { sLog.outDebug("============EventBossDied============"); }
    void EventBossEvaded(const EventInfoCreature &) { sLog.outDebug("============EventBossEvaded============"); }
    void EventCharacterLogin(const EventInfoCharacter &) { sLog.outDebug("============EventCharacterLogin============"); }
    void EventCharacterLogout(const EventInfoCharacter &) { sLog.outDebug("============EventCharacterLogout============"); }
    void EventCharacterCreated(const EventInfoCharacter &) { sLog.outDebug("============EventCharacterCreated============"); }
    void EventCharacterRenamed(const EventInfoCharacterRenamed &) { sLog.outDebug("============EventCharacterRenamed============"); }
    void EventCharacterDeleted(const EventInfoCharacter &) { sLog.outDebug("============EventCharacterDeleted============"); }
    void EventCharacterDeletedFinally(const EventInfoCharacter &) { sLog.outDebug("============EventCharacterDeletedFinally============"); }
    void EventCommandUsed(const EventInfoCommand &) { sLog.outDebug("============EventCommandUsed============"); }
    void EventCommandGMUsed(const EventInfoCommand &) { sLog.outDebug("============EventCommandGMUsed============"); }
    void EventCreatureSpawned(const EventInfoCreature &) { sLog.outDebug("============EventCreatureSpawned============"); }
    void EventCreatureDied(const EventInfoCreature &) { sLog.outDebug("============EventCreatureDied============"); }
    void EventGameEventStarted(const EventInfoGameEvent &) { sLog.outDebug("============EventGameEventStarted============"); }
    void EventGameEventStopped(const EventInfoGameEvent &) { sLog.outDebug("============EventGameEventStopped============"); }
    void EventPlayerLevelReached(const EventInfoPlayerLevel &) { sLog.outDebug("============EventPlayerLevelReached============"); }
    //    void EventPlayerSkillLevelReached(const EventInfoPlayerLevel &) { sLog.outDebug("============EventPlayerSkillLevelReached============"); }
    void EventPlayerReputationLevelReached(const EventInfoPlayerLevel &) { sLog.outDebug("============EventPlayerReputationLevelReached============"); }
    //    void EventPlayerPersonalArenaRatingGained(const EventInfoPlayerLevel &) { sLog.outDebug("============EventPlayerPersonalArenaRatingGained============"); }
    void EventPlayerTalentsReseted(const EventInfoPlayer &) { sLog.outDebug("============EventPlayerTalentsReseted============"); }
    void EventPlayerItemUsed(const EventInfoPlayerItem &) { sLog.outDebug("============EventPlayerItemUsed============"); }
    void EventPlayerItemEquipped(const EventInfoPlayerItem &) { sLog.outDebug("============EventPlayerItemEquipped============"); }
    void EventPlayerItemReceived(const EventInfoPlayerItem &) { sLog.outDebug("============EventPlayerItemReceived============"); }
    void EventPlayerItemColoredReceived(const EventInfoPlayerItem &) { sLog.outDebug("============EventPlayerItemColoredReceived============"); }
};
PrintEvents printEvents;
