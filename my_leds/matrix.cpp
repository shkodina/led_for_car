#include "matrix.h"
#include "matrix_defs.h"
#include "myfont.h"

#include <stdio.h>
#include <string.h>

unsigned char rmatrix [MATRIX_ROWS * MATRIX_COLOMS * MATRIX_BLOCK_SIZE];

unsigned char * matrix_get_matrix(){
  return rmatrix;
}

void matrix_clear(){
  for (char i = 0; i < MATRIX_ROWS * MATRIX_COLOMS; i++){
    memcpy(&rmatrix[i * MATRIX_BLOCK_SIZE], &myfont8x8[0][0], MATRIX_BLOCK_SIZE);    
  }
}

void matrix_set_text (char row, char * text, char len){
  if (len > MATRIX_COLOMS)
    len = MATRIX_COLOMS;

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;

  char row_start_index = row * MATRIX_COLOMS;
  
  for (char i = 0; i < len; i++){
    memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &myfont8x8[text[i] - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE);     
  }
}

void matrix_append_char(char row, char sim){

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;  

  char row_start_index = row * MATRIX_COLOMS;
  for (char i = 0; i < MATRIX_COLOMS - 1; i++){
    memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &rmatrix[(row_start_index + i + 1) * MATRIX_BLOCK_SIZE], MATRIX_BLOCK_SIZE);  
  }
  row_start_index = row_start_index + MATRIX_COLOMS - 1;
  memcpy(&rmatrix[row_start_index * MATRIX_BLOCK_SIZE], &myfont8x8[sim - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE);  
}

