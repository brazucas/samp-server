stock bool:IsPlayerLoggedIn(playerid)
{
    return bool:CallRemoteFunction("IsPlayerLoggedIn", "d", playerid);
}