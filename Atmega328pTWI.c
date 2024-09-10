#include "Atmega328pTWI.h"
#include "Atmega328pPins.h"
#include "Atmega328pUtil.h"

unsigned char sla_w;
void twi_init(unsigned char sla, int mode){ // mode = 0 for write, 1 for read
    sla_w = (sla<<1);
    sla_w |= mode;
}

void twi_start_condition(){
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}

void twi_start(){
    twi_start_condition();
    if((TWSR & 0xF8) != START){
        ERROR(0, START);
    }
    twi_sender(sla_w);
    if((TWSR & 0xF8) != MT_SLA_ACK){
        ERROR(sla_w, MT_SLA_ACK);
    }
}

void twi_stop(){
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void twi_send(unsigned char DATA){
    twi_sender(DATA);
    if((TWSR & 0xF8) != MT_DATA_ACK){
        ERROR(DATA, MT_DATA_ACK);
    }
    delay_microsec(1);
}

// used for either starting i2c connection or sending data
// input: sla_w and MT_SLA_ACK to start connection, data being sent and MT_DATA_ACK for sending data
void twi_sender(unsigned char data){
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}


// retry connection. If retries fail, turn on corresponding error LED
void ERROR(unsigned char data, unsigned char ack){
    int retries = 0;
    int max_retries = 10;

    while(retries < max_retries){
        if(ack == START){
            twi_start_condition();
        }
        twi_sender(data);
        
        if((TWSR & 0xF8) == ack){
            return;
        }
        ++retries;
        delay_microsec(1000);
    }

    ERROR_PORT |= (ERROR_LED_1) | (ERROR_LED_2) | (ERROR_LED_3);

    switch(TWSR & 0xF8){
        case 0x20:
            PORTD |= (1<<PD1);
            break;
        case 0x30:
            PORTD |= (1<<PD2);
            break;
        case 0x38:
           PORTD |= (1<<PD3);
           break;
        default:
           PORTD |= (1<<PD1);
           PORTD |= (1<<PD2);
           PORTD |= (1<<PD3);
    }
    return;
}
