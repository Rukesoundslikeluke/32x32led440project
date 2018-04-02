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
int board[3][3] = {0,0,0,0,0,0,0,0,0};
bool openspc = true;
bool turn = false;  //false = X turn
int turnNum = 0;
bool fixer = false;

//How the rgb board works
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

//MESSAGES
void drawgame(){  //Prints draw in middle of screen
  turnNum = 0;
  fillboard(0);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(4, 11);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(1,1,1));
  matrix.println("DRAW");
  delay(2100);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}
void owin(){  //Prints O WIN in middle of screen
  turnNum = 0;
  fillboard(0);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 11);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(1,1,1));
  matrix.println("O WIN");
  delay(2100);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}
void xwin(){  //Prints X WIN in middle of screen
  turnNum = 0;
  fillboard(0);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 11);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.println("X WIN");
  delay(2100);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

//GAME STATE FUNCTIONS
// 0 = free
// 1 = X
// 2 = O
// For these functions use above as a key when you see c as an arguement
 bool openspace(int x,int y){
  if(board[x][y] == 0){ return true;}
  return false;
 }
 void mark(int c,int x,int y){  //marks a spot on the game board array
    if(c == 1){board[x][y] = 1;}
    else if(c == 2){board[x][y] = 2;}
    else{board[x][y] = 0;}
 }
 bool checkwin(){//lazy way to check for win state
  //HORIZONTAL SECTION
  if(board[0][0] == board[1][0] && board[1][0] == board[2][0]&& board[0][0] != 0){
    matrix.drawRect(0, 4, 31, 2, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  if(board[0][1] == board[1][1] && board[1][1] == board[2][1]&& board[0][1] != 0){
    matrix.drawRect(0, 15, 31, 2, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  if(board[0][2] == board[1][2] && board[1][2] == board[2][2]&& board[0][2] != 0){
    matrix.drawRect(0, 26, 31, 2, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  //VERTICAL SECTION
  if(board[0][0] == board[0][1] && board[0][1] == board[0][2]&& board[0][0] != 0){
    matrix.drawRect(4, 0, 2, 31, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  if(board[1][0] == board[1][1] && board[1][1] == board[1][2]&& board[1][0] != 0){
    matrix.drawRect(15, 0, 2, 31, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  if(board[2][0] == board[2][1] && board[2][1] == board[2][2]&& board[2][0] != 0){
    matrix.drawRect(26, 0, 2, 31, matrix.Color333(1, 1, 1));
    delay(400);
    return true;
  }
  //DIAGONAL SECTION;
  if(board[0][0] == board[1][1] && board[1][1] == board[2][2]&& board[0][0] != 0){
    matrix.drawLine(0, 0, 31, 31, matrix.Color333(7, 0, 7));
    delay(400);
    return true;
  }
  if(board[0][2] == board[1][1] && board[1][1] == board[2][0]&& board[0][2] != 0){
    matrix.drawLine(0, 31, 31, 0, matrix.Color333(7, 0, 7));
    delay(400);
    return true;
  }
  return false;
 }
 void fillboard(int c){ //Fills board array with given number
  for(int i = 0;i<9;++i){
    for(int j =0;j<9;++j){
    mark(c,i,j);
   }
  }
 }
 void movecursor(){
  mov = false;//determines if the cursor has moved
  cix = pix; //prev cursor position
  ciy = piy;
  if(xPos <= 25 && pix > 0)   { pix -= 1; mov = true;}
  if(xPos >= 1000 && pix < 2){ pix += 1; mov = true;}
  if(yPos <= 25 && piy > 0)   { piy -= 1; mov = true;}
  if(yPos >= 1000 && piy < 2){ piy += 1; mov = true;}
  if(mov == true){ drawcursor(0,cix,ciy);}  //if cursor moved then "erase" prev cursor position
 }

//DRAW FUNCTIONS
//Think of drawing as a normal array 
//i.e. drawx(0,1) - > | |x| |
//                    | | | |
//                    | | |o| < - drawo(2,2)
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
void drawcursor(int d, int x, int y){ // d = color option (0 -> red |1 -> green)
  int xcoord = 0, ycoord = 0;
  if(x == 1){ xcoord+= 11;}
  else if(x == 2){ xcoord+=22;}
  if(y == 1){ ycoord+= 11;}
  else if(y == 2){ycoord+= 22;}
  if(d == 0){ matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(0, 0, 0));}
  else if(d == 2){matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(7, 0, 0));}
  else{ matrix.drawRect(xcoord, ycoord, 10, 10, matrix.Color333(0, 1, 0));}
 }
void drawgrid(){
  matrix.drawLine(10, 0, 10, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(21, 0, 21, 31, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 10, 31, 10, matrix.Color333(1, 0, 1));
  matrix.drawLine(0, 21, 31, 21, matrix.Color333(1, 0, 1));
}
void drawboard(int x, int y){
  drawgrid();
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
// initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  //activate pull-up resistor on the push-button pin
  pinMode(BTN, INPUT_PULLUP);
}


void loop() {
  xPos = analogRead(XPIN);//Read joystick x coordinate
  yPos = analogRead(YPIN);//Read joystick y coordinate
  btnState = digitalRead(BTN);//Read button input
  movecursor();//Cursor movement
  
  if(btnState == 0){//BTN Pressed
    drawcursor(0,pix,piy);        //Hide cursor
    openspc = openspace(pix,piy); //Check if spot is taken
    if(openspc == true){
      if(turn == true){drawo(pix,piy);}
      else{drawx(pix,piy);}
      turnNum++;
      if(checkwin() == true){
        if(turn == true){owin();}//O WIN
        if(turn == false){xwin();}//X WIN
        turn = true;
        fixer = true;
      }
      else if(turnNum == 9){//DRAW
        drawgame();
        fixer = true;
      }
      turn = !turn;
    }
    else{
      drawcursor(2,pix,piy);
    }
    delay(350);
  }
  if(fixer == true){//Made this to avoid cursor drawing after a win or draw
    fixer = false;
    pix = 1;
    piy = 1;
  }
  if(fixer == false){
    drawboard(pix,piy);
    drawcursor(1,pix,piy);
  }
 
  
  delay(100); // adds some delay between reads
}
