#include <a_samp>
#include <YSI_Data\y_foreach>

#define MAX_ATTRIBUTE_LEVEL 100

forward IncrementAttributeLevel(PlayerAttributeType:type);

enum PlayerAttributeType {
    THIRST,
    HUNGER,
    SLEEP,
}

enum PlayerAttributeTypeMapping {
    PlayerAttributeType:MAPPING_TYPE,
    DEFAULT_INCREMENT,
    DEFAULT_INCREMENT_INTERVAL,
}

new PlayerAttributeType:attributesTypeMapping[PlayerAttributeType][PlayerAttributeTypeMapping] = {
    {THIRST, 1, 20000},
    {HUNGER, 1, 60000},
    {SLEEP, 1, 80000}
};

new playerAttribute[MAX_PLAYERS][PlayerAttributeType];
new attributeStateTimer[PlayerAttributeType];

new attributeUpdateCallback[PlayerAttributeType][32] = {
    {"OnPlayerThirstUpdate"},
    {"OnPlayerHungerUpdate"},
    {"OnPlayerSleepUpdate"}
};

new maxAttributeLevelReachedCb[PlayerAttributeType][32] = {
    {"OnMaxThirstLevelReached"},
    {"OnMaxHungerLevelReached"},
    {"OnMaxSleepLevelReached"}
};

stock _GetPlayerAttributeLevel(playerid, PlayerAttributeType:type)
{
    return playerAttribute[playerid][type];
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

    playerAttribute[playerid][type] = level;

    CallLocalFunction(attributeUpdateCallback[type], "ii", playerid, level);
    
    return 1;
}

public IncrementAttributeLevel(PlayerAttributeType:type)
{
    foreach(new playerid : Player) {
        _SetPlayerAttributeLevel(playerid, type, _GetPlayerAttributeLevel(playerid, type) + attributesTypeMapping[type][DEFAULT_INCREMENT]);
    }
    
    return 1;
}

stock InitialisePlayerAttributeState(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        _SetPlayerAttributeLevel(playerid, attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE], 0);
    }
    return 1;
}

stock DestroyPlayerAttributeState(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        _SetPlayerAttributeLevel(playerid, attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE], 0);
    }
    return 1;
}

stock InitialiseAttributeState()
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        new PlayerAttributeType:type = attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE];
        attributeStateTimer[type] = SetTimerEx("IncrementAttributeLevel", attributesTypeMapping[type][DEFAULT_INCREMENT_INTERVAL], true, "ii", _:type);
    }

    return 1;
}

stock DestroyAttributeState()
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        KillTimer(attributeStateTimer[attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE]]);
    }
    return 1;
}