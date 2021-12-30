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

SDL_GLContext initialize(SDL_Window *window) {
    glv(SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize");

    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4), "Failed to set version");
    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5), "Failed to set version");

    window = glp(SDL_CreateWindow("Window Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE), "Window could not be created");
    SDL_GLContext context = glp(SDL_GL_CreateContext(window), "OpenGL context could not be created");

    glClearColor(0,0,0,1);
    return context;
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

void render(SDL_Window *window) {
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    SDL_Window *window;
    SDL_GLContext context = initialize(window);

    bool quit = false;
    while (!quit) {
        handle_events(&quit);
        render(window);
        SDL_Delay(1000.0f / 60);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}