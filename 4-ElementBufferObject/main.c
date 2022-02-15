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

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Vec3 vertices[9] = {
        { .x =-0.5f, .y = 0.5f, .z =0.0f },
        { .x = 0.0f, .y = 0.5f, .z =0.0f },
        { .x = 0.5f, .y = 0.5f, .z =0.0f },
        { .x =-0.5f, .y = 0.0f, .z =0.0f },
        { .x = 0.0f, .y = 0.0f, .z =0.0f },
        { .x = 0.5f, .y = 0.0f, .z =0.0f },
        { .x =-0.5f, .y =-0.5f, .z =0.0f },
        { .x = 0.0f, .y =-0.5f, .z =0.0f },
        { .x = 0.5f, .y =-0.5f, .z =0.0f },
    };

    uint8_t indices[24] = {
        0, 1, 4,
        4, 3, 0,
        1, 2, 5,
        5, 4, 1,
        3, 4, 7,
        7, 6, 3,
        4, 5, 8,
        8, 7, 4
    };

    uint32_t vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    prepareShader(VERTEX_SHADER_LOC, FRAGMENT_SHADER_LOC);

    bool quit = false;
    while (!quit) {
        handle_events(&quit);

        checkShaderModification(VERTEX_SHADER_LOC, FRAGMENT_SHADER_LOC);

        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_BYTE, 0);

        SDL_GL_SwapWindow(window);
        SDL_Delay(1000 / 60);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}