/*
  // March 2014 - TMRh20 - Updated along with High Speed RF24 Library fork
  // Parts derived from examples by J. Coliz <maniacbug@ymail.com>
*/
/**
 * Example for efficient call-response using ack-payloads 
 *
 * This example continues to make use of all the normal functionality of the radios including
 * the auto-ack and auto-retry features, but allows ack-payloads to be written optionally as well.
 * This allows very fast call-response communication, with the responding radio never having to 
 * switch out of Primary Receiver mode to send back a payload, but having the option to if wanting
 * to initiate communication instead of respond to a commmunication.
 */
 


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 
RF24 radio(6,7);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

#define STR_0_PIN 2
#define STR_1_PIN 3
#define STR_2_PIN 4
#define STR_3_PIN 5
#define STR_4_PIN 8
#define STR_5_PIN 9

#define STR_RELEASED -1
void setup(){

  Serial.begin(9600);
  printf_begin();
  Serial.print(F("\n\rEnter nomber of string to demos: "));

  // Setup and configure rf radio

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[0]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[1]);
  //radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging


  // pinsout
  pinMode(STR_0_PIN, INPUT_PULLUP);
  pinMode(STR_1_PIN, INPUT_PULLUP);
  pinMode(STR_2_PIN, INPUT_PULLUP);
  pinMode(STR_3_PIN, INPUT_PULLUP);
  pinMode(STR_4_PIN, INPUT_PULLUP);
  pinMode(STR_5_PIN, INPUT_PULLUP);
}

void loop(void) {
  if (Serial.available()){
    unsigned char sim = Serial.read();
    sim -= 48;
    radio.write( &sim, 1 );
  }

  static char last_pressed = STR_RELEASED;

  if(digitalRead(STR_0_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_0_PIN;
    unsigned char sim = 0;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_1_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_1_PIN;
    unsigned char sim = 1;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_2_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_2_PIN;
    unsigned char sim = 2;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_3_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_3_PIN;
    unsigned char sim = 3;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_4_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_4_PIN;
    unsigned char sim = 4;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_5_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_5_PIN;
    unsigned char sim = 5;
    radio.write( &sim, 1 ); 
  }

  if(digitalRead(STR_0_PIN) == HIGH && 
     digitalRead(STR_1_PIN) == HIGH &&
     digitalRead(STR_2_PIN) == HIGH &&
     digitalRead(STR_3_PIN) == HIGH &&
     digitalRead(STR_4_PIN) == HIGH &&
     digitalRead(STR_5_PIN) == HIGH)
  {
    last_pressed =  STR_RELEASED;
  }
  
}
