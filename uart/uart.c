#include "uart.h"
#include "gpio.h"
#include <stdint.h>

#define UART ((NRF_UART_REG*)0x40002000)
#define BAUD9600 (0x00275000) 
#define DISCONNECT (0xFFFFFFFF)

typedef struct{
  volatile uint32_t STARTRX;
  volatile uint32_t STOPRX;
  volatile uint32_t STARTTX;
  volatile uint32_t STOPTX;
  volatile uint32_t RESERVED0[3];
  volatile uint32_t SUSPEND;
  volatile uint32_t RESERVED1[56];
  volatile uint32_t CTS;
  volatile uint32_t NCTS;
  volatile uint32_t RXDRDY;
  volatile uint32_t RESERVED2[4];
  volatile uint32_t TXDRDY;
  volatile uint32_t RESERVED3;
  volatile uint32_t ERROR;
  volatile uint32_t RESERVED4[7];
  volatile uint32_t RXTO;
  volatile uint32_t RESERVED5[110];
  volatile uint32_t INTEN;
  volatile uint32_t INTENSET;
  volatile uint32_t INTENCLR;
  volatile uint32_t RESERVED6[93];
  volatile uint32_t ERRORSRC;
  volatile uint32_t RESERVED7[31];
  volatile uint32_t ENABLE;
  volatile uint32_t RESERVED8;
  volatile uint32_t PSELRTS;
  volatile uint32_t PSELTXD;
  volatile uint32_t PSELCTS;
  volatile uint32_t PSELRXD;
  volatile uint32_t RXD;
  volatile uint32_t TXD;
  volatile uint32_t RESERVED9;
  volatile uint32_t BAUDRATE;
  volatile uint32_t RESERVED10[17];
  volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
	GPIO->DIRSET=(1<<24);
	GPIO->DIRCLR=(1<<25);

	UART->PSELTXD=24;
	UART->PSELRXD=25;

	UART->BAUDRATE=BAUD9600;

	UART->PSELCTS=DISCONNECT;
	UART->PSELRTS=DISCONNECT;

	UART->ENABLE=0x4;
	UART->STARTRX=0x1;
}

void uart_send(char letter){
  UART->TXDRDY=0x0;
  UART->STARTTX=0x1;
	UART->TXD=letter;
	while (!UART->TXDRDY){};
  UART->TXDRDY=0x0;
	UART->STOPTX=0x1;
}

char uart_read(){
	char ret='\0';
	if(UART->RXDRDY){
		UART->STARTRX=0x1;
		ret=UART->RXD;
		UART->STOPRX=0x1;
	}
	return ret;
}