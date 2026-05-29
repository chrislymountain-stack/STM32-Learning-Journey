#include <stdio.h>

#define RCC_APB2ENR (*(volatile unsigned long *)0x40021018)  //Find a clock
#define GPIOC_CRH (*(volatile unsigned long *)0x40011004)    //Find GPIOC_CRH 
#define GPIOC_ODR (*(volatile unsigned long *)0x4001100C)    //Find GPIO_ODR

#define RCC_APB2ENR_IOPC_POS 4                        //IOPC position
#define GPIOC_CRH_PC13_POS 20                   //PC13 position is 20-23.20 is the start position. Mode:0010 general 2mhz output
#define GPIOC_ODR_PC13_POS 13                   //PC13 position of ODR is 13.


int main(){

  RCC_APB2ENR |=(1<<RCC_APB2ENR_IOPC_POS);               //Init clock
  GPIOC_CRH &=~(0b1111<<GPIOC_CRH_PC13_POS);       //Clear GPIOC_CRH  
  GPIOC_CRH |=(0b0010<<GPIOC_CRH_PC13_POS);        //Set 0010 mode

  while(1){

    GPIOC_ODR &=~(1<<GPIOC_ODR_PC13_POS);            //LED light
    for(volatile unsigned long i=0;i<1000000;i++){

    }

    GPIOC_ODR |=(1<<GPIOC_ODR_PC13_POS);             //LED close
    for(volatile unsigned long j=0;j<1000000;j++){
    
    }

   }

}


