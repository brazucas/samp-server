#include <a_samp>
#include <YSI_Coding\y_hooks>

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_STATE STARTED========================");
	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_PLAYER_STATE STOPPED========================");
	return 1;
}

hook OnBRZPlayerAuth(playerid)
{
	TogglePlayerSpectating(playerid, false);
	SetSpawnInfo(playerid, 0, 0, 1958.33, 1343.12, 15.36, 269.15, 26, 36, 28, 150, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}
