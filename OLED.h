#ifndef OLED_H
#define OLED_H

#include "Atmega328pPins.h"
#include "Atmega328pTWI.h"
#include "Atmega328pUtil.h"

void oled_command(unsigned char);
void oled_write(unsigned char);
void oled_init();

void oled_clear();
void oled_fill();
#endif