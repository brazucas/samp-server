#include <a_samp>

static enum Textdraw
{
    Text:TD_BRZ_HEADLINE,
    Text:TD_BRZ_URL,
    Text:TD_FORCE,
};

new Text:serverTextdraws[Textdraw];

stock InitialiseServerHud()
{
    serverTextdraws[TD_BRZ_HEADLINE] = TextDrawCreate(494.599975, 99.099906, "~g~(bra~y~z~b~u~w~c~b~a~y~s~g~rpg)");
	TextDrawBackgroundColor(serverTextdraws[TD_BRZ_HEADLINE], 255);
	TextDrawFont(serverTextdraws[TD_BRZ_HEADLINE], 3);
	TextDrawLetterSize(serverTextdraws[TD_BRZ_HEADLINE], 0.429996, 1.899999);
	TextDrawColor(serverTextdraws[TD_BRZ_HEADLINE], -1);
	TextDrawSetOutline(serverTextdraws[TD_BRZ_HEADLINE], 1);
	TextDrawSetProportional(serverTextdraws[TD_BRZ_HEADLINE], 1);

    serverTextdraws[TD_BRZ_URL] = TextDrawCreate(60, 419.887054, "~g~www.b~y~r~b~z~g~.gg");
	TextDrawBackgroundColor(serverTextdraws[TD_BRZ_URL], 190);
	TextDrawFont(serverTextdraws[TD_BRZ_URL], 1);
	TextDrawLetterSize(serverTextdraws[TD_BRZ_URL], 0.239998, 0.899999);
	TextDrawColor(serverTextdraws[TD_BRZ_URL], -1);
	TextDrawSetOutline(serverTextdraws[TD_BRZ_URL], 1);
	TextDrawSetProportional(serverTextdraws[TD_BRZ_URL], 1);

    serverTextdraws[TD_FORCE] = TextDrawCreate(31.300008, 423.799194, "ld_none:force");
	TextDrawBackgroundColor(serverTextdraws[TD_FORCE], 255);
	TextDrawFont(serverTextdraws[TD_FORCE], 4);
	TextDrawLetterSize(serverTextdraws[TD_FORCE], 1.000000, 1.000000);
	TextDrawColor(serverTextdraws[TD_FORCE], 130);
	TextDrawSetOutline(serverTextdraws[TD_FORCE], 0);
	TextDrawSetProportional(serverTextdraws[TD_FORCE], 1);
	TextDrawSetShadow(serverTextdraws[TD_FORCE], 0);
	TextDrawUseBox(serverTextdraws[TD_FORCE], 1);
	TextDrawBoxColor(serverTextdraws[TD_FORCE], 255);
	TextDrawTextSize(serverTextdraws[TD_FORCE], 111.000000, 11.000000);
}

stock ShowServerHud(playerid)
{
    TextDrawShowForPlayer(playerid, Text:serverTextdraws[TD_BRZ_HEADLINE]);
    TextDrawShowForPlayer(playerid, Text:serverTextdraws[TD_BRZ_URL]);
    TextDrawShowForPlayer(playerid, Text:serverTextdraws[TD_FORCE]);
}