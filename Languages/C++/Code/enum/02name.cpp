#include <iostream>

using namespace std;

enum class Level
{
    /// Most verbose debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG9,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG8,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG7,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG6,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG5,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG4,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG3,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG2,

    /// Intermediate debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG1,

    /// Least verbose debug log level. Compiled out when ACSDK_DEBUG_LOG_ENABLED is not defined.
    DEBUG0,

    /// Logs of normal operations, to be used in release builds.
    INFO,

    /// Log of an event that may indicate a problem.
    WARN,

    /// Log of an event that indicates an error.
    ERROR,

    /// Log of a event that indicates an unrecoverable error.
    CRITICAL,

    /// Level used to disable all logging.
    NONE,

    /// An unknown severity level.
    UNKNOWN
};

#define LEVEL_TO_NAME(name) \
    case Level::name:       \
        return #name;
     // return "name_val";

std::string convertLevelToName(Level in)
{
    // Level::in;
    switch (in)
    {
        LEVEL_TO_NAME(DEBUG9)
        LEVEL_TO_NAME(DEBUG8)
        LEVEL_TO_NAME(DEBUG7)
        LEVEL_TO_NAME(DEBUG6)
        LEVEL_TO_NAME(DEBUG5)
        LEVEL_TO_NAME(DEBUG4)
        LEVEL_TO_NAME(DEBUG3)
        LEVEL_TO_NAME(DEBUG2)
        LEVEL_TO_NAME(DEBUG1)
        LEVEL_TO_NAME(DEBUG0)
        LEVEL_TO_NAME(INFO)
        LEVEL_TO_NAME(WARN)
        LEVEL_TO_NAME(ERROR)
        LEVEL_TO_NAME(CRITICAL)
        LEVEL_TO_NAME(NONE)
        LEVEL_TO_NAME(UNKNOWN)
    }
    return "UNKNOWN";
}

int main(int argc, char *argv[])
{
    // cout << LEVEL_TO_NAME("UNKNOWN") << endl;

    // cout << Level::UNKNOWN << endl;

    cout << convertLevelToName(Level::DEBUG0) << endl;
    return 0;
}