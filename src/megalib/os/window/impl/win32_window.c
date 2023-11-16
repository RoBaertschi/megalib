//
// Created by TAABAROY on 16.11.2023.
//

#include "../window.h"
#include "windows.h"
#include "megalib/logging/logger.h"

#ifdef WINDOWS

static logger_t* logger = NULL;

static bool should_close = false;

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

ML_API void mlw_set_logger(logger_t* new_logger) {
    logger = new_logger;
}

ML_API window_t* mlw_create(const char* title) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    LPCSTR CLASS_NAME = (const char*) "Window";

    WNDCLASS windowClass = {
            .hInstance = hInstance,
            .lpszClassName = CLASS_NAME,
            .lpfnWndProc = wndProc,
            .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
            .hCursor = LoadCursor(0, IDC_ARROW),
            .hIcon = LoadIcon(0, IDI_APPLICATION)
    };

    if (!RegisterClass(&windowClass)) {
        if (logger) {
            char msg[200];
            sprintf(msg, "Failed to register Win32 Window class for window creation. Error: %lu", GetLastError());

            ml_logger_log(logger, LOG_LEVEL_ERROR, msg);
        }
        return NULL;
    }

    window_t* window = ML_MALLOC(sizeof(window_t));

    window->win32.hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL
            );

    window->type = WINDOW_TYPE_WIN32;

    SetWindowLongPtr(window->win32.hwnd, GWLP_USERDATA, (LONG_PTR) window);
    if (!window->win32.hwnd) {
        if(logger) {
            ml_logger_log(logger, LOG_LEVEL_ERROR, "Could not create Win32 window.");
        }
        return NULL;
    }

    ShowWindow(window->win32.hwnd, 1);

    return window;
}

ML_API void mlw_poll_events(window_t* window) {
    MSG msg;
    while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {

        if (msg.message == WM_QUIT) {
            ml_logger_log(logger, LOG_LEVEL_INFO, "Hello?");
            should_close = true;
            return;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

ML_API bool mlw_should_close(window_t* window) {

    return should_close;
}

ML_API void mlw_destory(window_t* window) {
    ML_FREE(window);
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_QUIT:
            should_close = true;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}


#endif