#include <tests\y_testing_mocks>
#include <BRZ_Datasource\mysql>
#include <YSI_Core\y_testing>
#include <YSI_Coding\y_hooks>

new mysql_errno_return_value;

stock MockMySQLERRNOReturnValue()
{
	return mysql_errno_return_value;
}

@test(.group = "brz_datasource_mysql") ShouldConMySQLSvSucssFully() // ShouldConnectToMySQLServerSuccessfully
{
	MockInit();
	MockReset("mysql_connect");
	MockReset("mysql_errno");
	MockReset("BRZ_Core_CloseServer");
	MockReset("mysql_set_option");

	mysql_errno_return_value = 0;
	MySQLConnect();

	ASSERT_CALL("mysql_connect", "ssss", "host", "user", "pass", "database");
	ASSERT_CALL_COUNT("BRZ_Core_CloseServer", 0);
	ASSERT_CALL("mysql_set_option", "sd", "SERVER_PORT", 3306);
}

@test(.group = "brz_datasource_mysql") ShouldClosSvIfMySQLConnFail() // ShouldCloseServerIfMySQLConnectionFails
{
	MockInit();
	MockReset("mysql_connect");
	MockReset("mysql_errno");
	MockReset("BRZ_Core_CloseServer");
	MockReset("mysql_set_option");

	mysql_errno_return_value = 1;
	MySQLConnect();
	
	ASSERT_CALL_COUNT("BRZ_Core_CloseServer", 1);
}

hook function BRZ_Core_CloseServer()
{
	RegisterCall("BRZ_Core_CloseServer", "");
	return 1;
}

hook function GetMySQLConfiguration(config[MySQLConfig])
{
	format(config[E_MYSQL_HOST], 64, "host");
	config[E_MYSQL_PORT] = 3306;
	format(config[E_MYSQL_USER], 64, "user");
	format(config[E_MYSQL_PASS], 64, "pass");
	format(config[E_MYSQL_DATABASE], 64, "database");
	return 1;
}

hook function mysql_connect(host[], user[], pass[], database[]) 
{
    RegisterCall("mysql_connect", "ssss", host, user, pass, database);
	return 1;
}

hook function mysql_errno() 
{
    RegisterCall("mysql_errno", "");
	return MockMySQLERRNOReturnValue();
}

hook native mysql_set_option(MySQLOpt:options, E_MYSQL_OPTION:option) 
{
	if (option == SERVER_PORT) {
    	RegisterCall("mysql_set_option", "sd", "SERVER_PORT", getarg(2));
	}

	return 1;
}