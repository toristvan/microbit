#include "twi.h"
#include "../gpiote/gpio.h"


void twi_init(){
  TWI0->PSELSCL=0;
  TWI0->PSELSDA=30;
  GPIO->PIN_CNF[0]=0x0000060C;//(1<<2)|(1<<3)|(1<<9)|(1<<10);//
  GPIO->PIN_CNF[30]=0x0000060C;//(1<<2)|(1<<3)|(1<<9)|(1<<10);//
  TWI0->RXDREADY = 0;
  TWI0->TXDSENT=0;
  TWI0->ERROR=0;
  TWI0->FREQUENCY=0x01980000;
  TWI0->ENABLE=5;
}

void twi_multi_read(uint8_t slave_address, uint8_t start_register,
  int registers_to_read, uint8_t * data_buffer){
    TWI0->ADDRESS=slave_address;
    TWI0->STARTTX=1;

    TWI0->TXDSENT = 0;
    TWI0->TXD = start_register;
    while(!TWI0->TXDSENT);

    TWI0->RXDREADY=0;
    TWI0->STARTRX=1;
    for (int i=0;i<registers_to_read-1;i++){
      while(!TWI0->RXDREADY);
      TWI0->RXDREADY=0;
      data_buffer[i]=TWI0->RXD;
    }
    TWI0->STOP=1;
    while(!TWI0->RXDREADY);
    data_buffer[registers_to_read-1]=TWI0->RXD;
    TWI0->RXDREADY=0;
  }

void twi_multi_write(uint8_t slave_address, uint8_t start_register,
    int registers_to_write, uint8_t * data_buffer){
    TWI0->ADDRESS=slave_address;
    TWI0->STARTTX=1;

    TWI0->TXDSENT=0;
    TWI0->TXD=start_register;
    while(!TWI0->TXDSENT);

    for (int i=0; i<registers_to_write;i++){
      TWI0->TXDSENT=0;
      TWI0->TXD=data_buffer[i];
      while(!TWI0->TXDSENT);
    }
    TWI0->STOP=1;
  }
