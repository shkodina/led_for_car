#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>

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

void setup() {
  // put your setup code here, to run once:
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
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging}


   // pinsout
  pinMode(STR_0_PIN, INPUT_PULLUP);
  pinMode(STR_1_PIN, INPUT_PULLUP);
  pinMode(STR_2_PIN, INPUT_PULLUP);
  pinMode(STR_3_PIN, INPUT_PULLUP);
  pinMode(STR_4_PIN, INPUT_PULLUP);
  pinMode(STR_5_PIN, INPUT_PULLUP);

}
//============================================================================
#define DATA_MARKER_MASK  0b10000001
#define DATA_CRCBIT_MASK  0b00000010
#define DATA_CRCBIT_SHIFT 1
#define DATA_DATA_MASK    0b00111100
#define DATA_DATA_SHIFT   2
/*
char try_get_data_from_pack(unsigned char data){
  if (data & DATA_MARKER_MASK != DATA_MARKER_MASK)
    return -1;

  char payload = ((data & DATA_DATA_MASK) >> DATA_DATA_SHIFT);
  if (((payload % 2) << DATA_CRCBIT_SHIFT) != (data & DATA_CRCBIT_MASK)){
    return -2;
  }

  return  payload;
}
*/
//============================================================================
char put_data_to_pack(char data){
  char crcbit = ((data % 2 ) << DATA_CRCBIT_SHIFT);
  data = data << DATA_DATA_SHIFT;
  data = data | crcbit;
  data = data | DATA_MARKER_MASK;
  return data;
}
//============================================================================
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    unsigned char sim = Serial.read();
    sim -= 48;
    radio.write( &sim, 1 );
  }

  static char last_pressed = STR_RELEASED;

  if(digitalRead(STR_0_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_0_PIN;
    unsigned char sim = put_data_to_pack(0);
    radio.write( &sim, 1 ); 
    Serial.println("STR_0_PIN");
  }

  if(digitalRead(STR_1_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_1_PIN;
    unsigned char sim = put_data_to_pack(1);
    radio.write( &sim, 1 ); 
    Serial.println("STR_1_PIN");
  }

  if(digitalRead(STR_2_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_2_PIN;
    unsigned char sim = put_data_to_pack(2);
    radio.write( &sim, 1 ); 
    Serial.println("STR_2_PIN");
  }

  if(digitalRead(STR_3_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_3_PIN;
    unsigned char sim = put_data_to_pack(3);
    radio.write( &sim, 1 ); 
    Serial.println("STR_3_PIN");
  }

  if(digitalRead(STR_4_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_4_PIN;
    unsigned char sim = put_data_to_pack(4);
    radio.write( &sim, 1 ); 
    Serial.println("STR_4_PIN");
  }

  if(digitalRead(STR_5_PIN) == LOW && last_pressed == STR_RELEASED){
    last_pressed =  STR_5_PIN;
    unsigned char sim = put_data_to_pack(5);
    radio.write( &sim, 1 ); 
    Serial.println("STR_5_PIN");
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
