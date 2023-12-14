#include <a_samp>
#include <BRZ_Scripting\brz_apis>
#include <hud>
#include <YSI_Coding\y_hooks>

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_STATE STARTED========================");
	InitialiseServerHud();
	return 1;
}

public OnPlayerConnect(playerid)
{
	InitialisePlayerHud(playerid);
	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_PLAYER_STATE STOPPED========================");
	return 1;
}

hook OnBRZPlayerAuth(playerid)
{
	printf("OnBRZPlayerAuth(%d)", playerid);
	TogglePlayerSpectating(playerid, false);

	SetSpawnInfo(playerid, 0, 0, 1743.248901, -1948.481933, 14.117187, 178.015930, 26, 36, 28, 150, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if (IsPlayerLoggedIn(playerid)) {
		ShowHudForPlayer(playerid);
	}

	return 1;
}