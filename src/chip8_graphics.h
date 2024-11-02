#ifndef CHIP8_GRAPHICS_H
#define CHIP8_GRAPHICS_H
#include "chip8.h"
#include <stdint.h>
#include <stdio.h>
#define FONTSET_SIZE 80
#define FONTSET_START_ADDRESS 0x50
extern uint8_t fontset[FONTSET_SIZE];
void chip8_font_init();
#endif
