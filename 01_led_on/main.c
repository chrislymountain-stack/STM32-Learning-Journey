#include <stdint.h>

#define RCC_APB2ENR (*(volatile unsigned long *)0x40021018) //Find APB2ENR Clock address 
#define GPIOC_CRH    (*(volatile unsigned long *)0x40011004) //Find a register controlling address 
#define GPIOC_ODR    (*(volatile unsigned long *)0x4001100C) //Find data out register controlling address

int main()

{

RCC_APB2ENR |= (1<<4);   // Give the clock drive
GPIOC_CRH &=~(0xF<<20);   //Init GPIO_CRH Set O000b for CRH of C13 pin 
GPIOC_CRH |=(0x2<<20);    // Set control mode for 0010 General-2Mhz
GPIOC_ODR &=~(0x1<<13);   // GPIO_ODR 13st pin --1

while(1)
{

}                        // Focus on this program.


}



