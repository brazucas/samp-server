---
sidebar_position: 1
---

# Dialogs

### `ShowAlert(playerid, const title[], const message[], const callback[])`

Shows an alert dialog to the player. The callback is called when the player clicks the OK button.

:::info
- `callback` must be a public function. It'll receive the `playerid` as argument.
:::

```cpp
#include <BRZ_SAMP\samp_dialogs>

forward ShowRegisterDialog(playerid);
public ShowRegisterDialog(playerid)
{
	printf("Player %d clicked OK on the register dialog", playerid);
	return 1;
}

public OnPlayerConnect(playerid)
{
	ShowAlert(playerid, "Alert Title", "Alert description.", "ShowRegisterDialog");
	return 1;
}
```