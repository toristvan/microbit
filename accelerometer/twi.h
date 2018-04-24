#ifndef TWI_H
#define TWI_H
#include <stdio.h>
#include <stdint.h>

#define TWI0 ((NRF_TWI_REG*)0x40003000)

typedef struct {
	/*Taskts*/
  volatile uint32_t STARTRX;
  volatile uint32_t RESERVED00[1];
  volatile uint32_t STARTTX;
  volatile uint32_t RESERVED01[2];
  volatile uint32_t STOP;
  volatile uint32_t RESERVED02[1];
  volatile uint32_t SUSPEND;
  volatile uint32_t RESUME;
  volatile uint32_t RESERVED03[56];
  /*Events*/
  volatile uint32_t STOPPED;
  volatile uint32_t RXDREADY;
  volatile uint32_t RESERVED04[4];
  volatile uint32_t TXDSENT;
  volatile uint32_t RESERVED05[1];
  volatile uint32_t ERROR;
  volatile uint32_t RESERVED06[4];
  volatile uint32_t BB;
  volatile uint32_t RESERVED07[49];
  /*Registers*/
  volatile uint32_t SHORTS;
  volatile uint32_t RESERVED08[63];
  volatile uint32_t INTEN;
  volatile uint32_t INTENSET;
  volatile uint32_t INTENCLR;
  volatile uint32_t RESERVED09[110];
  volatile uint32_t ERRORSRC;
  volatile uint32_t RESERVED10[14];
  volatile uint32_t ENABLE;
  volatile uint32_t RESERVED11[1];
  volatile uint32_t PSELSCL;
  volatile uint32_t PSELSDA;
  volatile uint32_t RESERVED12[2];
  volatile uint32_t RXD;
  volatile uint32_t TXD;
  volatile uint32_t RESERVED13[1];
  volatile uint32_t FREQUENCY;
  volatile uint32_t RESERVED14[24];
  volatile uint32_t ADDRESS;
} NRF_TWI_REG;


void twi_init();

void twi_multi_read(uint8_t slave_address, uint8_t start_register,
  int registers_to_read, uint8_t * data_buffer);

void twi_multi_write(uint8_t slave_address, uint8_t start_register,
  int registers_to_write, uint8_t * data_buffer);
#endif
