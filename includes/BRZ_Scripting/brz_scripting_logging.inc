enum LOG_TYPE
{
    LOG_TYPE_DEBUG,
    LOG_TYPE_INFO,
    LOG_TYPE_WARNING,
    LOG_TYPE_ERROR,
    LOG_TYPE_CRITICAL
}

#define log_debug( log(LOG_TYPE_DEBUG, 
#define log_info( log(LOG_TYPE_INFO, 
#define log_warning( log(LOG_TYPE_WARNING, 
#define log_error( log(LOG_TYPE_ERROR, 
#define log_critical( log(LOG_TYPE_CRITICAL, 

stock log(LOG_TYPE:type, const namespace[], const fstring[], {Float,_}:...)
{
    new message[128];

    static const STATIC_ARGS = 3;
    new n = (numargs() - STATIC_ARGS) * 4;

    if (n) {
        new
            arg_start,
            arg_end;

        #emit CONST.alt        fstring
        #emit LCTRL          5
        #emit ADD
        #emit STOR.S.pri       arg_start

        #emit LOAD.S.alt       n
        #emit ADD
        #emit STOR.S.pri       arg_end

        do
        {
            #emit LOAD.I
            #emit PUSH.pri
            arg_end -= 4;
            #emit LOAD.S.pri     arg_end
        }
        while (arg_end > arg_start);

        #emit PUSH.S         fstring
        #emit PUSH.C         128
        #emit PUSH.ADR        message

        n += 4 * 3;
        #emit PUSH.S         n
        #emit SYSREQ.C        format

        n += 4;
        #emit LCTRL          4
        #emit LOAD.S.alt       n
        #emit ADD
        #emit SCTRL          4
    } else {
        format(message, sizeof(message), "%s", fstring);
    }

    printf("::%s:%s:: %s", namespace, GetLogType(type), message);
}

stock GetLogType(LOG_TYPE:type)
{
    new logType[16] = "Debug";

    switch (type)
    {
        case LOG_TYPE_DEBUG:
        {
            format(logType, sizeof(logType), "DEBUG");
        }
        case LOG_TYPE_WARNING:
        {
            format(logType, sizeof(logType), "WARNING");
        }
        case LOG_TYPE_ERROR:
        {
            format(logType, sizeof(logType), "ERROR");
        }
        case LOG_TYPE_CRITICAL:
        {
            format(logType, sizeof(logType), "CRITICAL");
        }
    }

    return logType;
}