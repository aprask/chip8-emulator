#include "chip8.h"
void chip_Execute(chip8* chip8_t) {
    switch (chip8_t->opcode & 0xF000u) {
	        case 0x0000:
		    switch (chip8_t->opcode & 0x00FFu) {
		        case 0x00E0: chip8_OP_00E0(chip8_t); break;
			case 0x00EE: chip8_OP_00EE(chip8_t); break;
			default: chip8_OP_NULL(); break;
		    }
		    break;
		case 0x1000: chip8_OP_1nnn(chip8_t); break;
		case 0x2000: chip8_OP_2nnn(chip8_t); break;
		case 0x3000: chip8_OP_3xkk(chip8_t); break;
		case 0x4000: chip8_OP_4xkk(chip8_t); break;
	        case 0x5000: chip8_OP_5xy0(chip8_t); break;
		case 0x6000: chip8_OP_6xkk(chip8_t); break;
		case 0x7000: chip8_OP_7xkk(chip8_t); break;
		case 0x8000:
		    switch (chip8_t->opcode & 0x000Fu) {
		        case 0x0001: chip8_OP_8xy1(chip8_t); break;
			case 0x0002: chip8_OP_8xy2(chip8_t); break;
			case 0x0003: chip8_OP_8xy3(chip8_t); break;
			case 0x0004: chip8_OP_8xy4(chip8_t); break;
			case 0x0005: chip8_OP_8xy5(chip8_t); break;
			case 0x0006: chip8_OP_8xy6(chip8_t); break;
			case 0x0007: chip8_OP_8xy7(chip8_t); break;
			case 0x000E: chip8_OP_8xye(chip8_t); break;
			default: chip8_OP_NULL(); break;
		    }
		case 0x9000: chip8_OP_9xy0(chip8_t); break;
    	case 0xA000: chip8_OP_Annn(chip8_t); break;
    	case 0xB000: chip8_OP_Bnnn(chip8_t); break;
    	case 0xC000: chip8_OP_Cxkk(chip8_t); break;
    	case 0xD000: chip8_OP_Dxyn(chip8_t); break;
    	case 0xE000:
    		switch (chip8_t->opcode & 0x000Fu) {
    			case 0x000E: chip8_OP_Ex9e(chip8_t); break;
    			case 0x0001: chip8_OP_ExA1(chip8_t); break;
    			default: chip8_OP_NULL(); break;
    		}
    	case 0xF000:
    		switch (chip8_t->opcode & 0x00FFu) {
    			case 0x0007: chip8_OP_Fx07(chip8_t); break;
    			case 0x000A: chip8_OP_Fx0A(chip8_t); break;
    			case 0x0015: chip8_OP_Fx15(chip8_t); break;
    			case 0x0018: chip8_OP_Fx18(chip8_t); break;
    			case 0x001E: chip8_OP_Fx1E(chip8_t); break;
    			case 0x0029: chip8_OP_Fx29(chip8_t); break;
    			case 0x0033: chip8_OP_Fx33(chip8_t); break;
    			case 0x0055: chip8_OP_Fx55(chip8_t); break;
    			case 0x0065: chip8_OP_Fx65(chip8_t); break;
			    default: chip8_OP_NULL(); break;
    		}

	    default: chip8_OP_NULL(); break;
	}
}
void chip8_cycle(chip8* chip8_t) {
                     // high-byte = type of instruction (label)   low-byte = which registers/immediates (parameters)
    chip8_t->opcode = (chip8_t->memory[chip8_t->pc] << 8u) | chip8_t->memory[chip8_t->pc+1];
    chip8_t->pc+=2; // since pc+1 points to the parameters, we must go to the "next" label
    chip_Execute(chip8_t); // decode and execute
    if (chip8_t->delay_timer > 0) {
        chip8_t->delay_timer--;
    }
    if (chip8_t->sound_timer > 0) {
        chip8_t->sound_timer--;
    }
}
