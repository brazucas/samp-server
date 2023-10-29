#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <brz_scripting>

#define MYSQL_NAMESPACE "BRZ_Datasource_MySQL"

#if !defined MYSQL_HOST
	#define MYSQL_HOST "127.0.0.1"
#endif 
#if !defined MYSQL_PORT
	#define MYSQL_PORT 3310
#endif
#if !defined MYSQL_USER
	#define MYSQL_USER "root"
#endif
#if !defined MYSQL_PASS
	#define MYSQL_PASS "abcd1234"
#endif
#if !defined MYSQL_DATABASE
	#define MYSQL_DATABASE "rpgmgs"
#endif

forward MySQLConnect();
forward MySQLDisconnect();
forward MySQL:GetMySQLHandle();

enum MySQLConfig
{
	E_MYSQL_HOST[64],
	E_MYSQL_PORT,
	E_MYSQL_USER[64],
	E_MYSQL_PASS[64],
	E_MYSQL_DATABASE[64]
}

static MySQL:databaseConnection;

public MySQL:GetMySQLHandle()
{
	return databaseConnection;
}

public MySQLConnect()
{
	new config[MySQLConfig];
	GetMySQLConfiguration(config);

	log_info(MYSQL_NAMESPACE, "Connecting MySQL Datasource at mysql://%s:****@%s:%d/%s", config[E_MYSQL_USER], config[E_MYSQL_HOST], config[E_MYSQL_PORT], config[E_MYSQL_DATABASE]);

	new MySQLOpt:options = mysql_init_options();
	mysql_set_option(options, SERVER_PORT, config[E_MYSQL_PORT]);
    databaseConnection = mysql_connect(config[E_MYSQL_HOST], config[E_MYSQL_USER], config[E_MYSQL_PASS], config[E_MYSQL_DATABASE], options);

	if (mysql_errno(databaseConnection) != 0)  {
		log_critical(MYSQL_NAMESPACE, "Could not connect to the database! exiting server.");
		BRZ_Core_CloseServer();
	}

	return 1;
}

public MySQLDisconnect()
{
	mysql_close(databaseConnection);
	return 1;
}

stock GetMySQLConfiguration(config[MySQLConfig])
{
	format(config[E_MYSQL_HOST], 64, MYSQL_HOST);
	config[E_MYSQL_PORT] = MYSQL_PORT;
	format(config[E_MYSQL_USER], 64, MYSQL_USER);
	format(config[E_MYSQL_PASS], 64, MYSQL_PASS);
	format(config[E_MYSQL_DATABASE], 64, MYSQL_DATABASE);
	return 1;
}

hook function DatasourceConnect(Datasource:datasource)
{
	if (datasource == MySQL) {
		MySQLConnect();
	}
    return continue();
}

hook function DatasourceExit(Datasource:datasource)
{
	if (datasource == MySQL) {
    	MySQLDisconnect();
	}
    return continue();
}

hook OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid)
	{
		case CR_SERVER_GONE_ERROR:
		{
			log_error(MYSQL_NAMESPACE, "Lost connection to server");
		}
		case ER_SYNTAX_ERROR:
		{
			log_error(MYSQL_NAMESPACE, "Query syntax error: %s",query);
		}
		default: 
		{
			log_error(MYSQL_NAMESPACE, "[Id %i] Query error: %s", errorid, query);
		}
	}
	return continue(1);
}