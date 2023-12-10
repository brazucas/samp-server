#include <a_samp>
#include <YSI_Coding\y_hooks>

#if defined BRZ_VOIP_ENABLED
	#include <sampvoice>
#else
	#include <sampvoice_mock>
#endif

#include <state>
#include <api>
#include <brz_scripting>

#define VOIP_NAMESPACE "BRZ_VOIP"

#define GLOBAL_CHANNEL 0
#define  LOCAL_CHANNEL 1

new SV_UINT:gstream = SV_NONE;
new SV_UINT:lstream[MAX_PLAYERS] = { SV_NONE, ... };

public OnFilterScriptInit()
{
	print("========================BRZ_PLAYER_VOIP STARTED========================");

	if (!IsBRZVoipEnabled()) {
		log_info(VOIP_NAMESPACE, "VOIP is not enabled");
		return 1;
	}

	#if defined BRZ_VOIP_DEBUG
    	SvEnableDebug();
	#endif
	
    gstream = SvCreateStream();

	return 1;
}

public OnFilterScriptExit()
{
	print("========================BRZ_PLAYER_VOIP STOPPED========================");

	if (!IsBRZVoipEnabled()) {
		return 1;
	}

	if (gstream != SV_NONE)
    {
        SvDeleteStream(gstream);
        gstream = SV_NONE;
    }

	return 1;
}

public OnPlayerConnect(playerid)
{
	if (!IsBRZVoipEnabled()) {
		return 1;
	}

    if (SvGetVersion(playerid) == 0) {
        return SetVoipSupported(playerid, false);
    }

	SetVoipSupported(playerid, true);
    
	if (SvHasMicro(playerid) == SV_FALSE) {
        SetMicAvailable(playerid, false);
    }

	SetMicAvailable(playerid, true);

	if (gstream != SV_NONE) {
		SvSetKey(playerid, 0x5A, GLOBAL_CHANNEL); // Z key
		SvAttachStream(playerid, gstream, GLOBAL_CHANNEL);
		SvAttachListener(gstream, playerid);
		SvSetIcon(gstream, "speaker");

		SendClientMessage(playerid, -1, "Press Z to talk to global chat.");
	}

	if ((lstream[playerid] = SvCreateStream(40.0)) != SV_NONE) {
		SvSetKey(playerid, 0x42, LOCAL_CHANNEL); // B key
		SvAttachStream(playerid, lstream[playerid], LOCAL_CHANNEL);
		SvSetTarget(lstream[playerid], SvMakePlayer(playerid));
		SvSetIcon(lstream[playerid], "speaker");

		SendClientMessage(playerid, -1, "Press B to talk to local chat.");
	}

	SetVoipEnabled(playerid, true);
	SetMicEnabled(playerid, true);

	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if (!IsBRZVoipEnabled()) {
		return 1;
	}

    if (lstream[playerid] != SV_NONE)
    {
        SvDeleteStream(lstream[playerid]);
        lstream[playerid] = SV_NONE;
    }

	return 1;
}