#ifndef ATMEGA328PTWI_H
#define ATMEGA328PTWI_H
#include "Atmega328pPins.h"

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_DATA_ACK 0x28

#define TWCR *((volatile unsigned char*) 0xBC)
#define TWDR *((volatile unsigned char*) 0xBB)
#define TWSR *((volatile unsigned char*) 0xB9)

#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0

void twi_init(unsigned char, int);
void twi_start_condition();
void twi_start();
void twi_stop();
void twi_send(unsigned char);
void twi_sender(unsigned char);
void ERROR(unsigned char, unsigned char);
#endif