#include <a_samp>

static enum Textdraw
{
    PlayerText:TD_MONEY,
};

new PlayerText:playerTextdraws[MAX_PLAYERS][Textdraw];

stock InitialisePlayerHud(playerid)
{
    playerTextdraws[playerid][TD_MONEY] = CreatePlayerTextDraw(playerid, 612.000000,76.000000, "~g~R$00000000");
    PlayerTextDrawAlignment(playerid, playerTextdraws[playerid][TD_MONEY], 3);
    PlayerTextDrawBackgroundColor(playerid, playerTextdraws[playerid][TD_MONEY], 0x000000ff);
    PlayerTextDrawFont(playerid, playerTextdraws[playerid][TD_MONEY], 3);
    PlayerTextDrawLetterSize(playerid, playerTextdraws[playerid][TD_MONEY], 0.600000,2.399999);
    PlayerTextDrawColor(playerid, playerTextdraws[playerid][TD_MONEY], 0xffffffff);
    PlayerTextDrawSetOutline(playerid, playerTextdraws[playerid][TD_MONEY], 1);
    PlayerTextDrawSetProportional(playerid, playerTextdraws[playerid][TD_MONEY], 1);
    PlayerTextDrawSetShadow(playerid, playerTextdraws[playerid][TD_MONEY], 1);
}

stock ShowPlayerHud(playerid)
{
    PlayerTextDrawShow(playerid, PlayerText:playerTextdraws[playerid][TD_MONEY]);
}