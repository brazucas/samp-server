---
sidebar_position: 1
---

# Bridge APIs

Function wrappers for calling SA-MP remote functions i.e. filterscripts, plugins, etc.

### `bool:IsPlayerLoggedIn(playerid)`

Returns whether the player is authenticated or not.

```cpp
#include <BRZ_Scripting\brz_apis>

public OnPlayerSpawn(playerid)
{
	if (!IsPlayerLoggedIn(playerid)) {
		SendClientMessage(playerid, -1, "You are not logged in.");
		Kick(playerid);
	}

	return 1;
}
```