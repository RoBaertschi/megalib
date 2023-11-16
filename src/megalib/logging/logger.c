//
// Created by rtmba on 15.11.2023.
//

#include "logger.h"

ML_API struct logger_t ml_create_logger(const char* name) {
    logger_t logger = {
            LOG_LEVEL_INFO,
            name,
    };

    return logger;
}
ML_API void ml_logger_log(logger_t* logger, enum LogLevel level, const char * text) {
    if (logger->level > level) {
        return;
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time[64];
    size_t ret = strftime(time, sizeof(time), "%H:%M:%S", tm);
    if (!ret) {
        strncpy(time, "N/A", 3);
    }

    printf("%s[%s] (%s)%s: %s\033[0m \n", ml_log_level_color_string(level), time, logger->name, ml_log_level_string(level), text);
}
