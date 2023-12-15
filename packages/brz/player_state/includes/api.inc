forward SetPlayerHungerLevel(playerid, level);
forward GetPlayerHungerLevel(playerid);

public SetPlayerHungerLevel(playerid, level)
{
    _SetPlayerAttributeLevel(playerid, HUNGER, level);
    return 1;
}

public GetPlayerHungerLevel(playerid)
{
    return _GetPlayerAttributeLevel(playerid, HUNGER);
}