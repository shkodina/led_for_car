#ifndef MY_MATRIX_H
#define MY_MATRIX_H

unsigned char * matrix_get_matrix();
void matrix_clear();
void matrix_clear_row(unsigned char row);
void matrix_set_text (unsigned char row, unsigned char * text, unsigned char len);
//void matrix_append_char(unsigned char row, unsigned char sim);
unsigned char matrix_shift_cycle_left(unsigned char row, unsigned char sim = 0);
unsigned char matrix_get_shift(unsigned char row);
void matrix_set_maxi_font_mode(bool mode_set);
bool matrix_get_maxi_font_mode();

void matrix_rotate_fonts();

#endif
