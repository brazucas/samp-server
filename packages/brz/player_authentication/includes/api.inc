stock PublishPlayerLoginAction(playerid)
{
	CallRemoteFunction("OnBRZPlayerAuth", "d", playerid);

	return 1;
}