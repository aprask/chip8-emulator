#include "chip8_memory.h"

const unsigned int PC_START_ADDRESS = 0x200;

int chip8_load_rom_file(chip8* chip8_t, const char* file) {
    if (file == NULL) {
        printf("Cannot load ROM file\n");
        return -1;
    }

    long file_sz;
    FILE* parsed_file = fopen(file, "rb");
    if (parsed_file == NULL) {
        printf("Could not open file %s\n", file);
        return -1;
    }

    fseek(parsed_file, 0, SEEK_END);
    file_sz = ftell(parsed_file);
    fseek(parsed_file, 0, SEEK_SET);

    char* buffer = malloc(file_sz);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(parsed_file);
        return -1;
    }

    fread(buffer, sizeof(char), file_sz, parsed_file);
    fclose(parsed_file);

    for (uint64_t i = 0; i < file_sz; i++) {
        chip8_t->memory[PC_START_ADDRESS + i] = buffer[i];
    }

    free(buffer);
    return 0;
}

void chip8_pc_init(chip8* chip8_t) {
    chip8_t->pc = PC_START_ADDRESS;
}
