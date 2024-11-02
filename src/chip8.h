#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "chip8_cpu.h"

#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

typedef struct {
    uint8_t registers[16];
    uint8_t memory[4096];
    uint16_t index;
    uint16_t pc;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
    uint32_t video[VIDEO_WIDTH * VIDEO_HEIGHT];
    uint16_t opcode;
} chip8;

void chip8_init(chip8 *chip);
void chip8_cycle(chip8* chip8_t);

#endif
