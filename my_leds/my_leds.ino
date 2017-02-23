#include "pip_my_leds.h"
#include "TimerThree.h"
#include "matrix.h"


//unsigned char rgb1[12] = {0xff,0,0,0,0xff,0,0xff,0xff,0,0,0,0xff};
//unsigned char rgb2[12] = {0xff,0,0xff,0,0xff,0xff,0xff,0xff,0xff,0b11000000,0b00011000,0b00000011};
unsigned char rgb1[12] = {0xff,0,0,0,0xff,0,0xff,0xff,0,0,0,0xff};
unsigned char rgb2[12] = {0xff,0,0xff,0,0xff,0xff,0b10011001,0b10011001,0b10011001,0b11000000,0b00011000,0b00000011};

enum { LED_PIN = 13 };
enum LedState { LED_ON, LED_OFF, LED_BLINK };

LedState led_state;

unsigned char * lc_matrix;


void setup() {
  // put your setup code here, to run once:
  set_rgb1_pins_out();
  set_rgb2_pins_out();
  set_addr_pins_out();
  set_cmd_pins_out();

  Timer3.initialize(2300);
  Timer3.attachInterrupt(print_row_matrix);



  led_state = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  
  Serial1.begin(9600);
  Serial.begin(9600);

  matrix_clear();
  set_text(0, "1234", 4);
  set_text(1, "abcd", 4);
  lc_matrix = matrix_get_matrix();
}

void print_row_matrix(){
  static unsigned char cur_row = 0;
   
  //push_rgb_1_2_data(rgb1, rgb2, 4);

  push_r_data_by_row(lc_matrix , cur_row);
  set_row(cur_row++); 

  cur_row &= 7;
}

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

void serialEvent1() {
  Timer3.stop();
  // put your main code here, to run repeatedly:
  static unsigned char pos = 0;

  if (1)//Serial1.available())
  {
    char command = Serial1.read();
    
    rgb2[pos++] = command;
    if (pos == 12)
      pos = 0;

    Serial.write(command);
    
    switch (command)
    {
      case '1': led_state = LED_ON; break;
      case '0': led_state = LED_OFF; break;
      case '*': led_state = LED_BLINK; break;
      
      default:
      {
        for (int i = 0; i < 5; ++i)
        {
          digitalWrite(LED_PIN, HIGH);
          delay(50);
          digitalWrite(LED_PIN, LOW);
          delay(50);
        }
      }
    }
  }
  Timer3.start();
}
