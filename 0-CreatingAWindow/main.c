#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdbool.h>
#include <stdio.h>

void glv(int v, const char *msg) {
    if (v < 0) {
        fprintf(stderr, "%s: %s\n", msg, SDL_GetError());
        exit(1);
    }
}

void *glp(void *ptr, const char *msg) {
    if (!ptr) {
        fprintf(stderr, "%s: %s\n", msg, SDL_GetError());
        exit(1);
    }
    return ptr;
}


void handle_events(bool *quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                *quit = true;
                break;
        }
    }
}

int main() {
    glv(SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize");

    SDL_Window *window = glp(
        SDL_CreateWindow("Window Test",
                         SDL_WINDOWPOS_CENTERED, 
                         SDL_WINDOWPOS_CENTERED, 
                         640, 
                         480, 
                         SDL_WINDOW_OPENGL
        ),
    "Window could not be created");

    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3), "Failed to set version");
    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3), "Failed to set version");
    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE), "Failed to set core profile");

    SDL_GLContext context = glp(SDL_GL_CreateContext(window), "OpenGL context could not be created");

    bool quit = false;
    while (!quit) {
        handle_events(&quit);
        glClearColor(0.0f, 0.8f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
        SDL_Delay(1000.0f / 60);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}