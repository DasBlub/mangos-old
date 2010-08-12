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

void EventSystemMgr::TriggerCommandEvent(EventType type, const ChatCommand &command, uint32 accountId,
                                         const Player *player, uint32 time)
{
    EventInfoCommand event(type, command, accountId, player, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_COMMAND_USED:
            CommandEvents.InformListener(event, &ListenerCommand::EventCommandUsed);
            break;
        case EVENT_COMMAND_GM_USED:
            CommandEvents.InformListener(event, &ListenerCommand::EventCommandGMUsed);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerBossEvent(EventType type, const Creature &boss, uint32 time)
{
    EventInfoCreature event(type, boss, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_BOSS_AGGRO:
            BossEvents.InformListener(event, &ListenerBoss::EventBossAggro);
            break;
        case EVENT_BOSS_DIED:
            BossEvents.InformListener(event, &ListenerBoss::EventBossDied);
            break;
        case EVENT_BOSS_EVADED:
            BossEvents.InformListener(event, &ListenerBoss::EventBossEvaded);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerCreatureEvent(EventType type, const Creature &creature, uint32 time)
{
    EventInfoCreature event(type, creature, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_CREATURE_SPAWNED:
            CreatureEvents.InformListener(event, &ListenerCreature::EventCreatureSpawned);
            break;
        case EVENT_CREATURE_DIED:
            CreatureEvents.InformListener(event, &ListenerCreature::EventCreatureDied);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerCharacterEvent(EventType type, const std::string &name, uint32 accountId,
                                           const std::string &ip, const std::string &oldname, uint32 time)
{
    EventInfoCharacter event(type, name, accountId, ip, oldname, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_CHARACTER_CREATED:
            CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterCreated);
            break;
        case EVENT_CHARACTER_RENAMED:
            CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterRenamed);
            break;
        case EVENT_CHARACTER_DELETED:
            CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterDeleted);
            break;
        case EVENT_CHARACTER_DELETED_FINALLY:
            CharacterEvents.InformListener(event, &ListenerCharacter::EventCharacterDeletedFinally);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerPlayerLoginoutEvent(EventType type, const std::string &name, uint32 accountId,
                                                const std::string &ip, uint32 time)
{
    EventInfoCharacter event(type, name, accountId, ip, "", time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_PLAYER_LOGIN:
            PlayerLoginoutEvents.InformListener(event, &ListenerPlayerLoginout::EventPlayerLogin);
            break;
        case EVENT_PLAYER_LOGOUT:
            PlayerLoginoutEvents.InformListener(event, &ListenerPlayerLoginout::EventPlayerLogout);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerGameEventEvent(EventType type, uint16 id, const GameEventData &gameEvent, uint32 time)
{
    EventInfoGameEvent event(type, id, gameEvent, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_GAMEEVENT_STARTED:
            GameEventEvents.InformListener(event, &ListenerGameEvent::EventGameEventStarted);
            break;
        case EVENT_GAMEEVENT_STOPPED:
            GameEventEvents.InformListener(event, &ListenerGameEvent::EventGameEventStopped);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerBattleGroundEvent(EventType type, const BattleGround &battleGround, uint32 winnerFaction,
                                              const ArenaTeam *alliance, const ArenaTeam *horde, uint32 time)
{
    EventInfoBattleGround event(type, battleGround, winnerFaction, alliance, horde, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_BATTLEGROUND_STARTED:
            BattleGroundEvents.InformListener(event, &ListenerBattleGround::EventBattleGroundStarted);
            break;
        case EVENT_BATTLEGROUND_ENDED:
            BattleGroundEvents.InformListener(event, &ListenerBattleGround::EventBattleGroundEnded);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerPlayerLevelEvent(EventType type, const Player &player, uint32 level, uint32 increase, uint32 time)
{
    EventInfoPlayerLevel event(type, player, level, increase, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_PLAYER_LEVEL_REACHED:
            PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerLevelReached);
            break;
//        case EVENT_PLAYER_SKILL_LEVEL_REACHED:
//            PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerSkillLevelReached);
//            break;
        case EVENT_PLAYER_REPUTATION_LEVEL_REACHED:
            PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerReputationLevelReached);
            break;
//        case EVENT_PLAYER_PERSONAL_ARENA_RATING_GAINED:
//            PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerPersonalArenaRatingGained);
//            break;
        case EVENT_PLAYER_TALENT_RESET:
            PlayerLevelEvents.InformListener(event, &ListenerPlayerLevel::EventPlayerTalentReset);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

void EventSystemMgr::TriggerArenaTeamEvent(EventType type, const ArenaTeam &team, const Player *player, uint32 increase, uint32 time)
{
    EventInfoArenaTeam event(type, team, player, increase, time);
    sEventSystemMgr.PrintEventToLog(event);
    switch (type) {
        case EVENT_ARENA_TEAM_CREATED:
            ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamCreated);
            break;
        case EVENT_ARENA_TEAM_DISBANDED:
            ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamDisbanded);
            break;
        case EVENT_ARENA_TEAM_RATING_GAINED:
            ArenaTeamEvents.InformListener(event, &ListenerArenaTeam::EventArenaTeamRatingGained);
            break;
        default:
            sLog.outError("Could not find corresponding listener function for %s", NameOfEventType(type).c_str());
            break;
    }
}

// Regex to parse enum values:
// (EVENT_.*),.*  ->  case \1: return \"\1\";
std::string EventSystemMgr::NameOfEventType(EventType type) const
{
    switch (type)
    {
        case EVENT_COMMAND_USED: return "EVENT_COMMAND_USED";
        case EVENT_COMMAND_GM_USED: return "EVENT_COMMAND_GM_USED";

        case EVENT_CHARACTER_CREATED: return "EVENT_CHARACTER_CREATED";
        case EVENT_CHARACTER_RENAMED: return "EVENT_CHARACTER_RENAMED";
        case EVENT_CHARACTER_DELETED: return "EVENT_CHARACTER_DELETED";
        case EVENT_CHARACTER_DELETED_FINALLY: return "EVENT_CHARACTER_DELETED_FINALLY";

        case EVENT_CREATURE_SPAWNED: return "EVENT_CREATURE_SPAWNED";
        case EVENT_CREATURE_DIED: return "EVENT_CREATURE_DIED";

        case EVENT_BOSS_AGGRO: return "EVENT_BOSS_AGGRO";
        case EVENT_BOSS_EVADED: return "EVENT_BOSS_EVADED";
        case EVENT_BOSS_DIED: return "EVENT_BOSS_DIED";

        case EVENT_GAMEEVENT_STARTED: return "EVENT_GAMEEVENT_STARTED";
        case EVENT_GAMEEVENT_STOPPED: return "EVENT_GAMEEVENT_STOPPED";

        case EVENT_BATTLEGROUND_STARTED: return "EVENT_BATTLEGROUND_STARTED";
        case EVENT_BATTLEGROUND_ENDED: return "EVENT_BATTLEGROUND_ENDED";

        case EVENT_PLAYER_LOGIN: return "EVENT_PLAYER_LOGIN";
        case EVENT_PLAYER_LOGOUT: return "EVENT_PLAYER_LOGOUT";

        case EVENT_PLAYER_LEVEL_REACHED: return "EVENT_PLAYER_LEVEL_REACHED";
        //    case EVENT_PLAYER_SKILL_LEVEL_REACHED: return "EVENT_PLAYER_SKILL_LEVEL_REACHED";
        case EVENT_PLAYER_REPUTATION_LEVEL_REACHED: return "EVENT_PLAYER_REPUTATION_LEVEL_REACHED";
        //    case EVENT_PLAYER_PERSONAL_ARENA_RATING_GAINED: return "EVENT_PLAYER_PERSONAL_ARENA_RATING_GAINED";
        case EVENT_PLAYER_TALENT_RESET: return "EVENT_PLAYER_TALENT_RESET";

        //    case EVENT_PLAYER_SPELL_CAST: return "EVENT_PLAYER_SPELL_CAST";
        case EVENT_PLAYER_SPELL_LEARNED: return "EVENT_PLAYER_SPELL_LEARNED";
        case EVENT_PLAYER_DAMAGE_DEALT: return "EVENT_PLAYER_DAMAGE_DEALT";

        case EVENT_PLAYER_TELEPORTED: return "EVENT_PLAYER_TELEPORTED";
        //    case EVENT_PLAYER_FLIGHT_PATH_TAKEN: return "EVENT_PLAYER_FLIGHT_PATH_TAKEN";
        case EVENT_PLAYER_INSTANCE_ENTERED: return "EVENT_PLAYER_INSTANCE_ENTERED";
        case EVENT_PLAYER_INSTANCE_LEAVED: return "EVENT_PLAYER_INSTANCE_LEAVED";
        case EVENT_PLAYER_INSTANCE_ID_RECEIVED: return "EVENT_PLAYER_INSTANCE_ID_RECEIVED";

        case EVENT_PLAYER_REVIVED: return "EVENT_PLAYER_REVIVED";
        case EVENT_PLAYER_DIED: return "EVENT_PLAYER_DIED";
        case EVENT_PLAYER_KILLED_BY_PLAYER: return "EVENT_PLAYER_KILLED_BY_PLAYER";
        case EVENT_PLAYER_KILLED_BY_CREATURE: return "EVENT_PLAYER_KILLED_BY_CREATURE";
        case EVENT_PLAYER_KILLED_OTHER_PLAYER: return "EVENT_PLAYER_KILLED_OTHER_PLAYER";
        case EVENT_PLAYER_KILLED_OTHER_CREATURE: return "EVENT_PLAYER_KILLED_OTHER_CREATURE";

        case EVENT_PLAYER_ITEM_USED: return "EVENT_PLAYER_ITEM_USED";
        case EVENT_PLAYER_ITEM_EQUIPED: return "EVENT_PLAYER_ITEM_EQUIPED";
        case EVENT_PLAYER_ITEM_RECEIVED: return "EVENT_PLAYER_ITEM_RECEIVED";
        case EVENT_PLAYER_ITEM_COLORED_RECEIVED: return "EVENT_PLAYER_ITEM_COLORED_RECEIVED";

        case EVENT_PLAYER_QUEST_COMPLETED: return "EVENT_PLAYER_QUEST_COMPLETED";
        case EVENT_PLAYER_QUEST_ABANDONED: return "EVENT_PLAYER_QUEST_ABANDONED";
        case EVENT_PLAYER_QUEST_ITEM_COLLECTED: return "EVENT_PLAYER_QUEST_ITEM_COLLECTED";

        case EVENT_PLAYER_BATTLEGROUND_JOINED: return "EVENT_PLAYER_BATTLEGROUND_JOINED";
        case EVENT_PLAYER_BATTLEGROUND_LEAVED: return "EVENT_PLAYER_BATTLEGROUND_LEAVED";
        case EVENT_PLAYER_BATTLEGROUND_WON: return "EVENT_PLAYER_BATTLEGROUND_WON";
        case EVENT_PLAYER_BATTLEGROUND_LOST: return "EVENT_PLAYER_BATTLEGROUND_LOST";
        case EVENT_PLAYER_DUELL_WON: return "EVENT_PLAYER_DUELL_WON";
        case EVENT_PLAYER_DUELL_LOST: return "EVENT_PLAYER_DUELL_LOST";
        case EVENT_PLAYER_ARENA_TEAM_JOINED: return "EVENT_PLAYER_ARENA_TEAM_JOINED";
        case EVENT_PLAYER_ARENA_TEAM_LEAVED: return "EVENT_PLAYER_ARENA_TEAM_LEAVED";

        //    case EVENT_PLAYER_GAMEOBJECT_USED: return "EVENT_PLAYER_GAMEOBJECT_USED";
        case EVENT_PLAYER_MAIL_SEND: return "EVENT_PLAYER_MAIL_SEND";
        case EVENT_PLAYER_TRADE_ACCEPTED: return "EVENT_PLAYER_TRADE_ACCEPTED";
        case EVENT_PLAYER_TRADE_SPECIAL_ACCEPTED: return "EVENT_PLAYER_TRADE_SPECIAL_ACCEPTED";
        case EVENT_PLAYER_MERCHANT_TRADED: return "EVENT_PLAYER_MERCHANT_TRADED";

        case EVENT_PLAYER_MONEY_GAINED: return "EVENT_PLAYER_MONEY_GAINED";
        case EVENT_PLAYER_MONEY_LOOTED: return "EVENT_PLAYER_MONEY_LOOTED";

        case EVENT_LOOT_ITEM_EPIC_DROPPED: return "EVENT_LOOT_ITEM_EPIC_DROPPED";

        case EVENT_RAID_CREATED: return "EVENT_RAID_CREATED";
        case EVENT_RAID_DISBANDED: return "EVENT_RAID_DISBANDED";

        case EVENT_ARENA_TEAM_CREATED: return "EVENT_ARENA_TEAM_CREATED";
        case EVENT_ARENA_TEAM_DISBANDED: return "EVENT_ARENA_TEAM_DISBANDED";
        case EVENT_ARENA_TEAM_RATING_GAINED: return "EVENT_ARENA_TEAM_RATING_GAINED";

        //    case EVENT_AUCTION_CREATED: return "EVENT_AUCTION_CREATED";

        default: return "Eventname unknown";
    }
    return "Eventname unknown";
}

void EventSystemMgr::PrintEventToLog(const EventInfo& event) const
{
    sLog.outDebug("====================\nEvent occured: type=%s", NameOfEventType(event.type).c_str());
//    sLog.outDebug("Event occured: type=%s" val1=%d val2=%d obj1=%s[%s%d] obj2=%s[%s%d] time=%d",
//                   NameOfEventType(event.type).c_str(), event.val1, event.val2,
//                   obj1 ? obj1->GetName() : "NULL", obj1 ? (obj1->GetTypeId() == TYPEID_PLAYER ? "P#":"C#") : "", obj1 ? obj1->GetGUIDLow() : 0,
//                   obj2 ? obj2->GetName() : "NULL", obj2 ? (obj2->GetTypeId() == TYPEID_PLAYER ? "P#":"C#") : "", obj2 ? obj2->GetGUIDLow() : 0,
//                   event.time);
}
