#include <BRZ_Scripting\brz_apis>
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

forward FadePlayerScreen(playerid, color, FadeSpeed:speed, transparency);

static stock bool:IsPlayerScreenFaded(playerid)
{
	return playerFade[playerid][isFaded];
}

hook OnBRZPlayerAuth(playerid)
{
	playerFade[playerid][FadeTD] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_");
	PlayerTextDrawFont(playerid, playerFade[playerid][FadeTD], 1);
	PlayerTextDrawLetterSize(playerid, playerFade[playerid][FadeTD], 0.0, 50.0);
	PlayerTextDrawUseBox(playerid, playerFade[playerid][FadeTD], 1);
    PlayerTextDrawColor(playerid, playerFade[playerid][FadeTD], 0);
	PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], 0);

	playerFade[playerid][FadeTransparencyLevel] = 0;
	playerFade[playerid][isFaded] = false;

	return continue();
}

hook OnPlayerDisconnect(playerid, reason)
{
	PlayerTextDrawDestroy(playerid, playerFade[playerid][FadeTD]);
}

stock FadePlayerScreenToColor(playerid, colorWithTransparency, FadeSpeed:speed)
{
	new colorWithoutTransparency = colorWithTransparency - 255;

	PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], colorWithoutTransparency);
	PlayerTextDrawShow(playerid, playerFade[playerid][FadeTD]);

	SetTimerEx("FadePlayerScreen", 100, false, "dddd", playerid, colorWithoutTransparency, _:speed, 0);
}

public FadePlayerScreen(playerid, color, FadeSpeed:speed, transparency)
{
	new colorWithTransparency = color + transparency, 
		newTransparency = transparency;

	if (IsPlayerLoggedIn(playerid) && colorWithTransparency < (color + MAX_TRANSPARENCY_LEVEL) && !IsPlayerScreenFaded(playerid)) {
		if (speed == SLOW_FADE) newTransparency++;
		else if (speed == NORMAL_FADE) newTransparency += 15;
		else if (speed == FAST_FADE) newTransparency += 50;
		else newTransparency = 255;

		new newColor = color + newTransparency;

		if (newColor >= (color + MAX_TRANSPARENCY_LEVEL)) {
			playerFade[playerid][isFaded] = true;
			return 1;
		}

		PlayerTextDrawBoxColor(playerid, playerFade[playerid][FadeTD], newColor);
		PlayerTextDrawShow(playerid, playerFade[playerid][FadeTD]);

		SetTimerEx("ScreenFadeColor", 100, false, "ddd", playerid, newColor, _:speed, newTransparency);
	}

	return 1;
}