#include "shader_translator.h"

#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>

const char *readShaderFromFile(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open %s\n", path);
        perror("fopen");
        exit(1);
    }

    uint32_t cap = 1024;
    char *shader = malloc(cap);
    uint32_t size = 0;

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp))
    {
        for (uint32_t i = 0; buffer[i] != '\0' && i < 1024; i++)
        {
            if ((size + 1) == cap)
            {
                cap <<= 1;
                shader = realloc(shader, cap);
            }

            shader[size++] = buffer[i];
        }
    }
    fclose(fp);

    shader[size++] = '\0';
    return realloc(shader, size);
}

void checkCompileSuccess(uint32_t shader)
{
    int success;
    char info[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, info);
        fprintf(stderr, "Shader failed to compile:\n%s\n", info);
        exit(1);
    }
}

void checkLinkSuccess(uint32_t program)
{
    int success;
    char info[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, info);
        fprintf(stderr, "Program failed to link:\n%s\n", info);
        exit(1);
    }
}

void prepareShader(const char *vertexFile, const char *fragmentFile)
{
    const char *vertex = readShaderFromFile(vertexFile);
    const char *fragment = readShaderFromFile(fragmentFile);

    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, NULL);
    glCompileShader(vertexShader);
    checkCompileSuccess(vertexShader);

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, NULL);
    glCompileShader(fragmentShader);
    checkCompileSuccess(fragmentShader);

    uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    checkLinkSuccess(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    free((char*) vertex);
    free((char*) fragment);
}
