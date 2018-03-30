//TIC-TAC-TOE
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

//RGB Board
#define CLK 8  
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

//Analog Stick
#define YPIN  A4
#define XPIN  A5
#define BTN 12
int xPos = 0;
int yPos = 0;
int btnState = 0;

//Pixel mov
int pix = 1;
int piy = 1;
int cix = 0;
int ciy = 0;
bool mov = false;

//Game State
// 0 = free
// 1 = X
// 2 = O
int board[3][3] = {0};
bool openspc = true;
bool turn = false;

//How the rgb board works
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

 //GAME STATE FUNCTIONS
 bool openspace(int x,int y){
  if(board[x][y] == 0){ return true;}
  return false;
 }
 void mark(int c,int x,int y){
    if(c == 1){board[x][y] = 1;}
    else if(c == 2){board[x][y] = 2;}
    else{board[x][y] = 0;}
 }


//DRAW FUNCTIONS
//Think of drawing as a normal array 
//i.e. drawx(0,1) - > | |x| |
//                    | | | |
//     drawo(2,2) ->  | | |o|
//
//Top left led of each array section
//  (0,0) |(11,0) |(22,0)
//  (0,11)|(11,11)|(22,11)
//  (0,22)|(11,22)|(22,22)
void drawx(int x,int y){  //Draws an x at given point
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  matrix.drawLine(xcoord, ycoord, xcoord+9, ycoord+9, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord, ycoord+9, xcoord+9, ycoord, matrix.Color333(0, 0, 1));
  mark(1,x,y);
}
void drawo(int x,int y){  //Draws an o at given point
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  //Sides of Circle - order(top,left,right,bottom)
  matrix.drawLine(xcoord+3, ycoord, xcoord+6, ycoord, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord, ycoord+3, xcoord, ycoord+6, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+9, ycoord+3, xcoord+9, ycoord+6, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+3, ycoord+9, xcoord+6, ycoord+9, matrix.Color333(0, 0, 1));
  //Diagonals of Circle - order(tl,tr,bl,br)
  matrix.drawLine(xcoord+1, ycoord+2, xcoord+2, ycoord+1, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+7, ycoord+1, xcoord+8, ycoord+2, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+1, ycoord+7, xcoord+2, ycoord+8, matrix.Color333(0, 0, 1));
  matrix.drawLine(xcoord+7, ycoord+8, xcoord+8, ycoord+7, matrix.Color333(0, 0, 1));
  mark(2,x,y);
}
void drawcursor(int d, int x, int y){
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  if(d == 0){ matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(0, 0, 0));}
  else if(d == 2){matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(1, 0, 0));}
  else{ matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(0, 1, 0));}
 }
 void drawboard(int x, int y){
  for(int i=0;i<3;++i){
    for(int j=0;j<3;++j){
      if(i == x && j == y){}
      else if(board[i][j] == 1){drawx(i,j);}
      else if(board[i][j] == 2){drawo(i,j);}
  }
 }
}

void setup() {
  matrix.begin();
  //Grid
  matrix.drawLine(10, 0, 10, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(21, 0, 21, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 10, 31, 10, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 21, 31, 21, matrix.Color333(1, 0, 1));

// initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  //activate pull-up resistor on the push-button pin
  pinMode(BTN, INPUT_PULLUP);
}


void loop() {
  xPos = analogRead(XPIN);
  yPos = analogRead(YPIN);
  btnState = digitalRead(BTN);
  
  Serial.print("X: ");
  Serial.print(xPos);
  Serial.print(" | Y: ");
  Serial.print(yPos);
  Serial.print(" | Button: ");
  Serial.println(btnState);
 
  //Cursor movement
  mov = false;
  cix = pix;
  ciy = piy;
  if(xPos <= 25 && pix > 0)   { pix -= 1; mov = true;}
  if(xPos >= 1000 && pix < 2){ pix += 1; mov = true;}
  if(yPos <= 25 && piy > 0)   { piy -= 1; mov = true;}
  if(yPos >= 1000 && piy < 2){ piy += 1; mov = true;}
  if(mov == true){ drawcursor(0,cix,ciy);}
  //Grid
  matrix.drawLine(10, 0, 10, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(21, 0, 21, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 10, 31, 10, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 21, 31, 21, matrix.Color333(1, 0, 1));
  //Game State
  
  //Cursor
  drawcursor(1,pix,piy);
    //BTN Pressed
  if(btnState == 0){
    drawcursor(0,pix,piy);
    openspc = openspace(pix,piy);
    if(openspc == true){
      if(turn == true){drawo(pix,piy);}
      else{drawx(pix,piy);}
      turn = !turn;
    }
    else{
      drawcursor(2,pix,piy);
    }
    delay(350);
  }
  drawboard(pix,piy);
  drawcursor(1,pix,piy);
  
  delay(100); // adds some delay between reads
}
