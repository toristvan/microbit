#include "../accelerometer/accel.h"
#include "pwm.h"
#include "../accelerometer/twi.h"
#include "../accelerometer/utility.h"
#include "../gpiote/gpio.h"
#include "../uart/uart.h"

int main(){

  int prescaler = 3;
  int period = 40000;
  int init_duty = 3000;
  pwm_init(prescaler, period, init_duty);

  uart_init();
  twi_init();
  accel_init();
  int ticks;
  int max_accel = 512;
  int accel_buffer[3];
  int x_acc, y_acc, z_acc;

  int sleep;
  while(1){
    accel_read_x_y_z(accel_buffer);
    x_acc = accel_buffer[0];
    y_acc = accel_buffer[1];
    z_acc = accel_buffer[2];
    utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);

    ticks = (x_acc+max_accel)*2000;
    ticks = ticks / (2*max_accel);
    ticks = ticks + 2000;

    if (ticks > 4000) {
        ticks = 4000;
    }else if (ticks < 2000){
        ticks = 2000;
    }
    pwm_set_ticks(ticks);

    sleep = 1000;
    while(--sleep);
  }
  return 0;
}
