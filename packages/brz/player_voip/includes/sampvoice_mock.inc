enum SV_UINT
{
    SV_NONE,
    SV_FALSE,
}

stock SvEnableDebug()
{
    return 1;
}

stock SV_UINT:SvCreateStream({Float,_}:...)
{
    return SV_NONE;
}

stock SvDeleteStream({SV_UINT,_}: ...)
{
    return 1;
}

stock SvGetVersion({SV_UINT,_}:...)
{
    return 1;
}

stock SV_UINT:SvHasMicro({SV_UINT,_}:...)
{
    return SV_FALSE;
}

stock SvSetKey({SV_UINT,_}:...)
{
    return 1;
}

stock SvAttachStream({SV_UINT,_}:...)
{
    return 1;
}

stock SvAttachListener({SV_UINT,_}:...)
{
    return 1;
}

stock SvSetIcon({SV_UINT,_}:...)
{
    return 1;
}

stock SvSetTarget({SV_UINT,_}:...)
{
    return 1;
}

stock SvMakePlayer(...)
{
    return 1;
}