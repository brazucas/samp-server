stock PublishPlayerLoginAction(playerid)
{
	CallRemoteFunction("OnBRZPlayerAuthenticated", "d", playerid);

	return 1;
}