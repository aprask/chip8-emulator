cmake_minimum_required(VERSION 3.25.1)
project(chip8_emulator_project C)
set(CMAKE_C_STANDARD 23)
find_package(SDL2 REQUIRED)
add_executable(chip8_emulator_project
        src/chip8.c
        src/chip8_memory.c
        src/main.c
        src/chip8_graphics.c
        src/utils.c
        src/chip8_cpu.c
        src/chip8_textures.c
)
target_link_libraries(chip8_emulator_project SDL2::SDL2)
