#include "Atmega328pPins.h"
#include "Atmega328pUtil.h"
#include "OLED.h"

#define CPU_FREQUENCY 16000000UL
void setup();
void loop();


int main(){
    setup();

    return 0;
}

void setup(){
    delay_microsec(100);
    oled_init();
    oled_fill();
}

void loop(){

    
}

