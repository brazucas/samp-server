#include <_hud_state>

static enum PlayerAttributeType {
    bool:IS_PAUSED,
}

new playerState[MAX_PLAYERS][PlayerAttributeType];

stock SetIsPlayerPaused(playerid, bool:paused) {
    playerState[playerid][IS_PAUSED] = paused;
    return 1;
}

stock InitialisePlayerAttributeState(playerid)
{
    InitPlayerHudState(playerid);
    SetIsPlayerPaused(playerid, false);
    return 1;
}

stock DestroyPlayerAttributeState(playerid)
{
    DestroyPlayerHudState(playerid);
    SetIsPlayerPaused(playerid, false);
    return 1;
}