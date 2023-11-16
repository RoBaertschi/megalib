/**
 * @file log.h
 * @brief Simple Logging library written in C11
 */

//
// Created by rtmba on 11.11.2023.
// Resources:
// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences


#ifndef MEGALIB_LOG_H
#define MEGALIB_LOG_H

#include "megalib/megalib.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

/**
 * @def LOG_FILENAME
 * @brief The filename of the current file
 *
 * Used for accessing the name of the file where something gets logged.
 */

#ifdef WINDOWS
#   define LOG_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#else
#   define LOG_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifndef LOG
#   define LOG(text) ml_log(LOG_FILENAME, __LINE__, LOG, text)
#endif
#ifndef LOG_INFO
#   define LOG_INFO(text) ml_log(LOG_FILENAME, __LINE__, INFO, text)
#endif
#ifndef LOG_WARN
#   define LOG_WARN(text) ml_log(LOG_FILENAME, __LINE__, WARN, text)
#endif
#ifndef LOG_ERROR
#   define LOG_ERROR(text) ml_log(LOG_FILENAME, __LINE__, ERROR, text)
#endif

enum LogLevel {
    LOG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

ML_API void ml_log(const char* file, int line, enum LogLevel type, const char * text);
ML_API char * ml_log_level_string(enum LogLevel type);
ML_API char * ml_log_level_color_string(enum LogLevel type);

#endif //MEGALIB_LOG_H
