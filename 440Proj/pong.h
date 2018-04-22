#ifndef PONG_H
#define PONG_H
#include <Globals.h>

//Prototypes
    void moveplayers();
    void drawplayers(int,int,int);
    void moveball();
    void drawball(int);
    void win(int);
int xPos1 = 0;
int yPos1 = 0;
int btnState1 = 0;
int xPos2 = 0;
int yPos2 = 0;
int btnState3 = 0;

int psize = 5;  //paddle size
int pspeed = 2; //paddle speed

int  p1score = 0;
int  p2score = 0;
int  p1pos = 13;    //p1 position
int  p1posx;        //p1 past position
bool p1mov = false; //Check for p1 movement
int  p2pos = 13;    //p2 position
int  p2posx;        //p2 past position
bool p2mov = false; //Check for p2 movement

int bspeed = 75;//ballspeed
int ballx = 14; //ball x coordinate
int bally = 14; //ball y coordinate
int bcheck = 0;

int anglex = -1;
int angley = random(0,2);

void moveplayers(){ //Handles moving indidual players
    xPos1 = analogRead(XPIN);     //Read joystick x coordinate
    yPos1 = analogRead(YPIN);     //Read joystick y coordinate
    btnState1 = digitalRead(BTN); //Read button input
    xPos2 = analogRead(XPIN2);
    yPos2 = analogRead(YPIN2);
    btnState3 = digitalRead(BTN2);
    p2posx = p2pos;//used to erase old location
    p1posx = p1pos;
    //Checking if players are moving
    if(yPos1 > 1000 && p1pos+psize < 30){p1pos += pspeed;p1mov = true;}
    else if(yPos1 > 600 && p1pos+psize < 30){p1pos += 1;p1mov = true;}
    if(yPos1 < 30 && p1pos > 1){p1pos -= pspeed;p1mov = true;}
    else if(yPos1 < 480 && p1pos > 1){p1pos -= 1;p1mov = true;}
    if(yPos2 > 1000 && p2pos+psize < 30){p2pos += pspeed;p2mov = true;}
    else if(yPos2 > 600 && p2pos+psize < 30){p2pos += 1;p2mov = true;}
    if(yPos2 < 30 && p2pos > 1){p2pos -= pspeed;p2mov = true;}
    else if(yPos2 < 480 && p2pos > 1){p2pos -= 1;p2mov = true;}
    
    //Erases last position before drawing new one
    if(p1mov == true){drawplayers(0,p1posx,1);p1mov = false;}
    if(p2mov == true){drawplayers(0,p2posx,30);p2mov = false;}
    //Draws new position
    drawplayers(1,p1pos,1);
    drawplayers(1,p2pos,30);
}
void drawplayers(int d,int x,int p){ //d = drawmode x = player position p = player column
    if(d == 0){ matrix.drawLine(p,x,p,x+psize,matrix.Color333(0, 0, 0));}
    else{matrix.drawLine(p,x,p,x+psize,matrix.Color333(3, 3, 3));}
}
void moveball(){ //Handles moving the ball across screen
    drawball(0);//erase old ball location
    //Top and bottom Bounds
    if(bally <= 1 || bally >=30){
        angley *= -1;
    }
    if((bally == 2 || bally == 29)&&(angley == 2 || angley == -2)){
        angley *= -1;
    }
  
    ballx += anglex;//add next x movement
    bally += angley;//add next y movement
    bcheck = bally + angley;
  
    if(ballx == 2){ //p1 bounds
        if ((bcheck >= p1pos&& bcheck <= p1pos + psize)||(bally >= p1pos && bally <=p1pos+psize)){
            //Top of paddle
            if(bcheck < p1pos +2){
                if(angley == -1){angley = -2;}
                else{angley = -1;}
            }
            //Middle of paddle
            else if(bcheck < p1pos +4){bspeed -= 10;}
            //Bottom of paddle
            else if(bcheck < p1pos +6){
                if(angley == 1){angley = 2;}
                else{angley = 1;}
            }
            anglex *= -1;
        }
    }
    if(ballx == 29){ //p2 bounds
        if(bcheck >= p2pos && bcheck <= p2pos + psize||(bally >= p2pos && bally <=p2pos+psize)){
            //Top of paddle
            if(bcheck < p2pos +2){
                if(angley == -1){angley = -2;}
                else{angley = -1;}
            }
            //Middle of paddle
            else if(bcheck < p2pos +4){bspeed -= 10;}
            //Bottom of paddle
            else if(bcheck < p2pos +6){
                if(angley == 1){angley = 2;}
                else{angley = 1;}
            }
            anglex *= -1;
        }
    }
    drawball(1);
}
void drawball(int d){ //Draws the ball
    matrix.drawRect(2,1,28,30,matrix.Color333(0,0,0));
    if(d == 0){matrix.drawPixel(ballx,bally,matrix.Color333(0, 0, 0));}
    else{matrix.drawPixel(ballx,bally,matrix.Color333(0, 2, 2));}
}
void win(int x){ //Win state based off of given x
    if(x == 1){//p1 wins
        matrix.drawLine(31,1,31,30,matrix.Color333(0,3,0));
        p1score++;
        lcd.setCursor(9, 0);
        lcd.print(p1score);
    }
    else if(x == 2){//p2wins
        matrix.drawLine(0,1,0,30,matrix.Color333(0,3,0));
        p2score++;
        lcd.setCursor(9, 1);
        lcd.print(p2score);
    }
    delay(700);
    //Clear goals
    matrix.drawLine(0,1,0,30,matrix.Color333(0,0,0));
    matrix.drawLine(31,1,31,30,matrix.Color333(0,0,0));
    if(random(2) == 1){anglex = 1;}
    else{anglex = -1;}
    if(random(2) == 1){angley = -1;}
    else{angley = 1;}
    drawplayers(0,p1pos,1);
    drawplayers(0,p2pos,30);
    p1pos = 13;
    p2pos = 13;
    drawplayers(1,p1pos,1);
    drawplayers(1,p2pos,30);
    ballx = 14;
    bally = 14;
    bspeed = 75;
    drawball(1);
    delay(800);
}
void pong(){
    p1score = 0;
    p2score = 0;
    if(random(1) == 1){anglex = 1;}
    lcd.setCursor(0, 0);
    lcd.print("Player 1:");
    lcd.setCursor(0, 1);
    lcd.print("Player 2:");
    matrix.drawLine(2,0,29,0,matrix.Color333(2,0,2));
    matrix.drawLine(2,31,29,31,matrix.Color333(2,0,2));
    while(p1score < 3 && p2score < 3){
        
        if(ballx < 1){win(2);}
        if(ballx >30){win(1);}
        moveplayers();
        moveball();
        delay(bspeed);
    }
}
#endif