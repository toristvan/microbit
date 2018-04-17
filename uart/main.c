#include "uart.h"
#include "gpio.h"
#include "stdio.h"

#define MSK_BTN_A (1<<17)
#define MSK_BTN_B (1<<26)

ssize_t _write(int fd, const void *buf, size_t count){
	char* letter=(char*)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

ssize_t _read(int fd, void *buf, size_t count){
	char *str = (char *)(buf);
	char letter;
	do {
		letter = uart_read();
	} while(letter == '\0');
	*str = letter;
	return 1;
} //for firvillig opgave 4.7

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	GPIO->PIN_CNF[17]=0;
	GPIO->PIN_CNF[26]=0;

	uart_init();
	int sleep=0;
	int led=0;
	while(1){
		if(!(GPIO->IN & MSK_BTN_A)){
			//uart_send('A');
			iprintf("Norway has %d counties.\n\r",18);
			while(!(GPIO->IN & MSK_BTN_A)){};
		}else if(!(GPIO->IN & MSK_BTN_B)){
			uart_send('B');
			while(!(GPIO->IN & MSK_BTN_B)){};
		}
		if(uart_read()!='\0'){
			if(led){
				GPIO->OUTSET=(1<<13);
				GPIO->OUTSET=(1<<14);
				GPIO->OUTSET=(1<<15);
				led=0;
			}else{
				GPIO->OUTCLR=(1<<13);
				GPIO->OUTCLR=(1<<14);
				GPIO->OUTCLR=(1<<15);
				led=1;
			}

		}
		sleep=1000;
		while(--sleep);
	}
	return 0;

}