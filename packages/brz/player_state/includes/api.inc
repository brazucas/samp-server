forward SetPlayerHungerLevel(playerid, level);
forward GetPlayerHungerLevel(playerid);

public SetPlayerHungerLevel(playerid, level)
{
    _SetPlayerHungerLevel(playerid, level);
    return 1;
}

public GetPlayerHungerLevel(playerid)
{
    return _GetPlayerHungerLevel(playerid);
}