---
sidebar_position: 1
---

# hunger

Controls the player's hunger level and its related HUD.

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

### `ShowPlayerHungerHud(playerid)`
Show player's hunger hud.

### `HidePlayerHungerHud(playerid)`
Hides player's hunger hud.
