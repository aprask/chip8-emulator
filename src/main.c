#include <stdio.h>
#include "chip8.h"
#include "chip8_textures.h"
#include "chip8_memory.h"
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Invalid number of arguments\n");
        return -1;
    }
    int video_scale = atoi(argv[1]);
    int cycle_delay = atoi(argv[2]);
    const char* rom = argv[3];
    chip8* chip8_inst = (chip8*)malloc(sizeof(chip8));
    if (chip8_inst == NULL) {
        printf("Failed to allocate memory of chip8 instance\n");
        return -1;
    }
    sdl_init(
        "CHIP-8", 
        VIDEO_HEIGHT * video_scale,
        VIDEO_WIDTH * video_scale,
        VIDEO_WIDTH,
        VIDEO_HEIGHT
    );
    int loaded_rom = chip8_load_rom_file(chip8_inst, rom);
    if (!loaded_rom) {
        printf("Loaded rom\n");
    } else {
        printf("Failed to load rom\n");
        return -1;
    }
    int video_pitch = sizeof(chip8_inst->video[0]) * VIDEO_WIDTH;
    struct timeval last_cycle_time;
    gettimeofday(&last_cycle_time, NULL);
    bool quit = false;
    while (!quit) {
        quit = process_input(chip8_inst->keypad);
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        float dt = (current_time.tv_sec - last_cycle_time.tv_sec) * 1000.0f + 
               (current_time.tv_usec - last_cycle_time.tv_usec) / 1000.0f;
        if (dt > cycle_delay) {
            last_cycle_time = current_time;
            chip8_cycle(chip8_inst);
            sdl_update(chip8_inst->video, video_pitch);
        }
    }
    free(chip8_inst);
    chip8_inst = NULL;
    return 0;
}

