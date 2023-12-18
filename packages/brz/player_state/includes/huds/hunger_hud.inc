#include <YSI_Data\y_foreach>

forward OnPlayerHungerUpdate(playerid, level);

static enum CommonTextdraw
{
    Text:TD_HUNGER_OUTLINE,
    Text:TD_HUNGER_FILL,
};

static enum PlayerTextdraw
{
    PlayerText:TD_HUNGER_LEVEL,
};

new Text:hungerTextDraw[CommonTextdraw];
new PlayerText:playerHungerTextDraw[MAX_PLAYERS][PlayerTextdraw];

stock InitialiseHungerHud(playerid)
{
    hungerTextDraw[TD_HUNGER_OUTLINE] = TextDrawCreate(549.000000, 58.000000, "_");
	TextDrawBackgroundColor(hungerTextDraw[TD_HUNGER_OUTLINE], 255);
	TextDrawFont(hungerTextDraw[TD_HUNGER_OUTLINE], 1);
	TextDrawLetterSize(hungerTextDraw[TD_HUNGER_OUTLINE], 0.999999, 0.299999);
	TextDrawColor(hungerTextDraw[TD_HUNGER_OUTLINE], -1);
	TextDrawSetOutline(hungerTextDraw[TD_HUNGER_OUTLINE], 0);
	TextDrawSetProportional(hungerTextDraw[TD_HUNGER_OUTLINE], 1);
	TextDrawSetShadow(hungerTextDraw[TD_HUNGER_OUTLINE], 1);
	TextDrawUseBox(hungerTextDraw[TD_HUNGER_OUTLINE], 1);
	TextDrawBoxColor(hungerTextDraw[TD_HUNGER_OUTLINE], 255);
	TextDrawTextSize(hungerTextDraw[TD_HUNGER_OUTLINE], 604.000000, 0.000000);

	hungerTextDraw[TD_HUNGER_FILL] = TextDrawCreate(551.000000, 59.000000, "_");
	TextDrawBackgroundColor(hungerTextDraw[TD_HUNGER_FILL], 255);
	TextDrawFont(hungerTextDraw[TD_HUNGER_FILL], 1);
	TextDrawLetterSize(hungerTextDraw[TD_HUNGER_FILL], 0.979999, -0.000000);
	TextDrawColor(hungerTextDraw[TD_HUNGER_FILL], -1);
	TextDrawSetOutline(hungerTextDraw[TD_HUNGER_FILL], 0);
	TextDrawSetProportional(hungerTextDraw[TD_HUNGER_FILL], 1);
	TextDrawSetShadow(hungerTextDraw[TD_HUNGER_FILL], 1);
	TextDrawUseBox(hungerTextDraw[TD_HUNGER_FILL], 1);
	TextDrawBoxColor(hungerTextDraw[TD_HUNGER_FILL], 0x003200FF);
	TextDrawTextSize(hungerTextDraw[TD_HUNGER_FILL], 601.000000, 0.000000);

	playerHungerTextDraw[playerid][TD_HUNGER_LEVEL] = CreatePlayerTextDraw(playerid, 551.000000, 59.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 255);
	PlayerTextDrawFont(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	PlayerTextDrawLetterSize(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 0.979999, -0.000000);
	PlayerTextDrawColor(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], -1);
	PlayerTextDrawSetOutline(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 0);
	PlayerTextDrawSetProportional(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	PlayerTextDrawSetShadow(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	PlayerTextDrawUseBox(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	PlayerTextDrawBoxColor(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 0x2D5925FF);
	PlayerTextDrawTextSize(playerid, playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 601.000000, 0.000000);
}

stock _ShowPlayerHungerHud(playerid)
{
    TextDrawShowForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_OUTLINE]);
    TextDrawShowForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_FILL]);
}

stock _HidePlayerHungerHud(playerid)
{
    TextDrawHideForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_OUTLINE]);
    TextDrawHideForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_FILL]);
}

stock DestroyPlayerHungerHud(playerid)
{
	PlayerTextDrawDestroy(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL]);
}

stock DestroyPlayerHungerHudForAll()
{
	TextDrawDestroy(Text:hungerTextDraw[TD_HUNGER_OUTLINE]);
	TextDrawDestroy(Text:hungerTextDraw[TD_HUNGER_FILL]);

	foreach(new playerid : Player)
	{
		PlayerTextDrawDestroy(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL]);
	}	
}

stock UpdateHungerHud(playerid, level) {
	if (IsPlayerConnected(playerid)) {
	    new hungerLevel = 100 - level;

	    if (hungerLevel<=0){
	    	PlayerTextDrawUseBox(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL],0);
		} else if (hungerLevel>=95) {
			PlayerTextDrawUseBox(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	    	PlayerTextDrawTextSize(playerid,PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 601.0,0.0); 
	    } else {
			PlayerTextDrawUseBox(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], 1);
	    	PlayerTextDrawTextSize(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL], ((551-6)+((((551+6+55.5-2)-551)/100) * hungerLevel)), 0.0);
	    }

	    PlayerTextDrawShow(playerid, PlayerText:playerHungerTextDraw[playerid][TD_HUNGER_LEVEL]);
	}

	return 1;
}

public OnPlayerHungerUpdate(playerid, level)
{
	UpdateHungerHud(playerid, level);
	return 1;
}
