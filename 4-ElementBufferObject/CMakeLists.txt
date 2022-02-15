cmake_minimum_required(VERSION 3.16)
project(3-RealTimeShaderUpdate C)

set(CMAKE_C_STANDARD 11)
set(NAME Triangle)

add_executable(${NAME} main.c event_handler.c window_manager.c shader_translator.c)

set(LIBS GLEW GL SDL2)

target_include_directories(${NAME} PUBLIC include)
target_link_libraries(${NAME} ${LIBS})
