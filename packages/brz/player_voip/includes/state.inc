enum PlayerAttribute
{
	bool:VOIP_SUPPORTED,
	bool:VOIP_ENABLED,
    bool:MIC_AVAIABLE,
    bool:MIC_ENABLED
}

new PlayerData[MAX_PLAYERS][PlayerAttribute];

stock SetVoipSupported(playerid, bool:voip_supported)
{
    PlayerData[playerid][VOIP_SUPPORTED] = voip_supported;
    return 1;
}

stock IsVoipSupported(playerid)
{
    return PlayerData[playerid][VOIP_SUPPORTED];
}

stock SetVoipEnabled(playerid, bool:voip_enabled)
{
    PlayerData[playerid][VOIP_ENABLED] = voip_enabled;
    return 1;
}

stock IsVoipEnabled(playerid)
{
    return PlayerData[playerid][VOIP_ENABLED];
}

stock SetMicAvailable(playerid, bool:mic_available)
{
    PlayerData[playerid][MIC_AVAIABLE] = mic_available;
    return 1;
}

stock IsMicAvailable(playerid)
{
    return PlayerData[playerid][MIC_AVAIABLE];
}

stock SetMicEnabled(playerid, bool:mic_enabled)
{
    PlayerData[playerid][MIC_ENABLED] = mic_enabled;
    return 1;
}

stock IsMicEnabled(playerid)
{
    return PlayerData[playerid][MIC_ENABLED];
}