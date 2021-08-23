CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
MCU=attiny13
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -I. -I../src/ -I../fonts

all: main.hex

main.hex: main.o
	${OBJCOPY} -j .text -j .data -O ihex main.o main.hex
	avr-size -C --mcu=${MCU} main.o

main.o: main.c ../src/demo.c
	${CC} ${CFLAGS} -o main.o main.c ../src/demo.c

flash: main.hex
	${AVRDUDE} -p ${MCU} -P /dev/ttyUSB0 -c avrisp -b 19200 -U flash:w:main.hex:i

clean:
	rm -f *.o *.hex
