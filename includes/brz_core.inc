#include <BRZ_Core\brz_core_interface>

public BRZ_Core_GetBRZVersion()
{
    return 1;
}

public BRZ_Core_CloseServer()
{
    SendRconCommand("exit");
    return 1;
}