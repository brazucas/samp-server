---
sidebar_position: 1
---

# Feature Flags

Feature flags are a way of enabling or disabling features in the server. This is useful for testing new features, or for enabling features for a subset of players.

## API

### `bool:IsFeatureEnabled(FeatureToggles:toggle)`
Returns whether a feature is enabled or not.

```cpp
#include <BRZ_Core\feature_toggles>

public OnPlayerConnect(playerid)
{
	if (!IsFeatureEnabled(FF_AUTHENTICATION)) {
		printf("Player authentication is disabled. Skipping authentication for player %d", playerid);
		SendClientMessage(playerid, 0xFFFFFFFF, "Player authentication is disabled. Please try again later.");
		Kick(playerid);
		return 1;
	}
}
```