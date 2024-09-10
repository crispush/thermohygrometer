-include config.mk

ifndef AVRDUDE_CONFIG_PATH
	$(error AVRDUDE_CONFIG_PATH is not set. Set it in config.mk file.)
endif

ifndef COM
	$(error COM is not set. Set it in config.mk file.)
endif

compileMAIN: main.c
	avr-gcc -mmcu=atmega328p -c main.c -o main.o

compileOLED: OLED.c
	avr-gcc -mmcu=atmega328p -c OLED.c -o OLED.o

compileUTIL: Atmega328pUtil.c
	avr-gcc -mmcu=atmega328p -c Atmega328pUtil.c -o Atmega328pUtil.o

compileTWI: Atmega328pTWI.c
	avr-gcc -mmcu=atmega328p -c Atmega328pTWI.c -o Atmega328pTWI.o

link: OLED.o main.o
	avr-gcc -mmcu=atmega328p main.o OLED.o Atmega328pUtil.o Atmega328pTWI.o -o output.elf

convert: output.elf
	avr-objcopy -O ihex output.elf output.hex

upload: output.hex
	avrdude -C ${AVRDUDE_CONFIG_PATH} -b 19200 -c stk500v1 -p atmega328p -U flash:w:output.hex:i -v -P ${COM}

clean:
	rm OLED.o main.o Atmega328pUtil.o Atmega328pTWI.o 

build: compileMAIN compileOLED compileUTIL compileTWI link convert upload

