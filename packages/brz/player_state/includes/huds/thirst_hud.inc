#include <YSI_Data\y_foreach>

forward OnPlayerThirstUpdate(playerid, level);

static enum CommonTextdraw
{
    Text:TD_THIRST_OUTLINE,
    Text:TD_THIRST_FILL,
};

static enum PlayerTextdraw
{
    PlayerText:TD_THIRST_LEVEL,
};

new Text:thirstTextDraw[CommonTextdraw];
new PlayerText:playerThirstTextDraw[MAX_PLAYERS][PlayerTextdraw];

stock InitialiseThirstHud(playerid)
{
    thirstTextDraw[TD_THIRST_OUTLINE] = TextDrawCreate(549.000000, 38.000000, "_");
	TextDrawBackgroundColor(thirstTextDraw[TD_THIRST_OUTLINE], 255);
	TextDrawFont(thirstTextDraw[TD_THIRST_OUTLINE], 1);
	TextDrawLetterSize(thirstTextDraw[TD_THIRST_OUTLINE], 0.999999, 0.299999);
	TextDrawColor(thirstTextDraw[TD_THIRST_OUTLINE], -1);
	TextDrawSetOutline(thirstTextDraw[TD_THIRST_OUTLINE], 0);
	TextDrawSetProportional(thirstTextDraw[TD_THIRST_OUTLINE], 1);
	TextDrawSetShadow(thirstTextDraw[TD_THIRST_OUTLINE], 1);
	TextDrawUseBox(thirstTextDraw[TD_THIRST_OUTLINE], 1);
	TextDrawBoxColor(thirstTextDraw[TD_THIRST_OUTLINE], 255);
	TextDrawTextSize(thirstTextDraw[TD_THIRST_OUTLINE], 604.000000, 0.000000);

	thirstTextDraw[TD_THIRST_FILL] = TextDrawCreate(551.000000, 39.000000, "_");
	TextDrawBackgroundColor(thirstTextDraw[TD_THIRST_FILL], 255);
	TextDrawFont(thirstTextDraw[TD_THIRST_FILL], 1);
	TextDrawLetterSize(thirstTextDraw[TD_THIRST_FILL], 0.979999, -0.000000);
	TextDrawColor(thirstTextDraw[TD_THIRST_FILL], -1);
	TextDrawSetOutline(thirstTextDraw[TD_THIRST_FILL], 0);
	TextDrawSetProportional(thirstTextDraw[TD_THIRST_FILL], 1);
	TextDrawSetShadow(thirstTextDraw[TD_THIRST_FILL], 1);
	TextDrawUseBox(thirstTextDraw[TD_THIRST_FILL], 1);
	TextDrawBoxColor(thirstTextDraw[TD_THIRST_FILL], 0x0066CCFF);
	TextDrawTextSize(thirstTextDraw[TD_THIRST_FILL], 601.000000, 0.000000);

	playerThirstTextDraw[playerid][TD_THIRST_LEVEL] = CreatePlayerTextDraw(playerid, 551.000000, 39.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 255);
	PlayerTextDrawFont(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	PlayerTextDrawLetterSize(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 0.979999, -0.000000);
	PlayerTextDrawColor(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 0x00C7FFFF);
	PlayerTextDrawSetOutline(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 0);
	PlayerTextDrawSetProportional(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	PlayerTextDrawSetShadow(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	PlayerTextDrawUseBox(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	PlayerTextDrawBoxColor(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 0x00C7FFFF);
	PlayerTextDrawTextSize(playerid, playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 601.000000, 0.000000);
}

stock ShowPlayerThirst(playerid)
{
    TextDrawShowForPlayer(playerid, Text:thirstTextDraw[TD_THIRST_OUTLINE]);
    TextDrawShowForPlayer(playerid, Text:thirstTextDraw[TD_THIRST_FILL]);
}

stock DestroyPlayerThirstHud(playerid)
{
	PlayerTextDrawDestroy(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL]);
}

stock DestroyPlayerThirstHudForAll()
{
	TextDrawDestroy(Text:thirstTextDraw[TD_THIRST_OUTLINE]);
	TextDrawDestroy(Text:thirstTextDraw[TD_THIRST_FILL]);

	foreach(new playerid : Player)
	{
		PlayerTextDrawDestroy(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL]);
	}	
}

stock UpdateThirstHud(playerid, level) {
	if (IsPlayerConnected(playerid)) {
	    new thirstLevel = 100 - level;

	    if (thirstLevel <= 0){
	    	PlayerTextDrawUseBox(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 0);
		} else if (thirstLevel>=95) {
			PlayerTextDrawUseBox(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	    	PlayerTextDrawTextSize(playerid,PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 601.0,0.0); 
	    } else {
			PlayerTextDrawUseBox(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL], 1);
	    	PlayerTextDrawTextSize(playerid,PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL], ((551-6)+((((551+6+55.5-2)-551)/100)*thirstLevel)), 0.0);
	    }

	    PlayerTextDrawShow(playerid, PlayerText:playerThirstTextDraw[playerid][TD_THIRST_LEVEL]);
	}

	return 1;
}

public OnPlayerThirstUpdate(playerid, level)
{
	UpdateThirstHud(playerid, level);
	return 1;
}