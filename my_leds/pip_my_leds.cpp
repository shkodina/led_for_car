#include "pip_my_leds.h"
#include "pip_my_leds_defs.h"

#include "matrix_defs.h"

#include <Arduino.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void stub(char){}
unsigned char str1color = COLOR_R;
unsigned char str2color = COLOR_R << COLOR_SHIFT;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void (*printerForRow1)(char) = stub;
void (*printerForRow2)(char) = stub;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_rgb1_pins_out(){
  pinMode(PinR1, OUTPUT);   
  pinMode(PinG1, OUTPUT);   
  pinMode(PinB1, OUTPUT); 
  digitalWrite(PinR1, LOW);  
  digitalWrite(PinG1, LOW);  
  digitalWrite(PinB1, LOW);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_rgb2_pins_out(){
  pinMode(PinR2, OUTPUT);   
  pinMode(PinG2, OUTPUT);   
  pinMode(PinB2, OUTPUT); 
  digitalWrite(PinR2, LOW);  
  digitalWrite(PinG2, LOW);  
  digitalWrite(PinB2, LOW);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_addr_pins_out(){
  pinMode(PinAdrA, OUTPUT);   
  pinMode(PinAdrB, OUTPUT);   
  pinMode(PinAdrC, OUTPUT);   
  pinMode(PinAdrD, OUTPUT);  
  digitalWrite(PinAdrA, LOW);  
  digitalWrite(PinAdrB, LOW);  
  digitalWrite(PinAdrC, LOW);  
  digitalWrite(PinAdrD, LOW);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_cmd_pins_out(){
  pinMode(CMDLAT, OUTPUT);   
  pinMode(CMDCLK, OUTPUT);   
  pinMode(CMDOE, OUTPUT);   
  digitalWrite(CMDLAT, LOW);  
  digitalWrite(CMDCLK, LOW);  
  digitalWrite(CMDOE, LOW);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_addr(unsigned char addr){
  PORTA &= 0xf0;
  PORTA |= addr;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void puls_clk(){
  digitalWrite(CMDCLK, HIGH);   
  delayMicroseconds(PULS_CLK_DELAY_US);
  digitalWrite(CMDCLK, LOW);   
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void puls_lat(){
  digitalWrite(CMDLAT, HIGH);   
  delayMicroseconds(PULS_LAT_DELAY_US);
  digitalWrite(CMDLAT, LOW);   
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void set_row (unsigned char addr){
  digitalWrite(CMDOE, HIGH);  
  set_addr(addr);
  puls_lat();
  digitalWrite(CMDOE, LOW);     
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void put_oe_high (){
  digitalWrite(CMDOE, HIGH);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void put_oe_low (){
  digitalWrite(CMDOE, LOW);  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void push_r_data_by_row(unsigned char * r_matrix, char row){

  char r1pos = 0;
  char r2pos = r1pos + MATRIX_COLOMS * MATRIX_BLOCK_SIZE * MATRIX_COUNT;

  for (char i = 0; i < MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE; i++){
    PORTC &= 0b11000000;
    PORTC = ((( r_matrix[r1pos + i] >> row ) & 1 ) * str1color) | ((( r_matrix[r2pos + i] >> row ) & 1 ) * str2color) ;
    puls_clk(); 
  }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void set_colors(char color1, char color2){
  str1color = (color1 & 0b00000111);
  str2color = (color2 & 0b00000111) << COLOR_SHIFT;  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

