#include "../include/read_bytes.hpp"

// Lê um byte do arquivo
uint8_t read_byte(FILE *fp) {
      uint8_t byte = 0;

      fread(&byte, sizeof(uint8_t), 1, fp);

      return byte;
}

uint16_t read_word(FILE *fp) {
      uint16_t twoBytes = 0;

      fread(&twoBytes, sizeof(uint8_t), 2, fp);
      twoBytes = little_to_big16(twoBytes);

      return twoBytes;
}

uint32_t read_dword(FILE *fp) {
      uint32_t fourBytes = 0;

      fread(&fourBytes, sizeof(uint8_t), 4, fp);
      fourBytes = little_to_big32(fourBytes);

      return fourBytes;
}
