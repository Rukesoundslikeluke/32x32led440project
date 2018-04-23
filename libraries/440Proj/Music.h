#ifndef MUSIC_H
#define MUSIC_H
#include <Globals.h>

static int8_t Send_buf[8] = {0} ;
static uint8_t ansbuf[10] = {0};

void sendCommand(int8_t command, int16_t dat){
    delay(20);
    Send_buf[0] = 0x7e; //starting byte
    Send_buf[1] = 0xff; //version
    Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
    Send_buf[3] = command; //
    Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
    Send_buf[5] = (int8_t)(dat >> 8);//datah
    Send_buf[6] = (int8_t)(dat); //datal
    Send_buf[7] = 0xef; //ending byte
    for(uint8_t i=0; i<8; i++){
        mp3.write(Send_buf[i]) ;
    }
}
#endif