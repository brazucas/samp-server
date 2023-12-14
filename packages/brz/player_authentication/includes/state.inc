enum PlayerAttribute
{
	PLAYER_PASSWORD[64],
	PLAYER_NAME[MAX_PLAYER_NAME],
	bool:PLAYER_REGISTERED,
	bool:PLAYER_LOGGED_IN,
}

new PlayerData[MAX_PLAYERS][PlayerAttribute];

stock GetPlayerPassword(playerid, password[], len = sizeof(password))
{
    format(password, len, "%s", PlayerData[playerid][PLAYER_PASSWORD]);
    return 1;
}

stock SetPlayerPassword(playerid, const password[])
{
    format(PlayerData[playerid][PLAYER_PASSWORD], 64, "%s", password);
    return 1;
}

stock SetStatePlayerName(playerid, const playerName[])
{
    format(PlayerData[playerid][PLAYER_NAME], MAX_PLAYER_NAME, "%s", playerName);
    return 1;
}

stock GetStatePlayerName(playerid, playerName[], len = sizeof(playerName))
{
    format(playerName, len, "%s", PlayerData[playerid][PLAYER_NAME]);
    return 1;
}

stock SetIsPlayerLoggedIn(playerid, bool:loggedIn)
{
    PlayerData[playerid][PLAYER_LOGGED_IN] = loggedIn;
    return 1;
}

stock SetIsPlayerRegistered(playerid, bool:registered)
{
    PlayerData[playerid][PLAYER_REGISTERED] = registered;
    return 1;
}

stock bool:_IsPlayerLoggedIn(playerid)
{
    return PlayerData[playerid][PLAYER_LOGGED_IN];
}

stock bool:IsPlayerRegistered(playerid)
{
    return PlayerData[playerid][PLAYER_REGISTERED];
}

stock InitialisePlayer(playerid)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

    SetStatePlayerName(playerid, playerName);
    SetIsPlayerLoggedIn(playerid, false);
    SetIsPlayerRegistered(playerid, false);

	return 1;
}