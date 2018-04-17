#include "uart.h"
#include "gpio.h"

#define MSK_BTN_A (1<<17)
#define MSK_BTN_B (1<<26)

int main(){
	GPIO->PIN_CNF[17]=0;
	GPIO->PIN_CNF[26]=0;

	uart_init();
	int sleep=0;
	while(1){
		if(!(GPIO->IN & MSK_BTN_A)){
			uart_send('A');
		}else if(!(GPIO->IN & MSK_BTN_B)){
			uart_send('B');
		}
		sleep=1000;
		while(--sleep);
	}
	return 0;

}