#include "chip8_textures.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;

void sdl_init(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
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

void sdl_update(void const* buffer, int pitch) {
    // pitch: distance between the centers of two adjacent pixels on a display screen
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
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_x: chip8_t->keypad[0] = 1; break;
                    case SDLK_1: chip8_t->keypad[1] = 1; break;
                    case SDLK_2: chip8_t->keypad[2] = 1; break;
                    case SDLK_3: chip8_t->keypad[3] = 1; break;
                    case SDLK_q: chip8_t->keypad[4] = 1; break;
                    case SDLK_w: chip8_t->keypad[5] = 1; break;
                    case SDLK_e: chip8_t->keypad[6] = 1; break;
                    case SDLK_a: chip8_t->keypad[7] = 1; break;
                    case SDLK_s: chip8_t->keypad[8] = 1; break;
                    case SDLK_d: chip8_t->keypad[9] = 1; break;
                    case SDLK_z: chip8_t->keypad[0xA] = 1; break;
                    case SDLK_c: chip8_t->keypad[0xB] = 1; break;
                    case SDLK_4: chip8_t->keypad[0xC] = 1; break;
                    case SDLK_r: chip8_t->keypad[0xD] = 1; break;
                    case SDLK_f: chip8_t->keypad[0xE] = 1; break;
                    case SDLK_v: chip8_t->keypad[0xF] = 1; break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x: chip8_t->keypad[0] = 0; break;
                    case SDLK_1: chip8_t->keypad[1] = 0; break;
                    case SDLK_2: chip8_t->keypad[2] = 0; break;
                    case SDLK_3: chip8_t->keypad[3] = 0; break;
                    case SDLK_q: chip8_t->keypad[4] = 0; break;
                    case SDLK_w: chip8_t->keypad[5] = 0; break;
                    case SDLK_e: chip8_t->keypad[6] = 0; break;
                    case SDLK_a: chip8_t->keypad[7] = 0; break;
                    case SDLK_s: chip8_t->keypad[8] = 0; break;
                    case SDLK_d: chip8_t->keypad[9] = 0; break;
                    case SDLK_z: chip8_t->keypad[0xA] = 0; break;
                    case SDLK_c: chip8_t->keypad[0xB] = 0; break;
                    case SDLK_4: chip8_t->keypad[0xC] = 0; break;
                    case SDLK_r: chip8_t->keypad[0xD] = 0; break;
                    case SDLK_f: chip8_t->keypad[0xE] = 0; break;
                    case SDLK_v: chip8_t->keypad[0xF] = 0; break;
                }
                break;
        }
    }

    return quit;
}
