#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <BRZ_Datasource\mysql_migrations>
#include <BRZ_Core\Feature_Toggles\feature_toggles_helpers>

forward bool:IsFeatureEnabled(const toggle[]);
// forward bool:IsFeatureEnabledForPlayer(const toggle[], playerid);
// forward GetFeatureVariant(const toggle[]);
// forward GetFeatureVariantForPlayer(const toggle[]);
forward SetFeatureEnabled(const toggle[], bool:enabled);
// forward SetFeatureEnabledForPlayer(const toggle[], playerid, bool:enabled);
// forward SetFeatureVariant(const toggle[], const variant[]);
// forward SetFeatureVariantForPlayer(const toggle[], playerid, const variant[]);

enum FeatureToggle
{
    ToggleId[128],
    VariationId[128],
    bool:ToggleEnabled
}

enum FeatureToggleVariation
{
    ToggleVariationId[128]
}

new Cache:FeatureToggleCacheIndex[64];

public bool:IsFeatureEnabled(const toggle[])
{
    new 
        query[MAX_QUERY_SIZE],
        Cache:result,
        toggleEnabled,
        toggleId,
        rows;

    format(query, sizeof(query), "select id, enabled from feature_toggles where toggle_key = '%s'", toggle);
    result = mysql_query(MySQL:GetMySQLHandle(), query);

    cache_get_row_count(rows);

    if (rows == 0)
    {
        log_critical(FileNamespace(), "[IsFeatureEnabled] the requested toggle %s doesn't exist, returning false as default value", toggle);
        return false;
    }

    cache_get_value_name_int(0, "enabled", toggleEnabled);
    cache_get_value_name_int(0, "id", toggleId);

    FeatureToggleCacheIndex[toggleId] = result;

    if (toggleEnabled == 1) {
        return true;
    }

    return false;
}

public SetFeatureEnabled(const toggle[], bool:enabled)
{
    new query[MAX_QUERY_SIZE];

    new toggleId = GetToggleIdFromKey(toggle);

    if (toggleId == -1) {
        log_critical(FileNamespace(), "[GetToggleIdFromKey] failed while setting toggle %s enable status as %d", toggle, enabled);
    }

    format(query, sizeof(query), "update feature_toggles set enabled = %d where toggle_key = '%s'", enabled, toggle);
    mysql_query(MySQL:GetMySQLHandle(), query);

    if (FeatureToggleCacheIndex[toggleId]) {
        cache_delete(FeatureToggleCacheIndex[toggleId]);
    }

    return cache_affected_rows();
}

static stock FileNamespace()
{
    new namespace[64] = "FeatureToggles";
    return namespace;
}