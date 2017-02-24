#include "matrix.h"
#include "matrix_defs.h"
#include "myfont.h"

#include <stdio.h>
#include <string.h>

unsigned char rmatrix [MATRIX_ROWS * MATRIX_COLOMS * MATRIX_BLOCK_SIZE * MATRIX_COUNT];
unsigned char rshift[MATRIX_ROWS];
unsigned char rshifted_sim[MATRIX_ROWS];
//============================================================================================
unsigned char * matrix_get_matrix(){
  return rmatrix;
}
//============================================================================================
char matrix_get_shift(char row){
  return rshift[row];
}
//============================================================================================
void matrix_clear(){
  for (char i = 0; i < MATRIX_ROWS * MATRIX_COLOMS * MATRIX_COUNT; i++){
    memcpy(&rmatrix[i * MATRIX_BLOCK_SIZE], &myfont8x8[0][0], MATRIX_BLOCK_SIZE);    
  }

  for (char i = 0; i < MATRIX_ROWS; i++){
    rshift[i] = 0; 
    rshifted_sim[i] = 0; 
  }
}
//============================================================================================
void matrix_set_text (char row, char * text, char len){
  if (len > MATRIX_COLOMS * MATRIX_COUNT)
    len = MATRIX_COLOMS * MATRIX_COUNT;

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;

  char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT;
  
  for (char i = 0; i < len; i++){
    memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &myfont8x8[text[i] - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE);     
  }
}
//============================================================================================
void matrix_append_char(char row, char sim){

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;  

  char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT;
  for (char i = 0; i < MATRIX_COLOMS * MATRIX_COUNT - 1; i++){
    memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &rmatrix[(row_start_index + i + 1) * MATRIX_BLOCK_SIZE], MATRIX_BLOCK_SIZE);  
  }
  
  row_start_index = row_start_index + MATRIX_COLOMS * MATRIX_COUNT - 1;
  memcpy(&rmatrix[row_start_index * MATRIX_BLOCK_SIZE], &myfont8x8[sim - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE);  
}
//============================================================================================
void matrix_rotate_fonts(){
  unsigned char rotated[8];

  for (unsigned char i = 0; i < FONT_COUNT; i++){
    
    memset(rotated, 0, 8);

    for (char bc = 0; bc < 8; bc++){
      for (char bits = 0; bits < 8; bits++){
        rotated[bc] |= ((myfont8x8[i][bits] >> bc) & 1) << bits;        
      }
    }
    memcpy(&myfont8x8[i][0], rotated, 8);  
  }
}
//============================================================================================
char matrix_shift_cycle_left(char row, unsigned char sim = 0){

  if (!rshift[row]){
    rshifted_sim[row] = sim;  
  }
  
  char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE;

  char buf = rmatrix[row_start_index];

  char i;
  for (i = 0; i < MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE - 1; i++){
    rmatrix[row_start_index + i] = rmatrix[row_start_index + i + 1] ;
  }

  if (rshifted_sim[row]){
    rmatrix[row_start_index + i] = myfont8x8[rshifted_sim[row] - MYFONT8X8SHIFT][rshift[row]];   
  }else{
    rmatrix[row_start_index + i] = buf;
  }
    
  if (rshift[row] == 7){
    rshifted_sim[row] = 0;
  }
  
  rshift[row]++;
  rshift[row] &= 7;
  
  return rshift[row];
}
//============================================================================================

