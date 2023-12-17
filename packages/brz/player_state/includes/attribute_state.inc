#include <a_samp>
#include <YSI_Data\y_foreach>

#define MAX_ATTRIBUTE_LEVEL 100

forward IncrementAttributeLevel(playerid, PlayerAttributeType:type);

static enum PlayerAttribute {
    LEVEL,
    TIMER,
}

enum PlayerAttributeType {
    THIRST,
    HUNGER,
}

enum PlayerAttributeTypeMapping {
    PlayerAttributeType:MAPPING_TYPE,
    DEFAULT_INCREMENT,
    DEFAULT_INCREMENT_INTERVAL,
}

new PlayerAttributeType:attributesTypeMapping[PlayerAttributeType][PlayerAttributeTypeMapping] = {
    {THIRST, 1, 20000},
    {HUNGER, 1, 60000}
};

new playerAttribute[MAX_PLAYERS][PlayerAttributeType][PlayerAttribute];
new attributeUpdateCallback[PlayerAttributeType][32] = {
    {"OnPlayerThirstUpdate"},
    {"OnPlayerHungerUpdate"}
};

new maxAttributeLevelReachedCb[PlayerAttributeType][32] = {
    {"OnMaxThirstLevelReached"},
    {"OnMaxHungerLevelReached"}
};

stock _GetPlayerAttributeLevel(playerid, PlayerAttributeType:type)
{
    return playerAttribute[playerid][type][LEVEL];
}

public IncrementAttributeLevel(playerid, PlayerAttributeType:type)
{
    _SetPlayerAttributeLevel(playerid, type, _GetPlayerAttributeLevel(playerid, type) + attributesTypeMapping[type][DEFAULT_INCREMENT]);
    return 1;
}

stock InitialisePlayerAttributeStates(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        InitialisePlayerAttributeState(playerid, attributesTypeMapping[typeIndex][MAPPING_TYPE]);
    }
    return 1;
}

static stock InitialisePlayerAttributeState(playerid, PlayerAttributeType:type)
{
    _SetPlayerAttributeLevel(playerid, type, 0);
    playerAttribute[playerid][type][TIMER] = SetTimerEx("IncrementAttributeLevel", attributesTypeMapping[type][DEFAULT_INCREMENT_INTERVAL], true, "ii", playerid, _:type);

    return 1;
}

stock DestroyPlayerAttributeStates(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        KillTimer(playerAttribute[playerid][attributesTypeMapping[typeIndex][MAPPING_TYPE]][TIMER]);
    }
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