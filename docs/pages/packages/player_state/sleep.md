---
sidebar_position: 3
---

# sleep

Players will accrue sleep over time, and will need to sleep to avoid passing out.

## Callbacks

### `OnPlayerSleepUpdate(playerid, level)`
Called when the player's sleep level changes.

```cpp
hook OnPlayerSleepUpdate(playerid, level)
{
	UpdateSleepHud(playerid, level);
	return 1;
}
```

### `OnMaxSleepLevelReached(playerid)`
Called when the player reaches the maximum sleep level. This callback may be called multiple times, once every time the thirst timer passes and the player's sleep level is still at the maximum.

```cpp
#include <BRZ_SAMP\screen_fader>
#include <YSI_Coding\y_hooks>

hook OnMaxSleepLevelReached(playerid)
{
	SendClientMessage(playerid, 0xFF000000, "You passed out from exhaustion...");
	FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, SLOW_FADE);
	PlayerPlaySound(playerid,1076,0,0,0);
	
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		ApplyAnimation(playerid,"CRACK","crckidle2",4.1,1,1,1,1,1);
	}

	return 1;
}
```