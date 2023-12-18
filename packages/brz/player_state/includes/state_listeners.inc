#include <state_listeners\sleep_listener>
#include <YSI_Coding\y_hooks>

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

static stock HungerThirstPunishment(playerid)
{
    new Float:playerHealth;
    GetPlayerHealth(playerid, playerHealth);

    ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);
    SetPlayerHealth(playerid, playerHealth - HUNGER_HEALTH_PUNISHMENT);
}