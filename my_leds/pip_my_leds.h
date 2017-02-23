#ifndef PIP_MY_LEDS_H
#define PIP_MY_LEDS_H

void set_rgb1_pins_out();
void set_rgb2_pins_out();
void set_addr_pins_out();
void set_cmd_pins_out();

void set_addr(unsigned char addr);
void set_row(unsigned char addr);
void puls_clk();
void puls_lat();
void put_oe_high();
void put_oe_low();

void push_rgb_1_2_data(unsigned char * rgb1, unsigned char * rgb2, unsigned char count);

void push_r_data_by_row(unsigned char * r_matrix, char row);

#endif
