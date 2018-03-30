//tictactoe
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A2
#define B   A3
#define C   A4
#define D   A5
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void drawx(int x,int y){
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  matrix.drawLine(xcoord, ycoord, xcoord+9, ycoord+9, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord, ycoord+9, xcoord+3, ycoord+6, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+5, ycoord+4, xcoord+9, ycoord, matrix.Color333(0, 0, 1));
}

void drawo(int x,int y){
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  //Sides
    //top
  matrix.drawLine(xcoord+3, ycoord, xcoord+6, ycoord, matrix.Color333(0, 0, 1));
    //left
  matrix.drawLine(xcoord, ycoord+3, xcoord, ycoord+6, matrix.Color333(0, 0, 1));
    //right
  matrix.drawLine(xcoord+9, ycoord+3, xcoord+9, ycoord+6, matrix.Color333(0, 0, 1));
    //bottom
  matrix.drawLine(xcoord+3, ycoord+9, xcoord+6, ycoord+9, matrix.Color333(0, 0, 1));
  
  //Diagonals
    //top left
  matrix.drawLine(xcoord+1, ycoord+2, xcoord+2, ycoord+1, matrix.Color333(0, 0, 1));
    //top right
  matrix.drawLine(xcoord+7, ycoord+1, xcoord+8, ycoord+2, matrix.Color333(0, 0, 1));
    //bottom left
  matrix.drawLine(xcoord+1, ycoord+7, xcoord+2, ycoord+8, matrix.Color333(0, 0, 1));
    //bottom right
  matrix.drawLine(xcoord+7, ycoord+8, xcoord+8, ycoord+7, matrix.Color333(0, 0, 1));
}

void setup() {
  matrix.begin();
  //Grid
  matrix.drawLine(10, 0, 10, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(21, 0, 21, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 10, 31, 10, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 21, 31, 21, matrix.Color333(1, 0, 1));

  //Test shapes
  drawo(2,2);
  drawo(1,0);
  drawx(1,1);
  drawx(2,1);
}


void loop() {
  // put your main code here, to run repeatedly:

}
