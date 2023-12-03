#include <a_samp>
#include <BRZ_Core\feature_toggles>
#include <YSI_Coding\y_hooks>
#include <YSI_Visual\y_dialog>

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

enum PlayerAttribute
{
	PLAYER_PASSWORD[64],
	PLAYER_NAME[MAX_PLAYER_NAME],
	bool:PLAYER_REGISTERED,
	bool:PLAYER_LOGGED_IN,
}

new PlayerData[MAX_PLAYERS][PlayerAttribute];

public OnPlayerConnect(playerid)
{
	if (!IsFeatureEnabled(FF_AUTHENTICATION)) {
		printf("Player authentication is disabled. Skipping authentication for player %d", playerid);
		SendClientMessage(playerid, 0xFFFFFFFF, "Player authentication is disabled. Please try again later.");
		Kick(playerid);
		return 1;
	}

	if(!IsPlayerConnected(playerid)) return 0;

	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

	if (strcmp(playerName, PlayerData[playerid][PLAYER_NAME]) != 0) {
		InitialisePlayer(playerid);
	}

	BRZSpawnPlayer(playerid);

	if (PlayerData[playerid][PLAYER_REGISTERED] == false) {
		ShowRegisterDialog(playerid);
	} else {
		ShowLoginDialog(playerid);
	}
	
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	PlayerData[playerid][PLAYER_LOGGED_IN] = false;
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	BRZSpawnPlayer(playerid);
	return 1;
}

stock BRZSpawnPlayer(playerid)
{
	SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, true);

	return 1;
}

stock ShowRegisterDialog(playerid)
{
	inline Handler(response, listitem, string:inputtext[])
	{
		#pragma unused listitem

		if (response) {
			if(strlen(inputtext) < 3) {
				SendClientMessage(playerid, 0xFFFFFFFF, "Your password must be at least 3 characters long.");
				ShowRegisterDialog(playerid);
				return 1;
			}

			new playerName[MAX_PLAYER_NAME];
			GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

			format(PlayerData[playerid][PLAYER_PASSWORD], 64, "%s", inputtext);
			format(PlayerData[playerid][PLAYER_NAME], MAX_PLAYER_NAME, "%s", playerName);
			PlayerData[playerid][PLAYER_REGISTERED] = true;
			PlayerData[playerid][PLAYER_LOGGED_IN] = true;

			PublishPlayerLoginAction(playerid);
		} else {
			ShowRegisterDialog(playerid);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline Handler, DIALOG_STYLE_PASSWORD, "Welcome to BRZ.GG", "Please enter a password to register.", "Register", "Cancel");

	return 1;
}

stock ShowLoginDialog(playerid)
{
	inline Handler(response, listitem, string:inputtext[])
	{
		#pragma unused listitem

		if (response) {
			if (strcmp(inputtext, PlayerData[playerid][PLAYER_PASSWORD]) == 0) {
				PlayerData[playerid][PLAYER_LOGGED_IN] = true;
				PublishPlayerLoginAction(playerid);
			} else {
				SendClientMessage(playerid, 0xFFFFFFFF, "You have entered an incorrect password.");
				ShowLoginDialog(playerid);
			}
		} else {
			ShowLoginDialog(playerid);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline Handler, DIALOG_STYLE_PASSWORD, "Welcome back to BRZ.GG", "Please enter your password to login.", "Login", "Cancel");

	return 1;
}

stock PublishPlayerLoginAction(playerid)
{
	CallRemoteFunction("BRZPlayerAuthenticated", "d", playerid);

	return 1;
}

stock InitialisePlayer(playerid)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

	format(PlayerData[playerid][PLAYER_NAME], MAX_PLAYER_NAME, "%s", playerName);
	PlayerData[playerid][PLAYER_REGISTERED] = false;
	PlayerData[playerid][PLAYER_LOGGED_IN] = false;

	return 1;
}