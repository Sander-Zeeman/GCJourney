#ifndef SHADER_TRANSLATOR_H
#define SHADER_TRANSLATOR_H

#include <GL/glew.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void checkShaderModification(const char *vert_path, const char *frag_path);
void prepareShader(const char *vertexFile, const char *fragmentFile);

#endif //SHADER_TRANSLATOR_H
