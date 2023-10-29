enum Datasource
{
    MySQL,
}

forward BRZ_Datasource_InitDatasources();
forward BRZ_Datasource_ExitDatasources();
forward DatasourceConnect(Datasource:datasource);
forward DatasourceExit(Datasource:datasource);
forward OnDatasourcesReady();