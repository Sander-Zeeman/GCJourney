#include "include/event_handler.h"

void handle_events(bool *quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                *quit = true;
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    updateWindowSize(e.window.data1, e.window.data2);
        }
    }
}
