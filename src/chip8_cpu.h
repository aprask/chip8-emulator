#include "utils.h"
#include <string.h>
#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

void chip8_OP_00E0();
void chip8_OP_00EE();
void chip8_OP_1nnn();
void chip8_OP_2nnn();
void chip8_OP_3xkk();
void chip8_OP_4xkk();
void chip8_OP_5xy0();
void chip8_OP_6xkk();
void chip8_OP_7xkk();
void chip8_OP_8xy0();
void chip8_OP_8xy1();
void chip8_OP_8xy2();
void chip8_OP_8xy3();
void chip8_OP_8xy4();
void chip8_OP_8xy5();
void chip8_OP_8xy6();
void chip8_OP_8xy7();
void chip8_OP_8xyE();
void chip8_OP_9xy0();
void chip8_OP_Annn();
void chip8_OP_Bnnn();
void chip8_OP_Cxkk();
void chip8_OP_Dxyn();
void chip8_OP_Ex9E();
void chip8_OP_ExA1();
void chip8_OP_Fx07();
void chip8_OP_Fx0A();
void chip8_OP_Fx15();
void chip8_OP_Fx18();
void chip8_OP_Fx1E();
void chip8_OP_Fx29();
void chip8_OP_Fx33();
void chip8_OP_Fx55();
void chip8_OP_Fx65();
#endif
