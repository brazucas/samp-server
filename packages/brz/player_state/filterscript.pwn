#include <a_samp>
#include <BRZ_Scripting\brz_apis>
#include <money_hud>
#include <hunger_hud>
#include <server_info_hud>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_foreach>

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_STATE STARTED========================");
	
	InitialiseServerHud();

	foreach (new playerid : Player) {
		if (IsPlayerLoggedIn(playerid)) {
			InitialisePlayerHud(playerid);
			ShowPlayerHuds(playerid);
		}
	}

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
	DestroyServerInfoHud();
	DestroyPlayerMoneyHudForAll();
	DestroyPlayerHungerHud();
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
		ShowPlayerHuds(playerid);
	}

	return 1;
}

stock ShowPlayerHuds(playerid)
{
	ShowServerInfoHud(playerid);
	ShowPlayerMoney(playerid);
	ShowPlayerHunger(playerid);
	return 1;
}