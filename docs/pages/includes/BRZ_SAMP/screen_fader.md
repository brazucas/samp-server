---
sidebar_position: 2
---

# Screen Fader

### `FadePlayerScreenToColor(playerid, colorWithTransparency, FadeSpeed:speed)`

Fades the player screen to a color, usually black.

:::info speed options
- SLOW_FADE
- NORMAL_FADE
- FAST_FADE
:::

```cpp
#include <BRZ_SAMP\screen_fader>
#include <YSI_Visual\y_commands>

YCMD:fadescreen(playerid, const params[], help)
{
	FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, NORMAL_FADE);
	return 1;
}
```

### `ClearPlayerScreenFade(playerid)`

Clear player's screen fade effects.

```cpp
#include <BRZ_SAMP\screen_fader>
#include <YSI_Visual\y_commands>

YCMD:clearscreen(playerid, const params[], help)
{
	ClearPlayerScreenFade(playerid);
	return 1;
}
```