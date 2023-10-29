#include <YSI_Data\y_hashmap>

#define MAX_MOCK_FUNCTIONS 100
#define MAX_FUNCTION_CALLS 100
#define MAX_FUNCTION_NAME 32
#define MAX_FUNCTION_PARAMS_VALUE 2048

#define ASSERT_CALL(%0) ASSERT_TRUE(MOCK_CALL(%0))
#define ASSERT_CALL_COUNT(%0) ASSERT_TRUE(MOCK_CALL_COUNT(%0))

enum MockFunctionCallMap
{
    FunctionName[MAX_FUNCTION_NAME],
    Calls,
}

static
    totalCalls,
    callsParams[MAX_FUNCTION_CALLS][MAX_FUNCTION_PARAMS_VALUE],
    callsMockData[MAX_MOCK_FUNCTIONS][MockFunctionCallMap],
    HashMap:mapCalls<>;

stock MockInit()
{
    HashMap_Init(mapCalls, callsMockData, Calls);
}

stock MockReset(const functionName[])
{
    HashMap_Set(mapCalls, functionName, 0);
}

stock MOCK_CALL_COUNT(const function[], count)
{
    new calls = HashMap_Get(mapCalls, function);

    if (calls <= 0) {
        calls = 0;
    }

    return calls == count;
}

stock MOCK_CALL(const functionName[], const stringFormat[], {Float,_}:...)
{
    new formatIndex = 0,
        argumentIndex = 2,
        argumentCount = numargs(),
        paramsAsString[MAX_FUNCTION_PARAMS_VALUE] = "",
        match = 0;

    while(argumentIndex < argumentCount) 
    {
        switch(stringFormat[formatIndex])
        {
            case 'i', 'd': 
            {
                format(paramsAsString, sizeof(paramsAsString), "%s%d", paramsAsString, getarg(argumentIndex));
            }
            case 's': 
            {
                new stringArg[128] = "",
                    index = 0;

                while(getarg(argumentIndex, index) != '\0') {
                    format(stringArg, sizeof(stringArg), "%s%c", stringArg, getarg(argumentIndex, index++));
                }

                format(paramsAsString, sizeof(paramsAsString), "%s%s", paramsAsString, stringArg);
            }
        }

        ++argumentIndex;
        ++formatIndex;
    }

    format(paramsAsString, sizeof(paramsAsString), "%s%s", functionName, paramsAsString);

    for(new i = 0; i < totalCalls; i++)
    {
        if(!strcmp(callsParams[i], paramsAsString))
        {
            match = 1;
        }
    }

    return match;
}

stock RegisterCall(const functionName[], const stringFormat[], {Float,_}:...)
{
    new formatIndex = 0,
        argumentIndex = 2,
        argumentCount = numargs(),
        paramsAsString[MAX_FUNCTION_PARAMS_VALUE] = "";

    while(argumentIndex < argumentCount) 
    {
        switch(stringFormat[formatIndex])
        {
            case 'i', 'd': 
            {
                format(paramsAsString, sizeof(paramsAsString), "%s%d", paramsAsString, getarg(argumentIndex));
            }
            case 's': 
            {
                new stringArg[128] = "",
                    index = 0;

                while(getarg(argumentIndex, index) != '\0') {
                    format(stringArg, sizeof(stringArg), "%s%c", stringArg, getarg(argumentIndex, index++));
                }

                format(paramsAsString, sizeof(paramsAsString), "%s%s", paramsAsString, stringArg);
            }
        }

        ++argumentIndex;
        ++formatIndex;
    }

    new calls = HashMap_Get(mapCalls, functionName);

    if (calls <= 0) {
        calls = 0;
    }

    calls++;
    HashMap_Set(mapCalls, functionName, calls);

    format(callsParams[totalCalls], sizeof(callsParams[]), "%s%s", functionName, paramsAsString);
    totalCalls++;
}

#include <tests\Y_Testing_Mocks\native_mocks>