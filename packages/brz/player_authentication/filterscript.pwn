#include <a_samp>
#include <BRZ_Core\feature_toggles>
#include <state>
#include <api>
#include <samp_impl>

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_AUTHENTICATION STARTED========================");
	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_PLAYER_AUTHENTICATION STOPPED========================");
	return 1;
}

public OnPlayerConnect(playerid)
{
	if (!IsFeatureEnabled(FF_AUTHENTICATION)) {
		printf("Player authentication is disabled. Skipping authentication for player %d", playerid);
		SendClientMessage(playerid, 0xFFFFFFFF, "Player authentication is disabled. Please try again later.");
		Kick(playerid);
		return 1;
	}

	if(!IsPlayerConnected(playerid)) return 0;

	new playerName[MAX_PLAYER_NAME], storedPlayerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);
	GetStatePlayerName(playerid, storedPlayerName, MAX_PLAYER_NAME);

	if (strcmp(playerName, storedPlayerName) != 0) {
		InitialisePlayer(playerid);
	}

	StateSpawnPlayer(playerid);

	if (IsPlayerRegistered(playerid)) {
		ShowLoginDialog(playerid);
	} else {
		ShowRegisterDialog(playerid);
	}
	
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	SetIsPlayerLoggedIn(playerid, false);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	StateSpawnPlayer(playerid);
	return 1;
}