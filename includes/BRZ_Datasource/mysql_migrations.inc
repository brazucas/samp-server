#include <a_mysql>
#include <YSI_Coding\y_hooks>

#define MIGRATIONS_PATH "database/mysql/migrations/"

static enum MigrationInfo {
    bool:Executed,
    Filename[128]
}

forward MySQLMigrations_ExecFile(const filename[]);

public MySQLMigrations_ExecFile(const filename[]) 
{
    if (IsMigrationTableCreated()) {
        if(!IsMigrationFileExecuted(filename)) {
            new filenameWithExtension[128];
            format(filenameWithExtension, sizeof(filenameWithExtension), "%s%s.sql", MIGRATIONS_PATH, filename);
            
            mysql_query_file(MySQL:GetMySQLHandle(), filenameWithExtension);

            if(mysql_errno() == 0) {
                MarkMigrationAsExecuted(filename);
                log_info(FileNamespace(), "Executed migration file %s", filename);
            } else {
                log_error(FileNamespace(), "Failed to execute migration file %s, check if file exists or mysql error log", filename);
            }
        }
    } else {
        log_warning(FileNamespace(), "Migration table not found, creating it...", filename);
        if(CreateMigrationTable()) {
            log_warning(FileNamespace(), "Migration table created, retrying migration...", filename);
            MySQLMigrations_ExecFile(filename);
        } else {
            log_critical(FileNamespace(), "Failed to create migration table, closing server...");
            BRZ_Core_CloseServer();
        }
    }
}

hook function OnDatasourcesReady()
{
	MySQLMigrations_ExecFile("20230916_player_table");

    MySQLMigrations_ExecFile("20231104_feature_toggles");
    return continue();
}

static stock MarkMigrationAsExecuted(const filename[])
{
    new migration[MigrationInfo],
        Cache:result,
        query[MAX_QUERY_SIZE];

    if(GetMigration(filename, migration) == 1) {
        if(!migration[Executed]) {
            format(query, sizeof(query), "UPDATE `migrations` SET `executed_at` = NOW() WHERE `filename` = '%s%s.sql';", MIGRATIONS_PATH, filename);

            result = mysql_query(MySQL:GetMySQLHandle(), query);
            cache_delete(result);
        }
    } else {
        format(query, sizeof(query), "INSERT INTO `migrations` (`filename`, `executed_at`) VALUES ('%s%s.sql', NOW());", MIGRATIONS_PATH, filename);

        result = mysql_query(MySQL:GetMySQLHandle(), query);
        cache_delete(result);
    }
}

static stock GetMigration(const filename[], migration[MigrationInfo])
{
    new query[MAX_QUERY_SIZE],
        rows;

    format(query, sizeof(query), "SELECT * FROM `migrations` WHERE `filename` = '%s%s.sql';", MIGRATIONS_PATH, filename);
    new Cache:result = mysql_query(MySQL:GetMySQLHandle(), query);

    cache_get_row_count(rows);

    if(rows == 0) {
        cache_delete(result);
        return 0;
    }

    cache_get_value_name(0, "filename", migration[Filename]);
    cache_is_value_name_null(0, "executed_at", migration[Executed]);
    cache_delete(result);

    migration[Executed] = !migration[Executed];

    return 1;
}

static stock IsMigrationTableCreated()
{
    new query[MAX_QUERY_SIZE];
    format(query, sizeof(query), "SELECT COUNT(*) FROM INFORMATION_SCHEMA.TABLES WHERE table_schema = '%s' AND TABLE_NAME = 'migrations';", MYSQL_DATABASE);

    new Cache:result = mysql_query(MySQL:GetMySQLHandle(), query),
        count;

    cache_get_value_int(0, 0, count);
    cache_delete(result);

    return count > 0;
}

static stock IsMigrationFileExecuted(const filename[])
{
    new query[MAX_QUERY_SIZE];
    format(query, sizeof(query), "SELECT COUNT(*) FROM `migrations` WHERE `filename` = '%s%s.sql' AND executed_at IS NOT NULL;", MIGRATIONS_PATH, filename);

    new Cache:result = mysql_query(MySQL:GetMySQLHandle(), query),
        count;

    cache_get_value_int(0, 0, count);
    cache_delete(result);

    return count > 0;
}

static stock CreateMigrationTable()
{
    new Cache:result = mysql_query(MySQL:GetMySQLHandle(), "CREATE TABLE IF NOT EXISTS `migrations` (`id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY, `filename` VARCHAR(255) NOT NULL, `executed_at` DATETIME);");
    cache_delete(result);

    if(mysql_errno() == 0) {
        return true;
    } else {
        return false;
    }
}

static stock FileNamespace()
{
    new namespace[64] = "MySQLMigrations";
    return namespace;
}