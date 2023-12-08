#include <BRZ_SAMP\samp_dialogs>

forward ShowRegisterDialog(playerid);
forward ShowLoginDialog(playerid);

stock BRZSpawnPlayer(playerid)
{
	SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	TogglePlayerSpectating(playerid, true);

	return 1;
}

public ShowRegisterDialog(playerid)
{
	inline Handler(response, listitem, string:inputtext[])
	{
		#pragma unused listitem

		if (response) {
			if(strlen(inputtext) < 3) {
				ShowAlert(playerid, "Invalid Password", "Your password must be at least 3 characters long.", "ShowRegisterDialog");
				return 1;
			}

			new playerName[MAX_PLAYER_NAME];
			GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

			SetPlayerPassword(playerid, inputtext);
			SetStatePlayerName(playerid, playerName);

			SetIsPlayerLoggedIn(playerid, true);
			SetIsPlayerRegistered(playerid, true);

			PublishPlayerLoginAction(playerid);
		} else {
			ShowRegisterDialog(playerid);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline Handler, DIALOG_STYLE_PASSWORD, "Welcome to BRZ.GG", "Please enter a password to register.", "Register", "Cancel");

	return 1;
}

public ShowLoginDialog(playerid)
{
	inline Handler(response, listitem, string:inputtext[])
	{
		#pragma unused listitem

		if (response) {
			new password[64];
			GetPlayerPassword(playerid, password, 64);

			if (strcmp(inputtext, password) == 0) {
				SetIsPlayerLoggedIn(playerid, true);
				PublishPlayerLoginAction(playerid);
			} else {
				ShowAlert(playerid, "Incorrect Password", "You have entered an incorrect password.", "ShowLoginDialog");
			}
		} else {
			ShowLoginDialog(playerid);
		}
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline Handler, DIALOG_STYLE_PASSWORD, "Welcome back to BRZ.GG", "Please enter your password to login.", "Login", "Cancel");

	return 1;
}