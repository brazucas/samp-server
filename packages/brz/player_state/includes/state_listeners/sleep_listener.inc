#include <BRZ_SAMP\screen_fader>
#include <YSI_Coding\y_hooks>

#define SLEEP_MESSAGES_SIZE 5
#define HUNGER_HEALTH_PUNISHMENT 10.0

forward OnPlayerSleepUpdate(playerid, level);

enum SleepMessage {
    LEVEL,
    MESSAGE[128]
}

new sleepMessages[SLEEP_MESSAGES_SIZE][SleepMessage] = {
    {72, "Voce esta com sono, voce precisa dormir."},
    {74, "Voce esta com muito sono, voce precisa dormir."},
    {76, "Voce esta com muito muito sono, voce precisa dormir."},
    {78, "Voce esta com muito muito muito sono, voce precisa dormir."},
    {80, "Voce esta com muito muito muito muito sono, voce precisa dormir."}
};

static stock GetSleepMessageForLevel(level, message[])
{
    for (new index = 0; index < sizeof(sleepMessages); index++) {
        if (sleepMessages[index][LEVEL] == level) {
            format(message, 128, "%s", sleepMessages[index][MESSAGE]);
            return 1;
        }
    }

    format(message, 128, "");
    return 0;
}

hook OnMaxSleepLevelReached(playerid)
{
    SendClientMessage(playerid, 0xFF000000, "Acabou dormindo sozinho...~n~Você não é uma máquina!");
    FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, SLOW_FADE);
    PlayerPlaySound(playerid,1076,0,0,0);
    
    if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
        ApplyAnimation(playerid,"CRACK","crckidle2",4.1,1,1,1,1,1);
    }

    continue();
}

public OnPlayerSleepUpdate(playerid, level)
{    
    new message[128];
    GetSleepMessageForLevel(level, message);

    if (strlen(message)) {
        if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
            ApplyAnimation(playerid,"FAT","IDLE_tired",4.1,0,0,0,0,0);
        }

        SendClientMessage(playerid, 0xFF000000, message);
        FadePlayerScreenToColor(playerid, FADE_COLOR_BLACK, NORMAL_FADE);
    }

    return 1;
}