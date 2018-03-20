#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define MASK_BTN_A (1<<17)
#define MASK_BTN_B (1<<26)



typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0; //A skrur av
	GPIO->PIN_CNF[26] = 0; //B skruv paa


	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & MASK_BTN_B)){
			GPIO->OUTCLR=(1<<13);
			GPIO->OUTCLR=(1<<14);
			GPIO->OUTCLR=(1<<15);
		}

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		//else if((GPIO->IN & GPIO->PIN_CNF[17])!=GPIO->PIN_CNF[17]){
		else if(!(GPIO->IN & MASK_BTN_A)){
			GPIO->OUTSET=(1<<13);
			GPIO->OUTSET=(1<<14);
			GPIO->OUTSET=(1<<15);
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
