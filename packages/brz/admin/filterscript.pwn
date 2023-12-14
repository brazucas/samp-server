#include <a_samp>
#include <YSI_Visual\y_commands>

public OnFilterScriptInit()
{
	print("========================BRZ_ADMIN STARTED========================");
	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_ADMIN STOPPED========================");
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	new playerName[MAX_PLAYER_NAME], Float:angle;
	GetPlayerName(playerid, playerName, sizeof(playerName));
	GetPlayerFacingAngle(playerid, angle);

	if (IsPlayerAdmin(playerid)) {
    	SetPlayerPosFindZ(playerid, fX, fY, fZ);
		printf("Player %s teleported to %f, %f, %f, heading: %f", playerName, fX, fY, fZ, angle);
	}

    return 1;
}

YCMD:logpos(playerid, const params[], help)
{
	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, sizeof(playerName));

	new Float:x, Float:y, Float:z, Float:angle;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	printf("Player %s position: %f, %f, %f, heading: %f", playerName, x, y, z, angle);

	return 1;
}