#include "pip_my_leds.h"
#include "pip_my_leds_defs.h"

#include "matrix_defs.h"

#include <Arduino.h>

void set_rgb1_pins_out(){
  pinMode(PinR1, OUTPUT);   
  pinMode(PinG1, OUTPUT);   
  pinMode(PinB1, OUTPUT); 
  digitalWrite(PinR1, LOW);  
  digitalWrite(PinG1, LOW);  
  digitalWrite(PinB1, LOW);  
}

void set_rgb2_pins_out(){
  pinMode(PinR2, OUTPUT);   
  pinMode(PinG2, OUTPUT);   
  pinMode(PinB2, OUTPUT); 
  digitalWrite(PinR2, LOW);  
  digitalWrite(PinG2, LOW);  
  digitalWrite(PinB2, LOW);  
  
}

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

void set_cmd_pins_out(){
  pinMode(CMDLAT, OUTPUT);   
  pinMode(CMDCLK, OUTPUT);   
  pinMode(CMDOE, OUTPUT);   
  digitalWrite(CMDLAT, LOW);  
  digitalWrite(CMDCLK, LOW);  
  digitalWrite(CMDOE, LOW);  
}

void set_addr(unsigned char addr){
  digitalWrite(PinAdrD, LOW); 
  switch (addr){
    case 0:
      digitalWrite(PinAdrA, LOW); 
      digitalWrite(PinAdrB, LOW); 
      digitalWrite(PinAdrC, LOW); 
    break;
    case 1:
      digitalWrite(PinAdrA, HIGH); 
      digitalWrite(PinAdrB, LOW); 
      digitalWrite(PinAdrC, LOW); 
    break;
    case 2:
      digitalWrite(PinAdrA, LOW); 
      digitalWrite(PinAdrB, HIGH); 
      digitalWrite(PinAdrC, LOW); 
    break;
    case 3:
      digitalWrite(PinAdrA, HIGH); 
      digitalWrite(PinAdrB, HIGH); 
      digitalWrite(PinAdrC, LOW); 
    break;
    case 4:
      digitalWrite(PinAdrA, LOW); 
      digitalWrite(PinAdrB, LOW); 
      digitalWrite(PinAdrC, HIGH); 
    break;
    case 5:
      digitalWrite(PinAdrA, HIGH); 
      digitalWrite(PinAdrB, LOW); 
      digitalWrite(PinAdrC, HIGH); 
    break;
    case 6:
      digitalWrite(PinAdrA, LOW); 
      digitalWrite(PinAdrB, HIGH); 
      digitalWrite(PinAdrC, HIGH); 
    break;
    case 7:
      digitalWrite(PinAdrA, HIGH); 
      digitalWrite(PinAdrB, HIGH); 
      digitalWrite(PinAdrC, HIGH); 
    break;
    default:
      digitalWrite(PinAdrA, LOW); 
      digitalWrite(PinAdrB, LOW); 
      digitalWrite(PinAdrC, LOW); 
    break;
  }
}

void puls_clk(){
  digitalWrite(CMDCLK, HIGH);   
  delayMicroseconds(PULS_CLK_DELAY_US);
  digitalWrite(CMDCLK, LOW);   
}

void puls_lat(){
  digitalWrite(CMDLAT, HIGH);   
  delayMicroseconds(PULS_LAT_DELAY_US);
  digitalWrite(CMDLAT, LOW);   
}

void set_row (unsigned char addr){
  digitalWrite(CMDOE, HIGH);  
  set_addr(addr);
  puls_lat();
  digitalWrite(CMDOE, LOW);     
}

void put_oe_high (){
  digitalWrite(CMDOE, HIGH);  
}

void put_oe_low (){
  digitalWrite(CMDOE, LOW);  
}

void push_r_data_by_row(unsigned char * r_matrix, char row){

  char r1pos = 0;
  char r2pos = r1pos + MATRIX_COLOMS * MATRIX_BLOCK_SIZE * MATRIX_COUNT;

  for (char i = 0; i < MATRIX_COLOMS * MATRIX_COUNT * MATRIX_BLOCK_SIZE; i++){
    digitalWrite(PinR1, (( r_matrix[r1pos + i] >> row ) & 1 )); 
    digitalWrite(PinR2, (( r_matrix[r2pos + i] >> row ) & 1 ));
    puls_clk(); 
  }
}

