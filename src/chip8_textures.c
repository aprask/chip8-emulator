#include "chip8_textures.h"
#include <stdio.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

void sdl_init(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

void sdl_destroyer() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdl_update(const void* buffer, int pitch) {
    SDL_UpdateTexture(texture, NULL, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool process_input(chip8* chip8_t) {
    SDL_Event event;
    bool quit = false;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                printf("SDL_QUIT event detected.\n");
                quit = true;
                break;

            case SDL_KEYDOWN:
                printf("Key Down: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: 
                        quit = true; 
                        printf("ESC key pressed. Exiting...\n"); 
                        break;
                    case SDLK_x: 
                        chip8_t->keypad[0] = 1; 
                        printf("Keypad[0] set to 1 (x key)\n"); 
                        break;
                    case SDLK_1: 
                        chip8_t->keypad[1] = 1; 
                        printf("Keypad[1] set to 1 (1 key)\n"); 
                        break;
                    case SDLK_2: 
                        chip8_t->keypad[2] = 1; 
                        printf("Keypad[2] set to 1 (2 key)\n"); 
                        break;
                    case SDLK_3: 
                        chip8_t->keypad[3] = 1; 
                        printf("Keypad[3] set to 1 (3 key)\n"); 
                        break;
                    case SDLK_q: 
                        chip8_t->keypad[4] = 1; 
                        printf("Keypad[4] set to 1 (q key)\n"); 
                        break;
                    case SDLK_w: 
                        chip8_t->keypad[5] = 1; 
                        printf("Keypad[5] set to 1 (w key)\n"); 
                        break;
                    case SDLK_e: 
                        chip8_t->keypad[6] = 1; 
                        printf("Keypad[6] set to 1 (e key)\n"); 
                        break;
                    case SDLK_a: 
                        chip8_t->keypad[7] = 1; 
                        printf("Keypad[7] set to 1 (a key)\n"); 
                        break;
                    case SDLK_s: 
                        chip8_t->keypad[8] = 1; 
                        printf("Keypad[8] set to 1 (s key)\n"); 
                        break;
                    case SDLK_d: 
                        chip8_t->keypad[9] = 1; 
                        printf("Keypad[9] set to 1 (d key)\n"); 
                        break;
                    case SDLK_z: 
                        chip8_t->keypad[0xA] = 1; 
                        printf("Keypad[0xA] set to 1 (z key)\n"); 
                        break;
                    case SDLK_c: 
                        chip8_t->keypad[0xB] = 1; 
                        printf("Keypad[0xB] set to 1 (c key)\n"); 
                        break;
                    case SDLK_4: 
                        chip8_t->keypad[0xC] = 1; 
                        printf("Keypad[0xC] set to 1 (4 key)\n"); 
                        break;
                    case SDLK_r: 
                        chip8_t->keypad[0xD] = 1; 
                        printf("Keypad[0xD] set to 1 (r key)\n"); 
                        break;
                    case SDLK_f: 
                        chip8_t->keypad[0xE] = 1; 
                        printf("Keypad[0xE] set to 1 (f key)\n"); 
                        break;
                    case SDLK_v: 
                        chip8_t->keypad[0xF] = 1; 
                        printf("Keypad[0xF] set to 1 (v key)\n"); 
                        break;
                }
                break;

            case SDL_KEYUP:
                printf("Key Up: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                switch (event.key.keysym.sym) {
                    case SDLK_x: 
                        chip8_t->keypad[0] = 0; 
                        printf("Keypad[0] reset to 0 (x key)\n"); 
                        break;
                    case SDLK_1: 
                        chip8_t->keypad[1] = 0; 
                        printf("Keypad[1] reset to 0 (1 key)\n"); 
                        break;
                    case SDLK_2: 
                        chip8_t->keypad[2] = 0; 
                        printf("Keypad[2] reset to 0 (2 key)\n"); 
                        break;
                    case SDLK_3: 
                        chip8_t->keypad[3] = 0; 
                        printf("Keypad[3] reset to 0 (3 key)\n"); 
                        break;
                    case SDLK_q: 
                        chip8_t->keypad[4] = 0; 
                        printf("Keypad[4] reset to 0 (q key)\n"); 
                        break;
                    case SDLK_w: 
                        chip8_t->keypad[5] = 0; 
                        printf("Keypad[5] reset to 0 (w key)\n"); 
                        break;
                    case SDLK_e: 
                        chip8_t->keypad[6] = 0; 
                        printf("Keypad[6] reset to 0 (e key)\n"); 
                        break;
                    case SDLK_a: 
                        chip8_t->keypad[7] = 0; 
                        printf("Keypad[7] reset to 0 (a key)\n"); 
                        break;
                    case SDLK_s: 
                        chip8_t->keypad[8] = 0; 
                        printf("Keypad[8] reset to 0 (s key)\n"); 
                        break;
                    case SDLK_d: 
                        chip8_t->keypad[9] = 0; 
                        printf("Keypad[9] reset to 0 (d key)\n"); 
                        break;
                    case SDLK_z: 
                        chip8_t->keypad[0xA] = 0; 
                        printf("Keypad[0xA] reset to 0 (z key)\n"); 
                        break;
                    case SDLK_c: 
                        chip8_t->keypad[0xB] = 0; 
                        printf("Keypad[0xB] reset to 0 (c key)\n"); 
                        break;
                    case SDLK_4: 
                        chip8_t->keypad[0xC] = 0; 
                        printf("Keypad[0xC] reset to 0 (4 key)\n"); 
                        break;
                    case SDLK_r: 
                        chip8_t->keypad[0xD] = 0; 
                        printf("Keypad[0xD] reset to 0 (r key)\n"); 
                        break;
                    case SDLK_f: 
                        chip8_t->keypad[0xE] = 0; 
                        printf("Keypad[0xE] reset to 0 (f key)\n"); 
                        break;
                    case SDLK_v: 
                        chip8_t->keypad[0xF] = 0; 
                        printf("Keypad[0xF] reset to 0 (v key)\n"); 
                        break;
                }
                break;
        }
    }

    return quit;
}
