#include <YSI_Coding\y_hooks>
#include <BRZ_Datasource\brz_datasource_interface>
#include <brz_scripting>

#define DATASOURCE_NAMESPACE "BRZ_Datasource"

public BRZ_Datasource_InitDatasources()
{
    log_info(DATASOURCE_NAMESPACE, "Initialising datasources");
    DatasourceConnect(MySQL);
    return 1;
}

public BRZ_Datasource_ExitDatasources()
{
    log_info(DATASOURCE_NAMESPACE, "Exiting datasources");
    DatasourceExit(MySQL);
    return 1;
}

public OnDatasourcesReady()
{
    log_info(DATASOURCE_NAMESPACE, "All datasources connected");
    return 1;
}

public DatasourceConnect(Datasource:datasource)
{
    OnDatasourcesReady();
    return 1;
}

public DatasourceExit(Datasource:datasource)
{
    log_info(DATASOURCE_NAMESPACE, "All datasources exited");
    return 1;
}

#include <BRZ_Datasource\mysql>
#include <BRZ_Datasource\mysql_migrations>