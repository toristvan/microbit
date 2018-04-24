#include "gpiote.h"
#include "gpio.h"
#include "ppi.h"
#include <stdint.h>

int main(){

  //configure LED matrix
  for (int i=4;i<=15;i++){
    GPIO->DIRSET=(1<<i);
    GPIO->OUTCLR=(1<<i);
  }
  /*
  GPIOTE->CONFIG[0]=(13<<8)&&(3<<0)&&(3<<16);
  GPIOTE->CONFIG[1]=(14<<8)&&(3<<0)&&(3<<16);
  GPIOTE->CONFIG[2]=(15<<8)&&(3<<0)&&(3<<16);
  //A button
  GPIOTE->CONFIG[3]=(17<<8)&&(1<<0)&&(2<<16);
  */
  GPIOTE->CONFIG[0] = 0x00030D03;
  GPIOTE->CONFIG[1] = 0x00030E03;
  GPIOTE->CONFIG[2] = 0x00030F03;
  //A button
  GPIOTE->CONFIG[3] = 0x00021101;

  PPI->CHENSET=(7<<0);
  PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[0]);
  PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[1]);
  PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[3]);
  PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[2]);

  int sleep=0;
  while(1){
    sleep=10000;
    while(--sleep);
  }
  return 0;
}
