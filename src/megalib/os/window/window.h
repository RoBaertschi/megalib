
/**
 * @file window.h
 * @brief Simple window interface
 *
 * All functions use the prefix mlw which stands for megalib window. It exsists for shorter names.
 * TODO: Everything
 */

//
// Created by rtmba on 12.11.2023.
//

#ifndef MEGALIB_WINDOW_H
#define MEGALIB_WINDOW_H

#ifdef WINDOWS
#   include "windows.h"
#endif

#include <stdlib.h>
#include "megalib/megalib.h"
#include "megalib/logging/logger.h"

typedef enum WindowType {
    WINDOW_TYPE_WIN32,
} WindowType;


#ifdef WINDOWS
typedef struct win32_t {
    HWND hwnd;
    HDC dc;
} win32_t;
#endif

typedef struct window_t {
    WindowType type;
    union {
#ifdef WINDOWS
        win32_t win32;
#endif
    };
} window_t;

///// Initialization ////////

ML_API void mlw_set_logger(logger_t*);
ML_API window_t* mlw_create(const char* title);


///// Runtime Functions /////

ML_API void mlw_poll_events(window_t* window);
ML_API bool mlw_should_close(window_t* window);


///// Free window ////////////

ML_API void mlw_destory(window_t* window);

#endif //MEGALIB_WINDOW_H
