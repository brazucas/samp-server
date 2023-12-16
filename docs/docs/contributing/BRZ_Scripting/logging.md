---
sidebar_position: 1
---

# Logging

Logger functions helpers.

### `log_debug(const namespace[], const formatStr[], ...)`
:::info
`log_debug` will only log if the server is in debug mode.
:::

### `log_info(const namespace[], const formatStr[], ...)`
:::info
`log_info` will only be printed in the server console and may be lost on server restarts.
:::

### `log_warning(const namespace[], const formatStr[], ...)`
:::info
`log_warning` messages will be stored in the database and can be viewed in the admin panel.
:::

### `log_error(const namespace[], const formatStr[], ...)`
:::warning Note
`log_error` will trigger an alert for admins in Discord, e-mail, SMS if too many errors are logged within a short period of time.
:::

### `log_critical(const namespace[], const formatStr[], ...)`

:::danger IMPORTANT
`log_critical` will trigger an alert for admins in Discord, e-mail, SMS. Must only be used for critical path errors.
:::

```cpp title="Example"
#include <BRZ_Scripting\logging>

public OnPlayerConnect(playerid)
{
	log_debug("OnPlayerConnect", "Player %d connected.", playerid);
	log_info("OnPlayerConnect", "Player %d connected.", playerid);
	log_warning("OnPlayerConnect", "Player %d connected.", playerid);
	log_error("OnPlayerConnect", "Player %d connected.", playerid);
	log_critical("OnPlayerConnect", "Player %d connected.", playerid);
	return 1;
}
```

```cpp title="Critical path example"
#include <a_mysql>
#include <BRZ_Scripting\logging>

hook OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid)
	{
		case CR_SERVER_GONE_ERROR:
		{
			log_critical(MYSQL_NAMESPACE, "Lost connection to server");
		}
		case ER_SYNTAX_ERROR:
		{
			log_error(MYSQL_NAMESPACE, "Query syntax error: %s",query);
		}
		default: 
		{
			log_warning(MYSQL_NAMESPACE, "[Id %i] Query error: %s", errorid, query);
		}
	}
	return continue(1);
}
```