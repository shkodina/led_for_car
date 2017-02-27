// #include "MatrixString.h"
#ifndef MY_STRING_FOR_MATRIX_H
#define MY_STRING_FOR_MATRIX_H

#include <string.h>

#define MATRIX_STRING_MAX_LEN 128

class MatrixString {
  public:
    char str[MATRIX_STRING_MAX_LEN];
    bool need_scroll;
    unsigned char len;
    unsigned char next_sim_for_scroll_pos;
    unsigned long full_scrolled_count;

    char color;
	
    MatrixString();
    unsigned char get_next_sim_for_scroll();
    void reset(unsigned char * new_str, unsigned char new_len, char new_color);
    void append(unsigned char sim);
};

#endif
