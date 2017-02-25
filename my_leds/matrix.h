#ifndef MY_MATRIX_H
#define MY_MATRIX_H

unsigned char * matrix_get_matrix();
void matrix_clear();
void matrix_clear_row(char row);
void matrix_set_text (char row, char * text, char len);
void matrix_append_char(char row, char sim);
char matrix_shift_cycle_left(char row, unsigned char sim = 0);
char matrix_get_shift(char row);

void matrix_rotate_fonts();

#endif
