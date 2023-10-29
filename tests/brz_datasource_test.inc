#include <tests\y_testing_mocks>
#include <brz_datasource>
#include <YSI_Core\y_testing>
#include <YSI_Coding\y_hooks>

hook function DatasourceConnect(Datasource:datasource) 
{
	if (datasource == MySQL) {
		RegisterCall("DatasourceConnect", "s", "MySQL");
	}

	return;
}

@test(.group = "brz_datasource") ShouldInitMySQLDatasource()
{
	MockInit();
	BRZ_Datasource_InitDatasources();
	ASSERT_CALL("DatasourceConnect", "s", "MySQL");
}