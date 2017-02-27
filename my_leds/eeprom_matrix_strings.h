// #include "eeprom_matrix_strings.h"
#ifndef MY_EEPROM_MATRIX_STRINGS_H
#define MY_EEPROM_MATRIX_STRINGS_H

#include "MatrixString.h"

#define EEPROM_START_ADDR 100
#define EEPROM_STR_MAX_COUNT 6
#define EEPROM_STR_MAX_LEN MATRIX_STRING_MAX_LEN
#define EEPROM_STR_LEN_POS 0
#define EEPROM_STR_COLOR_POS 1
#define EEPROM_STR_UTIL_DATA_LEN 2 // len of string and color


char eeprom_str_set(MatrixString * mstr, char number);
char eeprom_str_get(MatrixString * mstr, char number);


#endif