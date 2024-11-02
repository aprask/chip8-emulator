#include "chip8.h"
#include "chip8_cpu.h"
#include "chip8_graphics.h"
// CLS
void chip8_OP_00E0(chip8* chip8_t) {
    memset(chip8_t->video, 0, sizeof(chip8_t->video));
}
// RET
void chip8_OP_00EE(chip8* chip8_t) {
    chip8_t->sp--; // decrement stack pointer
    chip8_t->pc = chip8_t->stack[chip8_t->sp]; // put the pc at the prev instruction
}
// JP addr
void chip8_OP_1nnn(chip8* chip8_t) {
    const uint16_t address = chip8_t->opcode & 0x0FFFu; // extracting the 8 "nnn" bits
    chip8_t->pc = address;
}
// CALL addr
void chip8_OP_2nnn(chip8* chip8_t) {
    const uint16_t address = chip8_t->opcode & 0x0FFFu;
    chip8_t->stack[chip8_t->sp] = chip8_t->pc;
    chip8_t->sp++;
    chip8_t->pc = address;
}
// SE (skip if equal to immediate) Vx (skipping mechanism)
void chip8_OP_3xkk(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t byte = chip8_t->opcode & 0x00FFu;
    if (chip8_t->registers[Vx] == byte) {
        chip8_t->pc+=2; // skipping next instruction since Vx == byte
    }
}
// SNE (skip if not equal to immediate) Vx
void chip8_OP_4xkk(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t byte = chip8_t->opcode & 0x00FFu;
    if (chip8_t->registers[Vx] != byte) {
        chip8_t->pc+= 2;
    }
}
// SE (skip if equal to register) Vx & Vy
void chip8_OP_5xy0(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u; // first register
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u; // second register
    if (chip8_t->registers[Vx] == chip8_t->registers[Vy]) {
        chip8_t->pc+=2;
    }
}
// LW (load immediate word)
void chip8_OP_6xkk(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t byte = chip8_t->opcode & 0x00FFu;
    chip8_t->registers[Vx] = byte;
}
// ADDI (add immediate)
void chip8_OP_7xkk(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t byte = chip8_t->opcode & 0x00FFu;
    chip8_t->registers[Vx] += byte;
}
// LW (load register word)
void chip8_OP_8xy0(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    chip8_t->registers[Vx] = chip8_t->registers[Vy];
}
// OR (OR to overlap registers)
void chip8_OP_8xy1(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    chip8_t->registers[Vx] |= chip8_t->registers[Vy];
}
// AND
void chip8_OP_8xy2(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    chip8_t->registers[Vx] &= chip8_t->registers[Vy];
}
// XOR
void chip8_OP_8xy3(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    chip8_t->registers[Vx] ^= chip8_t->registers[Vy];
}
// ADD w/ overflow flag
void chip8_OP_8xy4(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    const uint16_t sum = chip8_t->registers[Vx] + chip8_t->registers[Vy];
    if (sum > 255u) {
        chip8_t->registers[0xF] = 1; // overflow
    } else {
        chip8_t->registers[0xF] = 0;
    }
    chip8_t->registers[Vx] = sum & 0xFFu;
}
// SUB
void chip8_OP_8xy5(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    if (chip8_t->registers[Vx] > chip8_t->registers[Vy]) {
        chip8_t->registers[0xF] = 1; // > 0
    } else {
         chip8_t->registers[0xF] = 0; // == 0 (cannot have negatives in unsigned)
    }
    chip8_t->registers[Vx] -= chip8_t->registers[Vy];
}
// SRI
void chip8_OP_8xy6(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->registers[0xF] = (chip8_t->registers[Vx] & 0x1u); // lsb to flag nibble
    chip8_t->registers[Vx] >>= 1;
}
// SUB (subtract registers where difference = Vy - Vx)
void chip8_OP_8xy7(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    if (chip8_t->registers[Vy] > chip8_t->registers[Vx]) {
        chip8_t->registers[0xF] = 1; // overflow
    } else {
        chip8_t->registers[0xF] = 0;
    }
    chip8_t->registers[Vx] = chip8_t->registers[Vy] - chip8_t->registers[Vx];
}
// SLI
void chip8_OP_8xye(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->registers[0xF] = (chip8_t->registers[Vx] & 0x80u) >> 7u;
    chip8_t->registers[Vx] <<= 1;
}
// SNE (skip if not equal to register)
void chip8_OP_9xy0(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    if (chip8_t->registers[Vx] != chip8_t->registers[Vy]) {
        chip8_t->pc += 2;
    }
}
// Store Address in Index
void chip8_OP_Annn(chip8* chip8_t) {
    const uint16_t address = chip8_t->opcode & 0x0FFFu; // last 12 bits (nnn)
    chip8_t->index = address;
}
// JP V0, addr (jump to a location V0 with an offset of nnn)
void chip8_OP_Bnnn(chip8* chip8_t) {
    const uint16_t offset_address = chip8_t->opcode & 0x0FFFu;
    // jump to location by setting the pc to the first register location + offset
    chip8_t->pc = chip8_t->registers[0] + offset_address; // base address + offset address
}
// RAND
void chip8_OP_Cxkk(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    // uint8_t byte = chip8_t->opcode & 0x00FFu;
    chip8_t->registers[Vx] = chip8_get_rand_byte();
}
// Display sprite at location (vx, vy)
void chip8_OP_Dxyn(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t Vy = (chip8_t->opcode & 0x00F0u) >> 4u;
    const uint8_t height = chip8_t->opcode & 0x000Fu;
    const uint8_t x = chip8_t->registers[Vx] % VIDEO_WIDTH;
    const uint8_t y = chip8_t->registers[Vy] % VIDEO_HEIGHT;
    chip8_t->registers[0xF] = 0;
    for (unsigned int row = 0; row < height; row++) {
        const uint8_t spriteByte = chip8_t->memory[chip8_t->index + row];
        // 8 cols because each sprite is 8 pixels	
	for (unsigned int col = 0; col < 8; col++) {
	    /// checking to see if the pixel is on or off at said pos
        const uint8_t spritePixel = spriteByte & (0x80u >> col); //col bit
        const unsigned int row_sum = y+row;
        const unsigned int col_sum = x+col;
	    uint32_t* screenPixel = &chip8_t->video[row_sum * VIDEO_WIDTH + col_sum];
	    if (spritePixel) {
	       if (*screenPixel == 0xFFFFFFFF) {
	           chip8_t->registers[0xF] = 1; // collision
	       }
	       *screenPixel ^= 0xFFFFFFFF;
	    }
	}
    }
}
// SKP Vx (if key is pressed)
void chip8_OP_Ex9e(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t key = chip8_t->registers[Vx];
    if (chip8_t->keypad[key]){
        chip8_t->pc+=2;
    }
}
// SKNP Vx (skip if key is not pressed)
void chip8_OP_ExA1(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t key = chip8_t->registers[Vx];
    if (!chip8_t->keypad[key]) {
        chip8_t->pc+=2;
    }
}
// Set Vx to delay timer
void chip8_OP_Fx07(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->registers[Vx] = chip8_t->delay_timer;
}
// Store the value of the key in Vx
void chip8_OP_Fx0A(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    unsigned int key_pressed = 0;
    for (unsigned int i = 0; i <= 15; i++) {
	if (chip8_t->keypad[i]) {
	    chip8_t->registers[Vx] = i;
	    key_pressed = 1;
	    break;
	    }
    }
    if (!key_pressed) {
        chip8_t->pc-=2;
    }
}
// set the delay timer to Vx
void chip8_OP_Fx15(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->delay_timer = chip8_t->registers[Vx];
}
// set the sound timer to Vx
void chip8_OP_Fx18(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->sound_timer = chip8_t->registers[Vx];
}
// add index (index = index + Vx)
void chip8_OP_Fx1E(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    chip8_t->index += chip8_t->registers[Vx]; // for offsetting
}
// set index to the base address of the Sprite
void chip8_OP_Fx29(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    // digit variable refers to a specific character in the font table
    const uint8_t digit = chip8_t->registers[Vx];
    chip8_t->index = FONTSET_START_ADDRESS + (5 * digit); // font chars are 5 bytes wide
}
// store bcd in memory in locations i, i+1, i+2
void chip8_OP_Fx33(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    const uint8_t value = chip8_t->registers[Vx];
    if (value > 999) {
        chip8_t->memory[chip8_t->index+2] = 9;
	    chip8_t->memory[chip8_t->index+1] = 9;
	    chip8_t->memory[chip8_t->index] = 9;
    } else {
        chip8_t->memory[chip8_t->index+2] = value % 10;
        chip8_t->memory[chip8_t->index+1] = value % 10;
        chip8_t->memory[chip8_t->index] = value % 10;
    }
}
// store registers v0 to vx in memory starting at index i
void chip8_OP_Fx55(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    for (unsigned int i = 0; i <= Vx; i++) {
        chip8_t->memory[chip8_t->index+i] = chip8_t->registers[i];
    }
}
// read from registers starting at i
void chip8_OP_Fx65(chip8* chip8_t) {
    const uint8_t Vx = (chip8_t->opcode & 0x0F00u) >> 8u;
    for (unsigned int i = 0; i <= Vx; i++) {
        chip8_t->registers[i] = chip8_t->memory[chip8_t->index+i];
    }
}
void chip8_OP_NULL() {}
