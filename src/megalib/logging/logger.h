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

