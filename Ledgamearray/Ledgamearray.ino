//MAIN FILE
#include <Globals.h>
#include <ttt.h>
#include <pong.h>
#include <Music.h>
#include <Menu.h>

//LCD Screen
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
//RGB LED Matrix
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
// MUSIC Board
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);
//Gets menu choice
int choice;

void setup() {
  //RGB LED Matrix init
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0,0,0));
  //Music board init
  mySerial.begin(9600);
  delay(500);//Wait chip initialization is complete
  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card
  delay(200);//wait for 200ms
  sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class
  
  //Joystick init
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(XPIN2, INPUT);
  pinMode(YPIN2, INPUT);
  pinMode(BTN2, INPUT_PULLUP);
  
  //LCD init
  lcd.begin(16, 2);

  //Random seed
  randomSeed(analogRead(0));
}
void loop() {
  matrix.setTextColor(matrix.Color333(0,0,2));
  choice = menu();
  if(choice == 0){tttgame();}
  if(choice == 1){pong();}
  delay(5000);//Prevents accidental click when exiting game
}
