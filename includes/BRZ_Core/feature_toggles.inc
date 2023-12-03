enum FeatureToggles {
    RPG_ENABLED,
}

forward bool:IsFeatureEnabled(FeatureToggles:toggle);

stock bool:IsFeatureEnabled(FeatureToggles:toggle)
{
    if (toggle == RPG_ENABLED) {
        return true;
    }

    return false;
}