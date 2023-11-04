#include <a_mysql>
#include <brz_scripting>

stock bool:InitialiseFeatureToggle(const toggle[])
{
    new query[MAX_QUERY_SIZE];
    format(query, sizeof(query), "insert into feature_toggles(toggle_key, enabled) values('%s', 0)", toggle);
    mysql_query(MySQL:GetMySQLHandle(), query);

    if (cache_affected_rows() > 0) {
        return true;
    }

    log_critical(FileNamespace(), "[GetToggleIdFromKey] failed while trying to create toggle %s", toggle);
    return false;
}

stock GetToggleIdFromKey(const toggle[])
{
    new 
        query[MAX_QUERY_SIZE],
        toggleId,
        rows;

    format(query, sizeof(query), "select id from feature_toggles where toggle_key = '%s'", toggle);
    mysql_query(MySQL:GetMySQLHandle(), query);

    cache_get_row_count(rows);

    if (rows == 0)
    {
        log_critical(FileNamespace(), "[GetToggleIdFromKey] the requested toggle %s doesn't exist, creating it with default value", toggle);

        if (InitialiseFeatureToggle(toggle)) {
            return GetToggleIdFromKey(toggle);
        } else {
            return -1;
        }
    }

    cache_get_value_name_int(0, "id", toggleId);

    return toggleId;
}

static stock FileNamespace()
{
    new namespace[64] = "FeatureToggles";
    return namespace;
}