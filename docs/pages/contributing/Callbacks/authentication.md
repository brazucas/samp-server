---
sidebar_position: 1
---

# Authentication Callbacks

### `OnBRZPlayerAuth(playerid)`

Called when the player finishes authenticating (registering or logging in).

:::info Note
It's recommended to use YSI hooks to handle this callback.
:::

```cpp
#include <YSI_Coding\y_hooks>

hook OnBRZPlayerAuth(playerid)
{
	TogglePlayerSpectating(playerid, false);

	SetSpawnInfo(playerid, 0, 0, 1743.248901, -1948.481933, 14.117187, 178.015930, 26, 36, 28, 150, 0, 0);
	SpawnPlayer(playerid);

	InitialisePlayerHuds(playerid);
	InitialisePlayerAttributeStates(playerid);

	return 1;
}
```