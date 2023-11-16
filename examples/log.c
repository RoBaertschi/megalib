//
// Created by rtmba on 11.11.2023.
//

#define ML_LOG_IMPLEMENTATION
#include "megalib/logging/log.h"

/// Example of the logging system in megalib, also used for testing purposes
int main(void) {
    LOG("Hello World");
    LOG_INFO("LOG_LEVEL_INFO");
    LOG_WARN("Warning");
    LOG_ERROR("Error");
}