#define MAX_QUERY_SIZE 512

#include <a_samp>
#include <brz_core>
#include <brz_datasource>
#include <BRZ_Core\feature_toggles>

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

    SendRconCommand("loadfs brz_player_authentication");
    
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
