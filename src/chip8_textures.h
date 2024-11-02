#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
void sdl_init(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
void sdl_destroyer();
void sdl_update(void const* buffer, int pitch);
bool process_input(uint8_t* keys);