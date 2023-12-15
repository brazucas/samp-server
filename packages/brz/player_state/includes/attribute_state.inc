#include <a_samp>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_foreach>

#define MAX_ATTRIBUTE_LEVEL 100
#define DEFAULT_ATTRIBUTE_INCREMENT 1
#define DEFAULT_ATTRIBUTE_INCREMENT_INTERVAL_SECONDS 1

forward IncrementAttributeLevel(playerid, PlayerAttributeType:type);

static enum PlayerAttribute {
    LEVEL,
    TIMER,
}

enum PlayerAttributeType {
    THIRST,
    HUNGER,
}

new playerAttribute[MAX_PLAYERS][PlayerAttributeType][PlayerAttribute];
new attributeUpdateCallback[PlayerAttributeType][32] = {
    {"OnPlayerThirstUpdate"},
    {"OnPlayerHungerUpdate"}
};

new maxAttributeLevelReachedCb[PlayerAttributeType][32] = {
    {"OnPlayerMaxThirstLevelReached"},
    {"OnPlayerMaxHungerLevelReached"}
};

public IncrementAttributeLevel(playerid, PlayerAttributeType:type)
{
    _SetPlayerAttributeLevel(playerid, type, _GetPlayerAttributeLevel(playerid, type) + DEFAULT_ATTRIBUTE_INCREMENT);
    return 1;
}

stock InitialisePlayerAttributeStates(playerid)
{
    InitialisePlayerAttributeState(playerid, THIRST);
    InitialisePlayerAttributeState(playerid, HUNGER);
    return 1;
}

static stock InitialisePlayerAttributeState(playerid, PlayerAttributeType:type)
{
    _SetPlayerAttributeLevel(playerid, type, 0);
    playerAttribute[playerid][type][TIMER] = SetTimerEx("IncrementAttributeLevel", DEFAULT_ATTRIBUTE_INCREMENT_INTERVAL_SECONDS * 1000, true, "ii", playerid, type);

    return 1;
}

stock DestroyPlayerAttributeStates(playerid)
{
    KillTimer(playerAttribute[playerid][HUNGER][TIMER]);
    KillTimer(playerAttribute[playerid][THIRST][TIMER]);
    return 1;
}

stock DestroyAttributeStateForAll()
{
    foreach(new playerid : Player) {
        DestroyPlayerAttributeStates(playerid);
    }
    return 1;
}

stock _SetPlayerAttributeLevel(playerid, PlayerAttributeType:type, level)
{
    if (level < 0) {
        level = 0;
    }

    if (level > MAX_ATTRIBUTE_LEVEL) {
        level = MAX_ATTRIBUTE_LEVEL;

        CallLocalFunction(maxAttributeLevelReachedCb[type], "i", playerid);
    }

    playerAttribute[playerid][type][LEVEL] = level;

    CallLocalFunction(attributeUpdateCallback[type], "ii", playerid, level);
    
    return 1;
}

stock _GetPlayerAttributeLevel(playerid, PlayerAttributeType:type)
{
    return playerAttribute[playerid][type][LEVEL];
}