#include "include/window_manager.h"

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

void updateWindowSize(uint32_t width, uint32_t height) {
    g_width = width;
    g_height = height;
    glViewport(0, 0, g_width, g_height);
}

SDL_GLContext prepare(SDL_Window **window) {
    glv(SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize");

    *window = glp(
            SDL_CreateWindow("Window Test",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             g_width,
                             g_height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
            ),
            "Window could not be created");

    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3), "Failed to set version");
    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3), "Failed to set version");
    glv(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE), "Failed to set core profile");

    SDL_GLContext context = glp(SDL_GL_CreateContext(*window), "OpenGL context could not be created");
    glViewport(0, 0, g_width, g_height);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW failed to initialize\n");
        exit(1);
    }

    return context;
}

