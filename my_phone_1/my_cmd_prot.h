#ifndef MY_CMD_PROT_H
#define MY_CMD_PROT_H

#define CMD_MAX_THRESHOLD 0x20

#define COLOR_R 1
#define COLOR_G 2
#define COLOR_B 4

enum CMD_FOR_LEDS 
{
  STUB =            0x00,
  CLEAR_MATRIX =    0x01, 
  CLEAR0ROW =       0x02,
  CLEAR1ROW =       0x03,
  SCROL_MATRIX =    0x04,
  SCROL0ROW_START = 0x05,
  SCROL1ROW_START = 0x06,
  SCROL0ROW_STOP =  0x07,
  SCROL1ROW_STOP =  0x08,
  SET_COLOR0 =      0x09,
  SET_COLOR1 =      0x0a,
  SET_STR0 =        0x0b,
  SET_STR1 =        0x0c,
  STR_STOP =        0x0d,
  SET_SCROLL =      0x0e,
  STUB17 = 0x0f,
  STUB16 = 0x10,
  STUB15 = 0x11,
  STUB14 = 0x12,
  STUB13 = 0x13,
  STUB12 = 0x14,
  STUB11 = 0x15,
  STUB10 = 0x16,
  STUB9 = 0x17,
  STUB8 = 0x18,
  STUB7 = 0x19,
  STUB6 = 0x1a,
  STUB5 = 0x1b,
  STUB4 = 0x1c,
  STUB3 = 0x1d,
  STUB2 = 0x1e,
  STUB1 = 0x1f
};

#endif