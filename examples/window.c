//
// Created by TAABAROY on 16.11.2023.
//

#include "megalib/os/window/window.h"

int main(void) {
    logger_t logger = ml_create_logger("Window Logger");
    mlw_set_logger(&logger);
    window_t * window = mlw_create("Hello World");

    if (window == NULL) {
        return 1;
    }

    while(!mlw_should_close(window)) {
        mlw_poll_events(window);
    }

    mlw_destory(window);
}