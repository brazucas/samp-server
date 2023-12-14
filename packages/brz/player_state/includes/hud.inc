#include <hud/player-hud>
#include <hud/server-hud>

stock ShowHudForPlayer(playerid)
{
    ShowServerHud(playerid);
    ShowPlayerHud(playerid);
}