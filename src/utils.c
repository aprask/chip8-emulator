#include "utils.h"
void chip8_rand_num_init() {
    srand(time(NULL));
}
uint8_t chip8_get_rand_byte() {
    return rand() % 256;
}
