#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <stdint.h>

extern uint32_t g_width;
extern uint32_t g_height;

void glv(int v, const char *msg);
void *glp(void *ptr, const char *msg);

void updateWindowSize(uint32_t width, uint32_t height);
SDL_GLContext prepare(SDL_Window **window);

#endif //WINDOW_MANAGER_H
