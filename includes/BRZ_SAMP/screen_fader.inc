#include <BRZ_Scripting\brz_apis>
#include <YSI_Data\y_foreach>
#include <YSI_Coding\y_hooks>

#define MAX_TRANSPARENCY_LEVEL 255
#define FADE_COLOR_BLACK 0x000000FF

static enum PlayerFadeAttribute
{
	PlayerText:FadeTD,
	FadeTransparencyLevel,
	bool:isFaded,
}

new playerFade[MAX_PLAYERS][PlayerFadeAttribute];

enum FadeSpeed
{
	SLOW_FADE,
	NORMAL_FADE,
	FAST_FADE,
};

forward FadePlayerScreenIterator(playerid, color, FadeSpeed:speed, transparency);

static stock bool:IsPlayerScreenFaded(playerid)
{
	return playerFade[playerid][isFaded];
}

#if !defined IS_GAMEMODE
	hook OnFilterScriptExit()
	{
		foreach(new playerid : Player) {
			DestroyPlayerFadeTD(playerid);
		}
		return 1;
	}
#endif

#if !defined IS_GAMEMODE
	hook OnFilterScriptInit()
	{
		foreach(new playerid : Player) {
			CreatePlayerFadeTD(playerid);
		}
		return 1;
	}
#endif

hook OnPlayerConnect(playerid)
{
	return CreatePlayerFadeTD(playerid);
}

hook OnPlayerDisconnect(playerid, reason)
{
	return DestroyPlayerFadeTD(playerid);
}

static stock CreatePlayerFadeTD(playerid)
{
	playerFade[playerid][FadeTD] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_");
	PlayerTextDrawFont(playerid, playerFade[playerid][FadeTD], 1);
	PlayerTextDrawLetterSize(playerid, playerFade[playerid][FadeTD], 0.0, 50.0);
	PlayerTextDrawUseBox(playerid, playerFade[playerid][FadeTD], 1);
    PlayerTextDrawColor(playerid, playerFade[playerid][FadeTD], 0);
	PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], 0);

	playerFade[playerid][FadeTransparencyLevel] = 0;
	playerFade[playerid][isFaded] = false;
	return 1;
}

static stock DestroyPlayerFadeTD(playerid)
{
	PlayerTextDrawDestroy(playerid, playerFade[playerid][FadeTD]);
	return 1;
}

stock FadePlayerScreenToColor(playerid, colorWithTransparency, FadeSpeed:speed)
{
	PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], colorWithTransparency + MAX_TRANSPARENCY_LEVEL);
	PlayerTextDrawShow(playerid, playerFade[playerid][FadeTD]);

	playerFade[playerid][isFaded] = false;

	SetTimerEx("FadePlayerScreenIterator", 100, false, "dddd", playerid, colorWithTransparency, _:speed, 0);
}

public FadePlayerScreenIterator(playerid, color, FadeSpeed:speed, transparency)
{
	if (speed == SLOW_FADE) transparency += 1;
	else if (speed == NORMAL_FADE) transparency += 15;
	else if (speed == FAST_FADE) transparency += 50;
	else transparency += 1;

	new isAtMaximumTransparency = transparency >= MAX_TRANSPARENCY_LEVEL;

	if (IsPlayerLoggedIn(playerid) && !isAtMaximumTransparency && !IsPlayerScreenFaded(playerid)) {

		new newColor = color + transparency;

		if (isAtMaximumTransparency) {
			newColor = color;
			playerFade[playerid][isFaded] = true;
		}

		PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], newColor);
		PlayerTextDrawShow(playerid, playerFade[playerid][FadeTD]);

		if (!isAtMaximumTransparency) {
			SetTimerEx("FadePlayerScreenIterator", 100, false, "dddd", playerid, color, _:speed, transparency);
		}
	}

	return 1;
}

stock ClearPlayerScreenFade(playerid)
{
	PlayerTextDrawHide(playerid, playerFade[playerid][FadeTD]);
	playerFade[playerid][isFaded] = false;
}