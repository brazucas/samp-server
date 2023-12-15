#include <a_samp>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_foreach>

#define MAX_THIRST_LEVEL 100
#define THIRST_LEVEL_INCREMENT 1
#define THIRST_LEVEL_INCREMENT_INTERVAL_SECONDS 1

forward IncrementThirstLevel(playerid);

static enum PlayerThirst {
    ThirstLevel,
    ThirstTimer,
}

new playerThirst[MAX_PLAYERS][PlayerThirst];

public IncrementThirstLevel(playerid)
{
    _SetPlayerThirstLevel(playerid, _GetPlayerThirstLevel(playerid) + THIRST_LEVEL_INCREMENT);
    return 1;
}

stock InitialisePlayerThirstState(playerid)
{
    _SetPlayerThirstLevel(playerid, 0);
    playerThirst[playerid][ThirstTimer] = SetTimerEx("IncrementThirstLevel", THIRST_LEVEL_INCREMENT_INTERVAL_SECONDS * 1000, true, "i", playerid);

    return 1;
}

stock DestroyPlayerThirstState(playerid)
{
    KillTimer(playerThirst[playerid][ThirstTimer]);
    return 1;
}

stock DestroyThirstStateForAll()
{
    foreach(new playerid : Player) {
        DestroyPlayerThirstState(playerid);
    }
    return 1;
}

stock _SetPlayerThirstLevel(playerid, level)
{
    if (level < 0) {
        level = 0;
    }

    if (level > MAX_THIRST_LEVEL) {
        level = MAX_THIRST_LEVEL;
    }

    playerThirst[playerid][ThirstLevel] = level;

    CallLocalFunction("OnPlayerThirstUpdate", "ii", playerid, level);
    return 1;
}

stock _GetPlayerThirstLevel(playerid)
{
    return playerThirst[playerid][ThirstLevel];
}