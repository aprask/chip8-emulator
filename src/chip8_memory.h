#ifndef CHIP8_MEMORY_H
#define CHIP8_MEMORY_H
#include "chip8.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
int chip8_load_rom_file(chip8* chip8_t, const char* file);
#endif
