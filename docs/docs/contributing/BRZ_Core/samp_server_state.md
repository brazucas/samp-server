---
sidebar_position: 2
---

# Server State APIs

Helper functions to control the server state.

## API

### `BRZ_Core_GetBRZVersion()`
Get the current BRZ server version.

```cpp
public OnPlayerConnect(playerid)
{
	new server_version = BRZ_Core_GetBRZVersion();
	printf("Player %d connected to BRZ server version %s", playerid, server_version);
}
```

### `BRZ_Core_CloseServer()`
Closes the server. Currently it's just a wrap for SA-MP native `SendRconCommand("exit")` function.