#include "eeprom_matrix_strings.h"
#include <EEPROM.h>
//============================================================================================
char eeprom_str_set(MatrixString * mstr, char number){
  if(number >= EEPROM_STR_MAX_COUNT)
    return -1;
	
  unsigned int eeprom_str_start_pos  = 
    (EEPROM_START_ADDR + ((EEPROM_STR_MAX_LEN + EEPROM_STR_UTIL_DATA_LEN) * number)); 

  EEPROM.write(eeprom_str_start_pos + EEPROM_STR_LEN_POS, mstr->len);
  EEPROM.write(eeprom_str_start_pos + EEPROM_STR_COLOR_POS, mstr->color);
  
  eeprom_str_start_pos += EEPROM_STR_UTIL_DATA_LEN;
  
  for (unsigned char i = 0; i < mstr->len; i++){
    EEPROM.write(eeprom_str_start_pos + i, mstr->str[i]);
  }   
}
//============================================================================================
char eeprom_str_get(MatrixString * mstr, char number){
  if(number >= EEPROM_STR_MAX_COUNT)
    return -1;
	
  unsigned int eeprom_str_start_pos  = 
    (EEPROM_START_ADDR + ((EEPROM_STR_MAX_LEN + EEPROM_STR_UTIL_DATA_LEN) * number));
	
  mstr->len = EEPROM.read(eeprom_str_start_pos + EEPROM_STR_LEN_POS);
  mstr->color = EEPROM.read(eeprom_str_start_pos + EEPROM_STR_COLOR_POS);

  eeprom_str_start_pos += EEPROM_STR_UTIL_DATA_LEN;
  
  for (unsigned char i = 0; i < mstr->len; i++){
    mstr->str[i] = EEPROM.read(eeprom_str_start_pos + i);
  }
}
//================================================================================================
