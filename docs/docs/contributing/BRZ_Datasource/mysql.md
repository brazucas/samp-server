---
sidebar_position: 2
---

# MySQL

The server supports MySQL as a datasource. It uses [BlueG's SA-MP MySQL Plugin](https://github.com/pBlueG/SA-MP-MySQL) under the hood.

## Migrations

The server supports migrations. Migrations are used to create and update database tables. Migrations are located in `scriptfiles/database/mysql/migrations` folder. Each migration file should have a unique name and should be prefixed with a timestamp. The number is used to determine the order of migrations. For example, `20230916_player_table.sql`.

:::danger Important
The migration files should contain only one SQL statement. If you need to create multiple tables, create multiple migration files.
:::

### Creating a migration

1. Create a new file in `scriptfiles/database/mysql/migrations` folder. The file name should be prefixed with a timestamp, followed by an underscore and a description. For example, `20230916_player_table.sql`.
2. Call the `MySQLMigrations_ExecFile` function passing the file name as parameter. For example, `MySQLMigrations_ExecFile("20230916_player_table.sql");`. This function call must be called after the datasource is initialized. You may use the `OnDatasourcesReady` to do so:

```SQL title="scriptfiles/database/mysql/migrations/20230916_player_table.sql"
CREATE TABLE `player` (
	`id` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
	`name` VARCHAR(24) NOT NULL,
	`password` VARCHAR(64) NOT NULL,
	`email` VARCHAR(64) NOT NULL,
	`ip` VARCHAR(64) NOT NULL,
	`last_login` DATETIME NOT NULL,
	`created_at` DATETIME NOT NULL,
	`updated_at` DATETIME NOT NULL,
	PRIMARY KEY (`id`),
	UNIQUE INDEX `name` (`name`),
	UNIQUE INDEX `email` (`email`)
)
```

```cpp title="filterscript.pwn"
#include <BRZ_Datasource\mysql>
#include <BRZ_Datasource\mysql_migrations>

hook function OnDatasourcesReady()
{
	MySQLMigrations_ExecFile("20230916_player_table");
	return continue();
}
```