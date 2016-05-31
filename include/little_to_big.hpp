#ifndef _LITTLE_TO_BIG
#define _LITTLE_TO_BIG

#include <stdint.h>

// Passa uma word de little endian para big endian
uint16_t little_to_big16(uint16_t x);

// Passa uma dword de little endian para big endian
uint32_t little_to_big32(uint32_t x);

#endif // _LITTLE_TO_BIG
