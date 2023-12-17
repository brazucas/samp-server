---
sidebar_position: 1
---

# Hunger System

Player will lose hunger over time. If the player's hunger reaches 0, they will start losing health. A hunger bar will be displayed on the player's HUD.

## How it works

- Player starts with 0 hunger points.
- Player loses 1 hunger point every minute.
- If the player's hunger reaches the maximum (100), they will start losing 10 health points every minute.
- To regain hunger points, the player must eat food. Each food item will restore a different amount of hunger points.

## Callbacks

### `OnPlayerHungerUpdate(playerid, level)`
Called when the player's hunger level changes.

```cpp
hook OnPlayerHungerUpdate(playerid, level)
{
	UpdateHungerHud(playerid, level);
	return 1;
}
```

### `OnMaxHungerLevelReached(playerid)`
Called when the player reaches the maximum hunger level. This callback may be called multiple times, once every time the hunger timer passes and the player's hunger level is still at the maximum.

```cpp
hook OnMaxHungerLevelReached(playerid)
{
	new Float:health;
	GetPlayerHealth(playerid, health);

	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);
	SetPlayerHealth(playerid, health - 10);
	return 1;
}
```