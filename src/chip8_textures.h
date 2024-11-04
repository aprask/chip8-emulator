#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "chip8.h"
void sdl_init(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
void sdl_destroyer();
void sdl_update(void const* buffer, int pitch);
bool process_input(chip8* chip8_t);