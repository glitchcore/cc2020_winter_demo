DEVICE = attiny85
CLOCK = 8000000
PROGRAMMER = -c avrisp

# for ATTiny85
# see http://www.engbedded.com/fusecalc/
FUSES       = -U lfuse:w:0xc1:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) -P /dev/ttyACM0 -b 19200
COMPILE = avr-gcc -Wall -O0 -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

TARGET = demo

SOURCES_DIR = .
BUILD_DIR = build

C_SOURCES =  \
main.c \
../src/demo.c \
..src/textmode.c


C_INCLUDES = \
-I. \
-I../src/ \
-I../fonts

CC = gcc

LDFLAGS = 

all: $(BUILD_DIR)/$(TARGET).hex

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(COMPILE) -c $(C_INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) Makefile
	$(COMPILE) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(COMPILE) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	rm -f $@
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size --format=avr --mcu=$(DEVICE) $<

clean:
	-rm -fR .dep $(BUILD_DIR)

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -U flash:w:$^:i

fuse:
	$(AVRDUDE) $(FUSES)

# Targets for code debugging and analysis:
disasm:	$(BUILD_DIR)/$(TARGET).elf
	avr-objdump -d $@
