---
sidebar_position: 2
---

# thirst

Player will lose thirst over time. If the player's thirst reaches 0, they will start losing health. A thirst bar will be displayed on the player's HUD.

## Callbacks

### `OnPlayerThirstUpdate(playerid, level)`
Called when the player's thirst level changes.

```cpp
hook OnPlayerThirstUpdate(playerid, level)
{
	UpdateThirstHud(playerid, level);
	return 1;
}
```

### `OnMaxThirstLevelReached(playerid)`
Called when the player reaches the maximum thirst level. This callback may be called multiple times, once every time the thirst timer passes and the player's thirst level is still at the maximum.

```cpp
hook OnMaxThirstLevelReached(playerid)
{
	new Float:health;
	GetPlayerHealth(playerid, health);

	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);
	SetPlayerHealth(playerid, health - 10);
	return 1;
}
```