#include "pip_my_leds.h"
#include "TimerThree.h"
#include "matrix.h"

#define TIME_TO_SHIFT 50
unsigned char sim_to_shift = 0;

enum { LED_PIN = 13 };
enum LedState { LED_ON, LED_OFF, LED_BLINK };

LedState led_state;

unsigned char * lc_matrix;
//============================================================================================
//============================================================================================
void setup() {
  // put your setup code here, to run once:
  set_rgb1_pins_out();
  set_rgb2_pins_out();
  set_addr_pins_out();
  set_cmd_pins_out();

  Timer3.initialize(2500);
  Timer3.attachInterrupt(print_row_matrix);

  led_state = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  
  Serial1.begin(9600);
  Serial.begin(9600);

  matrix_rotate_fonts();

  matrix_clear();
  matrix_set_text(0, "12345678", 8);
  matrix_set_text(1, "abcdefgh", 8);
  lc_matrix = matrix_get_matrix();
}
//============================================================================================
//============================================================================================
void print_row_matrix(){
  static int time_to_shift = 0;
  
  static unsigned char cur_row = 0;
   
  push_r_data_by_row(lc_matrix , cur_row);
  set_row(cur_row++); 

  cur_row &= 7;

  if (++time_to_shift >= TIME_TO_SHIFT){
    
    if (sim_to_shift){
      if(! matrix_get_shift(0)){
        matrix_shift_cycle_left(0, sim_to_shift);
        sim_to_shift = 0;
      }
    }
      
    matrix_shift_cycle_left(0);
    time_to_shift = 0;
  }
}
//============================================================================================
//============================================================================================
void loop() {

  switch (led_state)
  {
    case LED_ON: digitalWrite(LED_PIN, HIGH); break;
    case LED_OFF: digitalWrite(LED_PIN, LOW); break;
    
    case LED_BLINK:
    {
      static unsigned long start_millis = 0;
      
      if (millis() - start_millis >= 300)
      {
        start_millis = millis();
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      }
    }
  }
}
//============================================================================================
//============================================================================================
void serialEvent1() {
  Timer3.stop();
  // put your main code here, to run repeatedly:
  static unsigned char pos = 0;

  if (Serial1.available())
  {
    char command = Serial1.read();
    
    //matrix_append_char(0, command);
    
    sim_to_shift = command;
    matrix_append_char(1, command);

    Serial.write(command);
    
    switch (command)
    {
      case '1': led_state = LED_ON; break;
      case '0': led_state = LED_OFF; break;
      case '*': led_state = LED_BLINK; break;
      case '-': led_state = LED_BLINK; matrix_clear(); break;
      
      default:/*
      {
        for (int i = 0; i < 5; ++i)
        {
          digitalWrite(LED_PIN, HIGH);
          delay(50);
          digitalWrite(LED_PIN, LOW);
          delay(50);
        }
      }*/
      ;
    }
  }
  Timer3.start();
}
//============================================================================================
//============================================================================================

