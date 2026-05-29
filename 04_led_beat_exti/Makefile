CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O0

LDFLAGS = -T linker.ld -nostdlib

OBJS = startup.o main.o

all: main.bin

startup.o: startup.s
	$(CC) $(CFLAGS) -c startup.s -o startup.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

main.elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o main.elf

main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

flash: main.bin
	st-flash write main.bin 0x8000000

clean:
	rm -f *.o *.elf *.bin

