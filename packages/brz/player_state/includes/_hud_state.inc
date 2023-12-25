#include <a_samp>
#include <YSI_Data\y_foreach>

#define MAX_ATTRIBUTE_LEVEL 100

forward IncrementAttributeLevel(PlayerAttributeType:type);

static enum PlayerAttributeType {
    THIRST,
    HUNGER,
    SLEEP,
}

static enum PlayerAttributeTypeMapping {
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

stock _SetPlayerAttribute(playerid, PlayerAttributeType:type, value)
{
    new _:newValue = value;

    if (value < 0) {
        newValue = 0;
    }

    if (value > MAX_ATTRIBUTE_LEVEL) {
        newValue = MAX_ATTRIBUTE_LEVEL;
        CallLocalFunction(maxAttributeLevelReachedCb[type], "i", playerid);
    }

    playerAttribute[playerid][type] = newValue;

    CallLocalFunction(attributeUpdateCallback[type], "ii", playerid, newValue);
    
    return 1;
}

public IncrementAttributeLevel(PlayerAttributeType:type)
{
    foreach(new playerid : Player) {
        _SetPlayerAttribute(playerid, type, _GetPlayerAttributeLevel(playerid, type) + attributesTypeMapping[type][DEFAULT_INCREMENT]);
    }
    
    return 1;
}

stock InitPlayerHudState(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        _SetPlayerAttribute(playerid, attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE], 0);
    }
    return 1;
}

stock DestroyPlayerHudState(playerid)
{
    for(new typeIndex = 0; typeIndex < sizeof(attributesTypeMapping); typeIndex++) {
        _SetPlayerAttribute(playerid, attributesTypeMapping[PlayerAttributeType:typeIndex][MAPPING_TYPE], 0);
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

#include <state_listeners\sleep_listener>
#include <state_listeners\hunger_thirst_listener>
#include <state_listeners\afk_listener>