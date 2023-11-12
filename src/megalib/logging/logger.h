//
// Created by rtmba on 12.11.2023.
//

#ifndef MEGALIB_LOGGER_H
#define MEGALIB_LOGGER_H
#include "log.h"

typedef struct logger_t {
    enum LogLevel level;
    const char* name;
} logger_t;

ML_API logger_t ml_create_logger(const char* name);
ML_API void ml_logger_log(logger_t* logger, enum LogLevel level, const char * text);

#endif //MEGALIB_LOGGER_H

#ifdef ML_LOGGER_IMPLEMENTATION

ML_API struct logger_t ml_create_logger(const char* name) {
    logger_t logger = {
            INFO,
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
#endif
