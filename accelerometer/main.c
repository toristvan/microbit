#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "accel.h"
#include "twi.h"
#include "ubit_led_matrix.h"
#include "utility.h"
#include "../gpiote/gpio.h"
#include "../uart/uart.h"

int main(){
  //WhoIAm?
  uint8_t accelerometer_address = 0x1D;
  uint8_t whoiam_register = 0x0D;
  int registers_to_read = 8;
  uint8_t * data_buffer;
  data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));
  uart_init();
  twi_init();
  twi_multi_read(accelerometer_address,whoiam_register,registers_to_read,data_buffer);
  utility_print(&uart_send, "\n\rI am %d. Nice to meet you.\n\r", data_buffer[0]);
  free(data_buffer);

  // Configure LED Matrix
    for(int i = 4; i <= 15; i++){
  	  GPIO->DIRSET = (1 << i);
  	  GPIO->OUTCLR = (1 << i);
    }
  accel_init();
  int accel_buffer[3];
  int x_acc, y_acc, z_acc;
  ubit_led_matrix_init();
  int x_led, y_led;

  int sleep;
  while(1){
  	accel_read_x_y_z(accel_buffer);
	x_acc = accel_buffer[0];
	y_acc = accel_buffer[1];
	z_acc = accel_buffer[2];
	utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);
	x_led = x_acc / 50;
	if (x_led > 2) {
		x_led = 2;
	}else if (x_led < -2){
		x_led = -2;
	}
	y_led = - y_acc / 50;
	if (y_led > 2) {
		y_led = 2;
	}else if (y_led < -2){
		y_led = -2;
	}
	ubit_led_matrix_light_only_at(x_led, y_led);
	sleep = 1000000;
	while(--sleep);
  }

  return 0;
}
