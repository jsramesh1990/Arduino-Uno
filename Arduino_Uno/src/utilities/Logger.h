#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "config.h"

enum LogLevel {
    LOG_NONE = 0,
    LOG_ERROR = 1,
    LOG_WARNING = 2,
    LOG_INFO = 3,
    LOG_DEBUG = 4,
    LOG_VERBOSE = 5,
    LOG_SUCCESS = 6
};

class Logger {
public:
    Logger();
    void begin();
    
    void log(String message, LogLevel level = LOG_INFO);
    void logError(String message);
    void logWarning(String message);
    void logInfo(String message);
    void logDebug(String message);
    void logVerbose(String message);
    void logSuccess(String message);
    
    void logSensorData(SensorData data);
    void logTestResults(TestResults results);
    void logCommunicationData(CommunicationData data);
    void logSystemState(SystemState state);
    
    void setLogLevel(LogLevel level);
    void enableTimeStamps(bool enable);
    void enableColors(bool enable);
    
    String getLogs();
    void clearLogs();
    void saveLogs();
    size_t getLogSize();

private:
    LogLevel m_currentLevel;
    bool m_timestamps;
    bool m_colors;
    
    String m_logBuffer;
    static const int MAX_LOG_SIZE = 10000;
    
    String getTimestamp();
    String getLevelString(LogLevel level);
    String colorize(String message, LogLevel level);
    void appendToLog(String message);
};

#endif // LOGGER_H
