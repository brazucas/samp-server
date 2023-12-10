forward bool:IsBRZVoipEnabled();

public bool:IsBRZVoipEnabled()
{
    #if defined BRZ_VOIP_ENABLED
        return true;
    #else
        return false;
    #endif
}