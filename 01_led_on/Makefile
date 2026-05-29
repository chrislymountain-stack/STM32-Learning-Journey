TARGET = main

CC = arm-none-eabi-gcc

CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O0
LDFLAGS = -T linker.ld -nostdlib

all:
	$(CC) $(CFLAGS) startup.s main.c $(LDFLAGS) -o $(TARGET).elf
	arm-none-eabi-objcopy -O binary $(TARGET).elf $(TARGET).bin

flash:
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
	-c "program main.elf verify reset exit"

clean:
	rm -f *.o *.elf *.bin

