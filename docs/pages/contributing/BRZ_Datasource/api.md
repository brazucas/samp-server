---
sidebar_position: 1
---

# API

### `BRZ_Datasource_InitDatasources()`

Initialises all datasources. Usually called in `OnGameModeInit()`.

### `BRZ_Datasource_ExitDatasources()`

Exits all datasources. Usually called in `OnGameModeExit()`.

### `DatasourceConnect(Datasource:datasource)`

Connects to a datasource. The Datasource name passed as argument must be part of the datasource enum

```cpp
public BRZ_Datasource_InitDatasources()
{
    log_info(DATASOURCE_NAMESPACE, "Initialising datasources");
    DatasourceConnect(MySQL);
    return 1;
}
```

### `DatasourceExit(Datasource:datasource)`

Exits a datasource. The Datasource name passed as argument must be part of the datasource enum

```cpp
public BRZ_Datasource_ExitDatasources()
{
	log_info(DATASOURCE_NAMESPACE, "Exiting datasources");
	DatasourceExit(MySQL);
	return 1;
}
```

### `OnDatasourcesReady()`

Called when all datasources are ready.

```cpp
hook function OnDatasourcesReady()
{
	log_info(DATASOURCE_NAMESPACE, "Datasources ready");
	return continue();
}
```