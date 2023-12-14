static enum Textdraw
{
    Text:TD_HUNGER_OUTLINE,
    Text:TD_HUNGER_FILL,
};

new Text:hungerTextDraw[Textdraw];

stock InitialiseHungerHud()
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
}

stock ShowPlayerHunger(playerid)
{
    TextDrawShowForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_OUTLINE]);
    TextDrawShowForPlayer(playerid, Text:hungerTextDraw[TD_HUNGER_FILL]);
}

stock DestroyPlayerHungerHud()
{
	TextDrawDestroy(Text:hungerTextDraw[TD_HUNGER_OUTLINE]);
	TextDrawDestroy(Text:hungerTextDraw[TD_HUNGER_FILL]);
}