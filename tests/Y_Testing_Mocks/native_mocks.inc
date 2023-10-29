static params[MAX_FUNCTION_PARAMS_VALUE];

stock MOCK_SendClientMessage(playerid, color, const message[]) 
{
    format(params, sizeof(params), "%d %d %s", playerid, color, message);
    RegisterCall("SendClientMessage", params);
}

#define _ALS_SendClientMessage
#define SendClientMessage( MOCK_SendClientMessage(