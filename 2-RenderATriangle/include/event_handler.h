#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdbool.h>

#include "window_manager.h"

extern uint32_t g_width;
extern uint32_t g_height;

void handle_events(bool *quit);


#endif //EVENT_HANDLER_H
