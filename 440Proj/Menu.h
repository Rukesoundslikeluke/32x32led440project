#ifndef MENU_H
#define MENU_H
#include <Globals.h>
//Mapping for joystick
int mxPos = 0;
int myPos = 0;
int mbtnState = 0;
// movement
int mpiy = 0;
int mciy = 0;
bool mmov = false;
//MENU FUNCTIONS
void drawmenucursor(int d, int y){ // d = color option (0 -> blank |1 -> green)
    int ycoord1 = 0, ycoord2 = 0;
    if(y == 0){ 
        ycoord2+= 9;
    }
    else if(y == 1){
        ycoord1+=11;
        ycoord2+=20;
    }
    else if(y == 2){
        ycoord1+=22;
        ycoord2+=31;
    }
    if(d == 0){
        matrix.drawLine(0, ycoord1, 31, ycoord1, matrix.Color333(0, 0, 0));
        matrix.drawLine(0, ycoord2, 31, ycoord2, matrix.Color333(0, 0, 0));
    }
    else if (d == 1){
        matrix.drawLine(0, ycoord1, 31, ycoord1, matrix.Color333(0, 1, 0));
        matrix.drawLine(0, ycoord2, 31, ycoord2, matrix.Color333(0, 1, 0));
    }
}
void movemenucursor(){
    mmov = false;//determines if the cursor has moved
    mciy = mpiy;
    if(myPos <= 25 && mpiy > 0)   { mpiy -= 1; mmov = true;}
    if(myPos >= 1000 && mpiy < 2){ mpiy += 1; mmov = true;}
    if(mmov == true){ 
        drawmenucursor(0,mciy);
    }  //if cursor moved then "erase" prev cursor position
    drawmenucursor(1,mpiy);
}

int menu(){
    matrix.fillScreen(matrix.Color333(0,0,0));
    lcd.setCursor(0,0);
    lcd.print("Made by:Michael,");
    lcd.setCursor(0,1);
    lcd.print("Fernando,Marcus!");
    matrix.setCursor(1, 1);
    matrix.print("T-T-T");
    matrix.setCursor(1, 12);
    matrix.print("Pong");
    matrix.setCursor(1, 23);
    matrix.print("Sleep");
    while (true){
        mxPos = analogRead(XPIN);//Read joystick x coordinate
        myPos = analogRead(YPIN);//Read joystick y coordinate
        mbtnState = digitalRead(BTN);//Read button input
        movemenucursor();
        if(mbtnState == 0){
            drawmenucursor(0,mpiy);
            if(mpiy == 0){
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                mpiy = 1;
                pix = 1;
                lcd.clear();
                delay(300);
                return 0;
            }
            else if(mpiy == 1){
                matrix.fillScreen(matrix.Color333(0, 0, 0));
                mpiy = 1;
                pix = 1;
                lcd.clear();
                delay(300);
                return 1;
            }
        }
        delay(100); // adds some delay between reads
    }
}
#endif