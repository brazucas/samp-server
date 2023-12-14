static enum Textdraw
{
    Text:TD_THIRST_OUTLINE,
    Text:TD_THIRST_FILL,
};

new Text:thirstTextDraw[Textdraw];

stock InitialiseThirstHud()
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
}

stock ShowPlayerThirst(playerid)
{
    TextDrawShowForPlayer(playerid, Text:thirstTextDraw[TD_THIRST_OUTLINE]);
    TextDrawShowForPlayer(playerid, Text:thirstTextDraw[TD_THIRST_FILL]);
}

stock DestroyPlayerThirstHud()
{
	TextDrawDestroy(Text:thirstTextDraw[TD_THIRST_OUTLINE]);
	TextDrawDestroy(Text:thirstTextDraw[TD_THIRST_FILL]);
}