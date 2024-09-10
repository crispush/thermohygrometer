#include "Atmega328pTWI.h"

#define PORTD *((volatile unsigned char*) 0x2B)
#define DDRD  *((volatile unsigned char*) 0x2A)

void setup_errors(){
    DDRD = 0x0E;
}

void oled_command(unsigned char cmd){
    twi_start();
    twi_send(0x80); // set command mode
    twi_send(cmd); 
    twi_stop();
    
}

void oled_write(unsigned char data){
    twi_start();
    twi_send(0x40); // set write mode
    twi_send(data);
    twi_stop();
}

void oled_init(){
    twi_init(0x3C, 0);
    setup_errors();
    oled_command(0xAE); // display off

    oled_command(0xA8); // multiplex ratio command
    oled_command(0x3F); // multiplex ratio data

    oled_command(0xD3); // set display offset command
    oled_command(0x00); // set display offset data

    oled_command(0x40); // display start line

    oled_command(0xA1); //  segment re-map

    oled_command(0xC8); // com output and dir normal

    oled_command(0xDA); // set COM Pins
    oled_command(0x12); // setting

    oled_command(0x81); // set contrast control command
    oled_command(0x3F); // set contrast control data

    //command(0xD9); // set pre-charge period
    //command(0x33); // phase 1 = [3:0] and 2 = [7:4]

    oled_command(0xA4); // Entire Display ON, ignore RAM content

    oled_command(0xA6); // set normal display

    oled_command(0xD5); // set display clock settings
    oled_command(0x80); // values divide ratio = [3:0], osc freq = [7:4]

    oled_command(0x8D); // set charge pump setting
    oled_command(0x14); // enable charge pump

    oled_command(0xAF);
}

void oled_clear(){
    oled_command(0x20); // set memory addressing mode
    oled_command(0x00); // set to horizontal addressing mode
    for(int i = 0; i < 1024; i++){
        oled_write(0x00);
    }
}
void oled_fill(){
    oled_command(0x20); // set memory addressing mode
    oled_command(0x00); // set to horizontal addressing mode
    for(int i = 0; i < 1024; i++){
        oled_write(0xFF);
    }
}
