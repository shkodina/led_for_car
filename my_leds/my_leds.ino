#include "pip_my_leds.h"
#include "TimerThree.h"
#include "matrix.h"
#include "matrix_defs.h"
#include "MatrixString.h"
#include "my_cmd_prot.h"
#include "eeprom_matrix_strings.h"

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define TIMER_INIT_VAL_US 300
#define TIMER_PRINT_ROW_PERIOD 1
#define TIMER_SHIFT_DEFAULT_PERIOD 105
#define TIMER_CMD_TIMEOUT 90

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 
RF24 radio(6,7);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

bool g_need_cmd_timeout = false;
static unsigned char command = STUB;

// CHANGEABLE PARAMS
unsigned int TIMER_SHIFT_PERIOD = TIMER_SHIFT_DEFAULT_PERIOD;

enum { LED_PIN = 13 };

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

  pinMode(LED_PIN, OUTPUT);
  
  Serial1.begin(9600);
  Serial.begin(9600);

  unsigned char str1[6] = {0xCF, 0xF0, 0xE8, 0xE2, 0xE5, 0xF2}; // Privet in russian
  
  strings[0].reset(str1, 6, COLOR_R);
  strings[1].reset("абвгдежзиклмнопрстуфхцчшщъыьэюя", 31, COLOR_G);

  set_colors(strings[0].color, strings[1].color);

  matrix_rotate_fonts();
  matrix_clear();

  strings[0].need_scroll = true;
  strings[1].need_scroll = true;

  // rf24l01
  // Setup and configure rf radio
  printf_begin();
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
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
  static unsigned long tic_cmd_timeout = 0;

  if (tic_print_row++ >= TIMER_PRINT_ROW_PERIOD){
    tic_print_row = 0;
    print_row();  
  }
  
  if (tic_shift++ >= TIMER_SHIFT_PERIOD){
    tic_shift = 0;


    
    for (unsigned char i = 0; i < MATRIX_ROWS; i++){
      if (strings[i].need_scroll){
        if(! matrix_get_shift(i)){
          matrix_shift_cycle_left(i, strings[i].get_next_sim_for_scroll());
        }else{
          matrix_shift_cycle_left(i);    
        }        
      }
    }
  }

  if (g_need_cmd_timeout && tic_cmd_timeout++ >= TIMER_CMD_TIMEOUT){
    tic_cmd_timeout = 0;
    g_need_cmd_timeout = false;
    command = STUB;     
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
/*
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
  */      
  
  if (radio.available()){
    Timer3.stop();
    byte sim = -1;
    radio.read( &sim, 1 ); 
    Serial.print(sim, HEX);
    sim %= 6;
    eeprom_str_get(&strings[0], sim); 
    prepare_str(0);
    Timer3.start();
  }
  
          
          

          
}
//============================================================================================
//============================================================================================
void prepare_str(unsigned char str_num){
  set_colors(strings[0].color, strings[1].color);   
            
  if ( strings[str_num].len > MATRIX_COLOMS * MATRIX_COUNT ){
    matrix_clear_row(str_num);
    strings[str_num].need_scroll = true;  
    strings[str_num].next_sim_for_scroll_pos = 0;
  }else{
    matrix_set_text(str_num, strings[str_num].str, strings[str_num].len) ; 
    strings[str_num].need_scroll = false;
    strings[str_num].next_sim_for_scroll_pos = 0;
  }  
            
}

//============================================================================================
//============================================================================================
enum CMDpoints {CMD_WAIT, CMD_INIT, CMD_GATHERING, CMD_CHECKING};

void serialEvent1() {
  Timer3.stop();


  static char str_num = -1;

  static unsigned char str_pos = 0;
  static unsigned char new_str[MATRIX_STRING_MAX_LEN];

  while (Serial1.available())
  {
    unsigned char sim = Serial1.read();
    Serial.print(sim, HEX);

    if (command == STUB){
      if (sim < CMD_MAX_THRESHOLD){ // get CMD
        switch (sim){
          case CLEAR_MATRIX:
            strings[0].need_scroll = false;
            strings[1].need_scroll = false;
            strings[0].next_sim_for_scroll_pos = 0;
            strings[1].next_sim_for_scroll_pos = 0;
            matrix_clear(); 
          break;
    
          case CLEAR0ROW:
            strings[0].need_scroll = false;
            strings[0].next_sim_for_scroll_pos = 0;
            matrix_clear_row(0);
          break;
          
          case CLEAR1ROW:
            strings[1].need_scroll = false;
            strings[1].next_sim_for_scroll_pos = 0;
            matrix_clear_row(1);
          break;
    
          case SCROL_MATRIX:
            //Serial.print("scroll matrix");
            strings[0].need_scroll = true;  
            strings[1].need_scroll = true;  
          break;
    
          case SCROL0ROW_START:
            //Serial.print("scroll 0");
            strings[0].need_scroll = true;   
          break;
    
          case SCROL1ROW_START:
            //Serial.print("scroll 1");
            strings[1].need_scroll = true;  
          break;
    
          case SCROL0ROW_STOP:
            //Serial.print("scroll 0 stop");
            strings[0].need_scroll = false;   
          break;
    
          case SCROL1ROW_STOP:
            //Serial.print("scroll 1 stop");
            strings[1].need_scroll = false;  
          break;
  
          case SET_STR0:
            Serial.print("\n ask new str 0 = ");
            str_num = 0;
            str_pos = 0; 
            command = SET_STR0;
          break;
          case SET_STR1:
            Serial.print("\n ask new str 1 = ");
            str_num = 1;
            str_pos = 0; 
            command = SET_STR1;
          break;
          
          case SET_COLOR0:
            command = SET_COLOR0;
            str_num = 0;
          break;
          case SET_COLOR1:
            command = SET_COLOR0;
            str_num = 1;
          break;
          
          case SET_SCROLL:
            command = SET_SCROLL;
          break;

          case SET_STR0_MEMORED:
            command = SET_STR0_MEMORED;
          break;
              
          case SHOW_MEMORED_STR:
            command = SHOW_MEMORED_STR;
          break;
               
          default:
          ;
        }
      }      
    }else{ // CMD DATA
      switch(command){
        case SET_STR0:
        case SET_STR1:
          if (sim != STR_STOP){
            new_str[str_pos++] = sim;    
          }else{
            command = STUB;
            strings[str_num].reset(new_str, str_pos, COLOR_R);

            prepare_str(str_num);
            
            str_num = -1;  
            str_pos = 0;  
          }
        break;
          
        case SET_COLOR0:
        case SET_COLOR1:
          command = STUB;
          if (sim > 0 && (sim < (COLOR_R | COLOR_G | COLOR_B))){
            strings[str_num].color = sim;  
          }else{
            strings[str_num].color = COLOR_R;  
          }
          set_colors(strings[0].color, strings[1].color);  
          str_num = -1;
        break; 

        case SET_SCROLL:
          command = STUB;          
          if (sim > 20 && sim < 250){
            TIMER_SHIFT_PERIOD = sim;  
          }else{
            TIMER_SHIFT_PERIOD = TIMER_SHIFT_DEFAULT_PERIOD;  
          }          
        break;

        case SET_STR0_MEMORED:
          command = STUB;
          eeprom_str_set(&strings[0], sim);
        break;

        case SHOW_MEMORED_STR:
          command = STUB;
          eeprom_str_get(&strings[0], sim);
          prepare_str(0);
        break;
        
        
        default:
          command = STUB;
        break;  
      }
    }
  }
  Timer3.start();
}
//============================================================================================
//============================================================================================

