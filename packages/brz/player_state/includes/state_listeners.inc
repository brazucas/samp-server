#include <YSI_Coding\y_hooks>

#define HUNGER_HEALTH_PUNISHMENT 10.0

hook OnMaxHungerLevelReached(playerid)
{
    new Float:playerHealth;
    GetPlayerHealth(playerid, playerHealth);

    ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0);
    SetPlayerHealth(playerid, playerHealth - HUNGER_HEALTH_PUNISHMENT);
    continue();
}