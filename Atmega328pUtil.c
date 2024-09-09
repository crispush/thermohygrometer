#include "Atmega328pUtil.h"

void delay_sec(volatile int n){
    int delay = (CPU_FREQUENCY / 3) * n;
    while(--delay){}
}

void delay_microsec(volatile long int n){
    long int delay = (CPU_FREQUENCY / 3000000) * n; // estimate 13 clock cycles per iteration
    while(--delay){}
}

