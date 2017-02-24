#include "MatrixString.h"


MatrixString::MatrixString(){
  memset(str, ' ', MAX_LEN);
  len = 0;
  need_scroll = false;
  next_sim_for_scroll_pos = 0;
  full_scrolled_count = 0;
}
//=============================================================================================
//=============================================================================================
void MatrixString::reset(unsigned char * new_str, unsigned char new_len){
  memcpy(str, new_str, new_len);
  len = new_len;
  need_scroll = false;
  next_sim_for_scroll_pos = 0; 
  full_scrolled_count = 0; 
}
//=============================================================================================
//=============================================================================================
void MatrixString::append(unsigned char sim){
  if (len != MAX_LEN){
    str[len] = sim;
    len++;    
  }
}
//=============================================================================================
//=============================================================================================
unsigned char MatrixString::get_next_sim_for_scroll(){
  char sim = str[next_sim_for_scroll_pos];
  next_sim_for_scroll_pos++;
  if (next_sim_for_scroll_pos == len){
    next_sim_for_scroll_pos = 0;
    full_scrolled_count++;
  }
  return sim;
}
//=============================================================================================
//=============================================================================================

