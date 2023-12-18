---
sidebar_position: 1
---

# Bridge APIs

Function wrappers for calling packages APIs from within other packages.

### `bool:IsPlayerLoggedIn(playerid)`

Returns whether the player is authenticated in the server.

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