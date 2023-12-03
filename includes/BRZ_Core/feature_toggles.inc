enum FeatureToggles {
    FF_AUTHENTICATION,
}

forward bool:IsFeatureEnabled(FeatureToggles:toggle);

stock bool:IsFeatureEnabled(FeatureToggles:toggle)
{
    if (toggle == FF_AUTHENTICATION) {
        return true;
    }

    return false;
}