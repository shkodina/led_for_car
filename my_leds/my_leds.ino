#include "pip_my_leds.h"
#include "TimerThree.h"
#include "matrix.h"
#include "matrix_defs.h"
#include "MatrixString.h"

#define TIMER_INIT_VAL_US 300
#define TIMER_PRINT_ROW_PERIOD 2
#define TIMER_SHIFT_PERIOD 200

enum { LED_PIN = 13 };
enum LedState { LED_ON, LED_OFF, LED_BLINK };
LedState led_state;

unsigned char * lc_matrix;
MatrixString strings[MATRIX_ROWS];

//============================================================================================
//============================================================================================
void init_global_values(){

  lc_matrix = matrix_get_matrix();
}
//============================================================================================
//============================================================================================
void setup() {
  // put your setup code here, to run once:
  set_rgb1_pins_out();
  set_rgb2_pins_out();
  set_addr_pins_out();
  set_cmd_pins_out();

  init_global_values();
  
  Timer3.initialize(TIMER_INIT_VAL_US);
  Timer3.attachInterrupt(state_machine);

  led_state = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  
  Serial1.begin(9600);
  Serial.begin(9600);


  strings[0].reset("Piper is", 8);
  strings[1].reset("the best", 8);
  

  matrix_rotate_fonts();
  matrix_clear();
  matrix_set_text(0, strings[0].str, 8);
  matrix_set_text(1, strings[1].str, 8);
  
}
//============================================================================================
//============================================================================================
void print_row(){
  static unsigned char cur_row = 0;  
  push_r_data_by_row(lc_matrix , cur_row);
  set_row(cur_row++); 
  cur_row &= 7;    
}
//=====================================================================================
//=====================================================================================
void state_machine(){
  static unsigned long tic_print_row = 0; 
  static unsigned long tic_shift = 0;  

  if (tic_print_row++ == TIMER_PRINT_ROW_PERIOD){
    tic_print_row = 0;
    print_row();  
  }
  
  if (tic_shift++ == TIMER_SHIFT_PERIOD){
    tic_shift = 0;


    
    for (char i = 0; i < MATRIX_ROWS; i++){
      if (strings[i].need_scroll){
        if(! matrix_get_shift(i)){
          if ( strings[i].len <= MATRIX_COUNT * MATRIX_COLOMS){
            matrix_shift_cycle_left(i);    
          }else{
            matrix_shift_cycle_left(i, strings[i].get_next_sim_for_scroll());
          }
        }else{
          matrix_shift_cycle_left(i);    
        }
                
      }
    }
  }
}
//=====================================================================================
//=====================================================================================
/*
void print_row_matrix(){
  static int time_to_shift = 0;
  


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
*/
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
enum CMDpoints {CMD_WAIT, CMD_INIT, CMD_GATHERING, CMD_CHECKING};

void serialEvent1() {
  Timer3.stop();
  // put your main code here, to run repeatedly:
  static unsigned char state = CMD_WAIT;

  while (Serial1.available())
  {
    char sim = Serial1.read();
 
    Serial.write(sim);
    
    switch (sim)
    {
      case '1': led_state = LED_ON; strings[1].need_scroll = !strings[1].need_scroll;  break;
      case '0': led_state = LED_OFF; strings[0].need_scroll = !strings[0].need_scroll; break;
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

