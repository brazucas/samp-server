#include <BRZ_SAMP\screen_fader>
#include <YSI_Coding\y_hooks>

#define HUNGER_HEALTH_PUNISHMENT 10.0

enum SleepMessage {
    LEVEL,
    MESSAGE[128]
}

new sleepMessages[5][128] = {
    {72, "Voce esta com sono, voce precisa dormir."},
    {74, "Voce esta com muito sono, voce precisa dormir."},
    {76, "Voce esta com muito muito sono, voce precisa dormir."},
    {78, "Voce esta com muito muito muito sono, voce precisa dormir."},
    {80, "Voce esta com muito muito muito muito sono, voce precisa dormir."}
};

static stock GetSleepMessageForLevel(level)
{
    for (new index = 0; index < sizeof(sleepMessages); index++) {
        if (sleepMessages[index][LEVEL] == level) {
            return sleepMessages[index][MESSAGE];
        }
    }
    return "";
}

hook OnMaxHungerLevelReached(playerid)
{
    HungerThirstPunishment(playerid);
    continue();
}

hook OnMaxThirstLevelReached(playerid)
{
    HungerThirstPunishment(playerid);
    continue();
}

hook OnPlayerSleepUpdate(playerid, level)
{
    if (level >= 100) {
        SendClientMessage(playerid, 0xFF000000, "Acabou dormindo sozinho...~n~Você não é uma máquina!");
        FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, SLOW_FADE);
        PlayerPlaySound(playerid,1076,0,0,0);
        
        if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
            ApplyAnimation(playerid,"CRACK","crckidle2",4.1,1,1,1,1,1);
        }
    } else if (strlen(sleepMessages[level])) {
        if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
            ApplyAnimation(playerid,"FAT","IDLE_tired",4.1,0,0,0,0,0);
        }

        SendClientMessage(playerid, 0xFF000000, sleepMessages[level]);
        FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, NORMAL_FADE);
    }

    continue();
}

static stock HungerThirstPunishment(playerid)
{
    new Float:playerHealth;
    GetPlayerHealth(playerid, playerHealth);

    ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);
    SetPlayerHealth(playerid, playerHealth - HUNGER_HEALTH_PUNISHMENT);
}