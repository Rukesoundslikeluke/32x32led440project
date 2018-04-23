#ifndef _MENU_H
#define _MENU_H
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <LiquidCrystal.h> // Lcd library
#include <SoftwareSerial.h>//Music board library

//External global variables that will be defined elsewhere
extern RGBmatrixPanel matrix;
extern LiquidCrystal lcd;
extern SoftwareSerial mp3;

//RGB Board
#define CLK 11  
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

//LCD SCREEN
#define RS 45
#define EN 47
#define D4 49
#define D5 44
#define D6 46
#define D7 48

//PLAYER 1
#define YPIN  A12
#define XPIN  A13
#define BTN 35

//PLAYER 2
#define YPIN2  A14
#define XPIN2  A15
#define BTN2 39

//MUSIC BOARD
#define ARDUINO_RX 1
#define ARDUINO_TX 0

//MUSIC CONTROLS
#define CMD_NEXT_SONG       0X01  // Play next song.
#define CMD_PREV_SONG       0X02  // Play previous song.
#define CMD_PLAY_W_INDEX    0X03

#define CMD_VOLUME_UP       0X04
#define CMD_VOLUME_DOWN     0X05
#define CMD_SET_VOLUME      0X06

#define CMD_SEL_DEV         0X09
#define DEV_TF              0X02
#define CMD_PLAY            0X0D
#define CMD_PAUSE           0X0E
#define CMD_SINGLE_CYCLE    0X19
#define SINGLE_CYCLE_ON     0X00
#define SINGLE_CYCLE_OFF    0X01
#define CMD_PLAY_W_VOL      0X22

#endif
