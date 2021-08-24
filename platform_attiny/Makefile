CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
MCU=attiny13
REGS=-ffixed-3 -ffixed-4 -ffixed-5 -ffixed-6 -ffixed-7 -ffixed-8 -ffixed-9
CFLAGS= -Wall -g0 -Os -mmcu=${MCU} -I. -I../src/ -I../fonts ${REGS}

all: main.hex

main.hex: main.o
	${OBJCOPY} -j .text -j .data -O ihex main.o main.hex
	avr-size -C --mcu=${MCU} main.o
	avr-objdump -d main.o > main.asm

main.o: main.c ../src/demo.c ../src/textmode.c
	${CC} ${CFLAGS} -o main.o main.c

flash: main.hex
	${AVRDUDE} -p ${MCU} -P /dev/ttyUSB0 -c avrisp -b 19200 -U flash:w:main.hex:i

clean:
	rm -f *.o *.hex
