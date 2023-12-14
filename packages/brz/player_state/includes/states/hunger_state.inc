#include <a_samp>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_foreach>

#define MAX_HUNGER_LEVEL 100
#define HUNGER_LEVEL_INCREMENT 1
#define HUNGER_LEVEL_INCREMENT_INTERVAL_SECONDS 1

forward IncrementHungerLevel(playerid);

static enum PlayerHunger {
    HungerLevel,
    HungerTimer,
}

new playerHunger[MAX_PLAYERS][PlayerHunger];

public IncrementHungerLevel(playerid)
{
    _SetPlayerHungerLevel(playerid, _GetPlayerHungerLevel(playerid) + HUNGER_LEVEL_INCREMENT);
    return 1;
}

stock InitialisePlayerHungerState(playerid)
{
    _SetPlayerHungerLevel(playerid, 0);
    playerHunger[playerid][HungerTimer] = SetTimerEx("IncrementHungerLevel", HUNGER_LEVEL_INCREMENT_INTERVAL_SECONDS * 1000, true, "i", playerid);

    return 1;
}

stock DestroyPlayerHungerState(playerid)
{
    KillTimer(playerHunger[playerid][HungerTimer]);
    return 1;
}

stock DestroyHungerStateForAll()
{
    foreach(new playerid : Player) {
        DestroyPlayerHungerState(playerid);
    }
    return 1;
}

stock _SetPlayerHungerLevel(playerid, level)
{
    if (level < 0) {
        level = 0;
    }

    if (level > MAX_HUNGER_LEVEL) {
        level = MAX_HUNGER_LEVEL;
    }

    playerHunger[playerid][HungerLevel] = level;

    CallLocalFunction("OnPlayerHungerUpdate", "ii", playerid, level);
    return 1;
}

stock _GetPlayerHungerLevel(playerid)
{
    return playerHunger[playerid][HungerLevel];
}