forward bool:IsPlayerLoggedIn(playerid);

public bool:IsPlayerLoggedIn(playerid)
{
	return _IsPlayerLoggedIn(playerid);
}

stock PublishPlayerLoginAction(playerid)
{
	CallRemoteFunction("OnBRZPlayerAuth", "d", playerid);

	return 1;
}