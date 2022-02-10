#include "include/event_handler.h"
#include "include/shader_translator.h"
#include "include/window_manager.h"

#include "include/Vec3.h"

#define VERTEX_SHADER_LOC "../shaders/vertex.glsl"
#define FRAGMENT_SHADER_LOC "../shaders/fragment.glsl"

uint32_t g_width = 640;
uint32_t g_height = 480;

int main() {
    SDL_Window *window;
    SDL_GLContext context = prepare(&window);

    Vec3 triangle[3] = {
       {
            .x =-0.5f,
            .y =-0.5f,
            .z =0.0f
        },
        {
            .x =0.0f,
            .y =0.5f,
            .z =0.0f
        },
        {
            .x =0.5f,
            .y =-0.5f,
            .z =0.0f
        }
    };

    uint32_t vao;
    glGenVertexArrays(1, &vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    prepareShader(VERTEX_SHADER_LOC, FRAGMENT_SHADER_LOC);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    bool quit = false;
    while (!quit) {
        handle_events(&quit);

        checkShaderModification(VERTEX_SHADER_LOC, FRAGMENT_SHADER_LOC);

        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
        SDL_Delay(1000 / 60);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}