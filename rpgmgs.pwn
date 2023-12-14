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

        SendRconCommand("loadfs brz_player_authentication");
        SendRconCommand("loadfs brz_player_state");
        SendRconCommand("loadfs brz_player_voip");
        SendRconCommand("loadfs brz_admin");
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
