#ifndef _READ_BYTES
#define _READ_BYTES

#include <stdio.h>
#include "../include/little_to_big.hpp"

/** \fn read_byte
* \brief Lê um byte do arquivo
*/
uint8_t read_byte(FILE *fp);


/** \fn read_word
* \brief Lê dois bytes do arquivo
*/
uint16_t read_word(FILE *fp);

/** \fn read_dword
* \brief Le tres bytes do arquivo
*/
uint32_t read_dword(FILE *fp);

#endif // _READ_BYTES
