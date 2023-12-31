#include <a_samp>
#include <BRZ_Scripting\brz_apis>
#include <huds\money_hud>
#include <huds\hunger_hud>
#include <huds\thirst_hud>
#include <huds\server_info_hud>
#include <attribute_state>
#include <api>
#include <YSI_Coding\y_hooks>

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_STATE STARTED========================");
	
	InitialiseServerHud();
	InitialiseAttributeState();

	foreach (new playerid : Player) {
		if (IsPlayerLoggedIn(playerid)) {
			InitialisePlayerHuds(playerid);
			ShowPlayerHuds(playerid);

			InitialisePlayerAttributeState(playerid);
		}
	}

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	DestroyPlayerMoneyHud(playerid);
	DestroyPlayerHungerHud(playerid);
	DestroyPlayerThirstHud(playerid);

	DestroyPlayerAttributeState(playerid);
	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_PLAYER_STATE STOPPED========================");
	DestroyServerInfoHud();

	DestroyPlayerMoneyHudForAll();
	DestroyPlayerHungerHudForAll();
	DestroyPlayerThirstHudForAll();
	DestroyAttributeState();
	return 1;
}

hook OnBRZPlayerAuth(playerid)
{
	TogglePlayerSpectating(playerid, false);

	SetSpawnInfo(playerid, 0, 0, 1743.248901, -1948.481933, 14.117187, 178.015930, 26, 36, 28, 150, 0, 0);
	SpawnPlayer(playerid);

	InitialisePlayerHuds(playerid);
	InitialisePlayerAttributeState(playerid);

	continue();
}

public OnPlayerSpawn(playerid)
{
	if (IsPlayerLoggedIn(playerid)) {
		ShowPlayerHuds(playerid);
	}

	return 1;
}

stock InitialisePlayerHuds(playerid)
{
	InitialiseMoneyHud(playerid);
	InitialiseHungerHud(playerid);
	InitialiseThirstHud(playerid);

	return 1;
}

stock ShowPlayerHuds(playerid)
{
	ShowServerInfoHud(playerid);
	ShowPlayerMoney(playerid);
	_ShowPlayerHungerHud(playerid);
	ShowPlayerThirst(playerid);
	return 1;
}