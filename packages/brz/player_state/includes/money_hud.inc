#include <a_samp>
#include <YSI_Data\y_foreach>

static enum Textdraw
{
    PlayerText:TD_MONEY,
};

new PlayerText:moneyTextdraws[MAX_PLAYERS][Textdraw];

stock InitialiseMoneyHud(playerid)
{
    moneyTextdraws[playerid][TD_MONEY] = CreatePlayerTextDraw(playerid, 612.000000,76.000000, "~g~R$00000000");
    PlayerTextDrawAlignment(playerid, moneyTextdraws[playerid][TD_MONEY], 3);
    PlayerTextDrawBackgroundColor(playerid, moneyTextdraws[playerid][TD_MONEY], 0x000000ff);
    PlayerTextDrawFont(playerid, moneyTextdraws[playerid][TD_MONEY], 3);
    PlayerTextDrawLetterSize(playerid, moneyTextdraws[playerid][TD_MONEY], 0.600000,2.399999);
    PlayerTextDrawColor(playerid, moneyTextdraws[playerid][TD_MONEY], 0xffffffff);
    PlayerTextDrawSetOutline(playerid, moneyTextdraws[playerid][TD_MONEY], 1);
    PlayerTextDrawSetProportional(playerid, moneyTextdraws[playerid][TD_MONEY], 1);
    PlayerTextDrawSetShadow(playerid, moneyTextdraws[playerid][TD_MONEY], 1);

    InitialiseHungerHud();
}

stock ShowPlayerMoney(playerid)
{
    PlayerTextDrawShow(playerid, PlayerText:moneyTextdraws[playerid][TD_MONEY]);
}

stock DestroyPlayerMoneyHudForAll()
{
    foreach (new playerid : Player) {
        PlayerTextDrawDestroy(playerid, PlayerText:moneyTextdraws[playerid][TD_MONEY]);
    }
}

stock DestroyPlayerMoneyHud(playerid)
{
    PlayerTextDrawDestroy(playerid, PlayerText:moneyTextdraws[playerid][TD_MONEY]);
}