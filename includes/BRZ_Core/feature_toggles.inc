#include <a_mysql>
#include <YSI_Coding\y_hooks>
#include <BRZ_Datasource\mysql_migrations>
#include <BRZ_Core\Feature_Toggles\feature_toggles_helpers>

forward bool:IsFeatureEnabled(const toggle[]);

stock bool:IsFeatureEnabled(const toggle[])
{
    if (strcmp(toggle, "core.my-feature.enabled", true) == 0) {
        return true;
    }

    return false;
}

static stock FileNamespace()
{
    new namespace[64] = "FeatureToggles";
    return namespace;
}