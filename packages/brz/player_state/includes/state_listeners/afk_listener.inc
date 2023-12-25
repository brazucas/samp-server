#include <YSF>
#include <YSI_Coding\y_hooks>

hook OnPlayerPauseStateChange(playerid, pausestate)
{
    if (pausestate == 1) {
        SetIsPlayerPaused(playerid, true);
    } else {
        SetIsPlayerPaused(playerid, false);
    }
    return continue();
}