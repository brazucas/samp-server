#include <YSI_Visual\y_dialog>

stock ShowAlert(playerid, const title[], const message[], const callback[])
{
    inline Handler(response, listitem, string:inputtext[])
	{
		#pragma unused listitem,response,inputtext

		CallLocalFunction(callback, "i", playerid);
		return 1;
	}
	Dialog_ShowCallback(playerid, using inline Handler, DIALOG_STYLE_MSGBOX, title, message, "OK");

    return 1;
}