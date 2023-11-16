//
// Created by rtmba on 15.11.2023.
//

#include "log.h"



ML_API void ml_log(const char* file, int line, enum LogLevel type, const char* text) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time[64];
    size_t ret = strftime(time, sizeof(time), "%H:%M:%S", tm);
    if (!ret) {
        strncpy(time, "N/A", 3);
    }

    printf("%s[%s] (%s %i)%s: %s\033[0m \n", ml_log_level_color_string(type), time, file, line, ml_log_level_string(type), text);
}
ML_API char * ml_log_level_string(enum LogLevel type) {
    char* value;
    switch (type) {
        case LOG_LEVEL_LOG:
            value = "";
            break;
        case LOG_LEVEL_INFO:
            value = " [LOG_LEVEL_INFO]";
            break;
        case LOG_LEVEL_WARN:
            value = " [LOG_LEVEL_WARN]";
            break;
        case LOG_LEVEL_ERROR:
            value = " [LOG_LEVEL_ERROR]";
            break;
    }

    return value;
}
ML_API char * ml_log_level_color_string(enum LogLevel type) {
    char* value;
    switch (type) {
        case LOG_LEVEL_LOG:
        case LOG_LEVEL_INFO:
            value = "";
            break;
        case LOG_LEVEL_WARN:
            value = "\033[33m";
            break;
        case LOG_LEVEL_ERROR:
            value = "\033[31m";
    }

    return value;
}

