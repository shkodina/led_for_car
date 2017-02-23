#ifndef MY_MATRIX_H
#define MY_MATRIX_H

unsigned char * matrix_get_matrix();
void matrix_clear();
void matrix_set_text (char row, char * text, char len);
void matrix_append_char(char row, char sim);

void matrix_rotate_fonts();

#endif
