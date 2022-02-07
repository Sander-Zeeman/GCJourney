#ifndef SHADER_TRANSLATOR_H
#define SHADER_TRANSLATOR_H

#include <stdint.h>

char const *readShaderFromFile(const char *path);
void prepareShader(const char *vertexFile, const char *fragmentFile);

#endif //SHADER_TRANSLATOR_H
