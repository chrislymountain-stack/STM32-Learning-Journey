#include <stdint.h>


//Systick register
#define SYST_CSR    (*(volatile unsigned long *)0xE000E010)  
#define SYST_RVR    (*(volatile unsigned long *)0xE000E014)
#define SYST_CVR    (*(volatile unsigned long *)0xE000E018)
 

//The registers taking charge of the LED on
#define RCC_APB2ENR (*(volatile unsigned long *)0x40021018)  
#define GPIOC_CRH   (*(volatile unsigned long *)0x40011004)     
#define GPIOC_ODR   (*(volatile unsigned long *)0x4001100C)     


//systick_CSR bit position
#define SYST_CSR_CLK_POS       2
#define SYST_CSR_TICKINT_POS   1
#define SYST_CSR_ENABLE_POS    0 

//GPIOC bit position
#define RCC_APB2ENR_IOPC_POS   4                   //IOPC position
#define GPIOC_CRH_PC13_POS    20                   //LED pin is PC13 position 20-23.20 is the start position. Mode:0010 general 2mhz output
#define GPIOC_ODR_PC13_POS    13                   //PC13 position of ODR is 13.
 
#define SYST_RELOAD      8000000                   // STM32 main clock freq=72Mhz, led on per 0.1 seconds

//Set the programming after Systick finished counting.
//__attribute__((used)) 
void SysTick_Handler(void){

GPIOC_ODR ^=(1<<GPIOC_ODR_PC13_POS);                // Led on and off
}


void systick_init(void){
SYST_CSR=0;
SYST_RVR=SYST_RELOAD-1;
SYST_CVR=0;
SYST_CSR= (1<<SYST_CSR_CLK_POS) | (1<<SYST_CSR_TICKINT_POS) | (1<<SYST_CSR_ENABLE_POS);

}


int main(){
  
  RCC_APB2ENR |=(1<<RCC_APB2ENR_IOPC_POS);          //Init clock
  GPIOC_CRH &=~(0b1111<<GPIOC_CRH_PC13_POS);       //Clear GPIOC_CRH  
  GPIOC_CRH |=(0b0010<<GPIOC_CRH_PC13_POS);        //Set 0010 mode
  
  systick_init();
  
  while(1){

    
  }
   
    
}




