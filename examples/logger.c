//
// Created by rtmba on 12.11.2023.
//
#define ML_LOGGER_IMPLEMENTATION
#define ML_LOG_IMPLEMENTATION
#include "megalib/logging/logger.h"

int main(void) {
    logger_t logger1 = ml_create_logger("Logger 1");
    ml_logger_log(&logger1, LOG, "Hello World!");
    ml_logger_log(&logger1, INFO, "Hello World!");
    ml_logger_log(&logger1, WARN, "Hello World!");
    ml_logger_log(&logger1, ERROR, "Hello World!");

    logger_t  logger2 = ml_create_logger("Hello Test");
    ml_logger_log(&logger2, WARN, "Welp");
}
