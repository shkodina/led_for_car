#include "matrix.h"
#include "matrix_defs.h"
//#include "myfont.h"
#include "fonts/myfont_cyrilic.h"

#include <stdio.h>
#include <string.h>

unsigned char rmatrix [MATRIX_ROWS * MATRIX_COLOMS * MATRIX_BLOCK_SIZE * MATRIX_COUNT];
unsigned char rshift[MATRIX_ROWS];
unsigned char rshifted_sim[MATRIX_ROWS];
//============================================================================================
bool is_maxi_mode = false;
void matrix_set_maxi_font_mode(bool mode_set){
  is_maxi_mode = mode_set;
}
bool matrix_get_maxi_font_mode(){
  return is_maxi_mode;
}
char maxi_char_cur_part[2] = {0,0}; // row count = 2;
unsigned char maxichar[4][8];
void dubnshift(unsigned char v, unsigned char &r, unsigned char &l){
	l = r = 0;
	if (v & 0b10000000) l|=0b11000000;
	if (v & 0b01000000) l|=0b00110000;
	if (v & 0b00100000) l|=0b00001100;
	if (v & 0b00010000) l|=0b00000011;
	if (v & 0b00001000) r|=0b11000000;
	if (v & 0b00000100) r|=0b00110000;
	if (v & 0b00000010) r|=0b00001100;
	if (v & 0b00000001) r|=0b00000011;
}
void fillmaxichar(unsigned char sim){
	unsigned char ll, rr;

	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][0], ll, rr);
	maxichar[0][0] = maxichar[0][1] = ll;
	maxichar[2][0] = maxichar[2][1] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][1], ll, rr);
	maxichar[0][2] = maxichar[0][3] = ll;
	maxichar[2][2] = maxichar[2][3] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][2], ll, rr);
	maxichar[0][4] = maxichar[0][5] = ll;
	maxichar[2][4] = maxichar[2][5] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][3], ll, rr);
	maxichar[0][6] = maxichar[0][7] = ll;
	maxichar[2][6] = maxichar[2][7] = rr;
	
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][4], ll, rr);
	maxichar[1][0] = maxichar[1][1] = ll;
	maxichar[3][0] = maxichar[3][1] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][5], ll, rr);
	maxichar[1][2] = maxichar[1][3] = ll;
	maxichar[3][2] = maxichar[3][3] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][6], ll, rr);
	maxichar[1][4] = maxichar[1][5] = ll;
	maxichar[3][4] = maxichar[3][5] = rr;
	dubnshift(myfont8x8[sim - MYFONT8X8SHIFT][7], ll, rr);
	maxichar[1][6] = maxichar[1][7] = ll;
	maxichar[3][6] = maxichar[3][7] = rr;
	
}
//============================================================================================
unsigned char * matrix_get_matrix(){
  return rmatrix;
}
//============================================================================================
unsigned char matrix_get_shift(unsigned char row){
  return rshift[row];
}
//============================================================================================
void matrix_clear(){
  for (unsigned char i = 0; i < MATRIX_ROWS * MATRIX_COLOMS * MATRIX_COUNT; i++){
    memcpy(&rmatrix[i * MATRIX_BLOCK_SIZE], &myfont8x8[0][0], MATRIX_BLOCK_SIZE);    
  }

  for (unsigned char i = 0; i < MATRIX_ROWS; i++){
    rshift[i] = 0; 
    rshifted_sim[i] = 0; 
  }
}
//============================================================================================
void matrix_clear_row(unsigned char row){
  unsigned char start_i = row * MATRIX_COLOMS * MATRIX_COUNT;
  for (unsigned char i = 0; i < MATRIX_COLOMS * MATRIX_COUNT; i++){
    memcpy(&rmatrix[(start_i + i) * MATRIX_BLOCK_SIZE], &myfont8x8[0][0], MATRIX_BLOCK_SIZE);    
  }

  rshift[row] = 0; 
  rshifted_sim[row] = 0; 
  maxi_char_cur_part[row] = 0;
}
//============================================================================================
void matrix_set_text (unsigned char row, unsigned char * text, unsigned char len){
  if (len > MATRIX_COLOMS * MATRIX_COUNT)
    len = MATRIX_COLOMS * MATRIX_COUNT;

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;

  unsigned char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT;
  maxi_char_cur_part[row] = 0;
  
  for (unsigned char i = 0; i < len; i++){
    if (is_maxi_mode){
	  fillmaxichar(text[i]);
	  memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &maxichar[maxi_char_cur_part[row] + row * 2][0], MATRIX_BLOCK_SIZE);
	  maxi_char_cur_part[row] = (maxi_char_cur_part[row] + 1) & 1;
	}else{
      memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &myfont8x8[text[i] - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE); 
    }	  
  }
}
//============================================================================================
/*
void matrix_append_char(unsigned char row, unsigned char sim){

  if (row > MATRIX_ROWS - 1)
    row =  MATRIX_ROWS - 1;  

  unsigned char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT;
  for (unsigned char i = 0; i < MATRIX_COLOMS * MATRIX_COUNT - 1; i++){
    memcpy(&rmatrix[(row_start_index + i) * MATRIX_BLOCK_SIZE], &rmatrix[(row_start_index + i + 1) * MATRIX_BLOCK_SIZE], MATRIX_BLOCK_SIZE);  
  }
  
  row_start_index = row_start_index + MATRIX_COLOMS * MATRIX_COUNT - 1;
  memcpy(&rmatrix[row_start_index * MATRIX_BLOCK_SIZE], &myfont8x8[sim - MYFONT8X8SHIFT][0], MATRIX_BLOCK_SIZE);  
}
*/
//============================================================================================
void matrix_rotate_fonts(){
  unsigned char rotated[8];

  for (unsigned char i = 0; i < FONT_COUNT; i++){
    
    memset(rotated, 0, 8);

    for (unsigned char bc = 0; bc < 8; bc++){
      for (unsigned char bits = 0; bits < 8; bits++){
        rotated[bc] |= ((myfont8x8[i][bits] >> bc) & 1) << bits;        
      }
    }
    memcpy(&myfont8x8[i][0], rotated, 8);  
  }
}
//============================================================================================
unsigned char matrix_shift_cycle_left(unsigned char row, unsigned char sim = 0){

  if (!rshift[row]){
    rshifted_sim[row] = sim;  
  }
  
  unsigned char row_start_index = row * MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE;

  unsigned char buf = rmatrix[row_start_index];

  unsigned char i;
  for (i = 0; i < MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE - 1; i++){
    rmatrix[row_start_index + i] = rmatrix[row_start_index + i + 1] ;
  }

  if (rshifted_sim[row]){
    if (is_maxi_mode){
	    fillmaxichar(rshifted_sim[row]);
	    rmatrix[row_start_index + i] = maxichar[maxi_char_cur_part[row] + row * 2][rshift[row]];	  
	  }else{
      rmatrix[row_start_index + i] = myfont8x8[rshifted_sim[row] - MYFONT8X8SHIFT][rshift[row]]; 
	  }
  }else{
    rmatrix[row_start_index + i] = buf;
  }
    
  if (rshift[row] == 7){
    rshifted_sim[row] = 0;
    if (is_maxi_mode){
      maxi_char_cur_part[row] = (maxi_char_cur_part[row] + 1) & 1; 
    }   
  }
  
  rshift[row]++;
  rshift[row] &= 7;
  
  return rshift[row];
}
//============================================================================================

