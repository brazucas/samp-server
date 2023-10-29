#include <a_samp>
#include <brz_core>
#include <brz_datasource>

#if defined RUN_TESTS
    #include <tests\main>
#endif

public OnGameModeInit()
{
    #if !defined RUN_TESTS
        BRZ_Datasource_InitDatasources();
    #endif

    #if defined RUN_TESTS
        SendRconCommand("exit");
    #endif
    
    return 1;
}

public OnGameModeExit()
{
    #if !defined RUN_TESTS
        BRZ_Datasource_ExitDatasources();
    #endif
    return 1;
}

main() 
{
}
