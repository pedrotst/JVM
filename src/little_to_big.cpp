#include "../include/little_to_big.hpp"

uint16_t little_to_big16(uint16_t x) {
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);

    return x;
}

uint32_t little_to_big32(uint32_t x) {
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
    x = ((x & 0xFFFF0000) >> 16) | ((x & 0x0000FFFF) << 16);

    return x;
}
