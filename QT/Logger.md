

https://github.com/Mokolea/SimpleQtLogger



初始化

```c++
void _initLogger() {
    Q_ASSERT_X(SQTL_VERSION >= SQTL_VERSION_CHECK(1, 2, 0), "main", "utils version");

    // enable sinks
    ENABLE_LOG_SINK_FILE = true;
    ENABLE_LOG_SINK_CONSOLE = true;
    ENABLE_LOG_SINK_QDEBUG = false;
    ENABLE_LOG_SINK_SIGNAL = false;
    // set log-features
    ENABLE_FUNCTION_STACK_TRACE = true;
    ENABLE_CONSOLE_COLOR = true;
    ENABLE_CONSOLE_TRIMMED = true;
    ENABLE_CONSOLE_LOG_FILE_STATE = true;
    // set log-levels (global; all enabled)
    ENABLE_LOG_LEVELS.logLevel_DEBUG = true;
    ENABLE_LOG_LEVELS.logLevel_FUNCTION = true;
    // set log-levels (specific)
    EnableLogLevels enableLogLevels_file = ENABLE_LOG_LEVELS;
    EnableLogLevels enableLogLevels_console = ENABLE_LOG_LEVELS;
    EnableLogLevels enableLogLevels_qDebug = ENABLE_LOG_LEVELS;
    EnableLogLevels enableLogLevels_signal = ENABLE_LOG_LEVELS;
    enableLogLevels_console.logLevel_FUNCTION = false;
    EnableLogLevels enableLogLevels_fileWarn = ENABLE_LOG_LEVELS;
    enableLogLevels_fileWarn.logLevel_NOTE = false;
    enableLogLevels_fileWarn.logLevel_INFO = false;
    enableLogLevels_fileWarn.logLevel_DEBUG = false;
    enableLogLevels_fileWarn.logLevel_FUNCTION = false;

    // initialize logger (step 1/2)

    Logger::createInstance(qApp);
    Logger::getInstance()->setLogFormat_file("<TS> [<LL>] <TEXT> (<FUNC>@<FILE>:<LINE>)", "<TS> [<LL>] <TEXT>");
    Logger::getInstance()->setLogLevels_file(enableLogLevels_file);
    // todo: 目录需要检查确// todo: 目录需要检查确认
    Logger::getInstance()->setLogFileName(QDir::home().filePath("FactoryTest/Logs/testloggerGui.log"), 10 * 1000, 10);
    Logger::getInstance()->setLogLevels_console(enableLogLevels_console);
    Logger::getInstance()->setLogLevels_qDebug(enableLogLevels_qDebug);
    Logger::getInstance()->setLogLevels_signal(enableLogLevels_signal);
}

```



使用:

```c++
    L_INFO("+++ test Logger");
    L_FATAL("L_FATAL");
    L_ERROR("L_ERROR");
    L_WARN("L_WARN");
    L_NOTE("L_NOTE");
    L_INFO("L_INFO");
    L_DEBUG("L_DEBUG");
    L_INFO("--- test Logger");

    L_INFO(QString());           // --> "?"
    L_INFO(QString("xixi"));     // --> "xixi"
    L_INFO(" \n Trimmed \n\n");  // --> 两边的空格换行会被删除掉
    L_INFO("UTF-8 Unicode text: äöü àéè");
```

