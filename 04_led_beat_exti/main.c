#include <stdint.h>


//EXTI and AFIO register
#define EXTI_IMR    (*(volatile unsigned long *)0x40010400)  
#define EXTI_FTSR   (*(volatile unsigned long *)0x4001040C)    //Fall edge trigger
#define EXTI_PR      (*(volatile unsigned long *)0x40010414)
#define NVIC_ISER0 (*(volatile unsigned long *)0xE000E100) 
#define AFIO_EXTICR1    (*(volatile unsigned long *)0x40010008)
 
#define RCC_APB2ENR (*(volatile unsigned long *)0x40021018)
#define GPIOA_CRL   (*(volatile unsigned long *)0x40010800) 
#define GPIOC_CRH   (*(volatile unsigned long *)0x40011004)
#define GPIOA_IDR    (*(volatile unsigned long *)0x40010808)
#define GPIOA_ODR (*(volatile unsigned long *)0x4001080C)   
#define GPIOC_ODR   (*(volatile unsigned long *)0x4001100C)     

#define EXTI_FTSR_POS            (1<<0)
#define EXTI_PR_POS              (1<<0)
#define EXTI_IMR_LINE_POS        (1<<0)     //Assume line 13 is the handler      
#define AFIO_EXITCR1_EXTIA0_POS  ~(0b1111<<0)  
#define RCC_APB2ENR_IOPC_POS   (1<<4)                   //IOPC position
#define RCC_APB2ENR_IOPA_POS   (1<<2) 
#define GPIOC_CRH_PC13_POS    20                   //LED pin is PC13 position 20-23.20 is the start position. Mode:0010 general 2mhz output
#define GPIOC_ODR_PC13_POS    13                   //PC13 position of ODR is 13.
 

void EXTI0_Init(void){

  RCC_APB2ENR |=RCC_APB2ENR_IOPA_POS; //turn on the IOPA CRL clock
  RCC_APB2ENR |=(1<<0);               //turn on the AFIO clock
  
  GPIOA_CRL &=~(0b1111<<0);          //Configure the IPOA  
  GPIOA_CRL |=(0b1000<<0);
  GPIOA_ODR |= (1<<0);               //Configure the pullup mode

  AFIO_EXTICR1 &=AFIO_EXITCR1_EXTIA0_POS; //AFIO connect IOPA---EXTI0        
  EXTI_IMR |=EXTI_IMR_LINE_POS;           //EXTI interrup line set
  EXTI_FTSR |=EXTI_FTSR_POS;              // Fall trigger

  NVIC_ISER0 |= (1<<6);                   //Inform NVIC and the position of exti0 is 6.
 
}


void EXTI0_IRQHandler(void){

GPIOC_ODR ^=(1<<GPIOC_ODR_PC13_POS);                // Led on and off
EXTI_PR |=EXTI_PR_POS;                           // Interrup data clear

}


int main(){
  
  RCC_APB2ENR |=(1<<RCC_APB2ENR_IOPC_POS);          //Init clock
  GPIOC_CRH &=~(0b1111<<GPIOC_CRH_PC13_POS);       //Clear GPIOC_CRH  
  GPIOC_CRH |=(0b0010<<GPIOC_CRH_PC13_POS);        //Set 0010 mode
  
  GPIOC_ODR &=~(1<<GPIOC_ODR_PC13_POS);
  EXTI0_Init();  
  
  while(1){

    
  }
   
    
}




