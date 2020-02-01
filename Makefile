
TARGET = demo

SOURCES_DIR = .
BUILD_DIR = build

C_SOURCES =  \
demo.c \
main.c

C_INCLUDES = \
-I.

CC = gcc

LDFLAGS = 


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(C_INCLUDES) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR .dep $(BUILD_DIR)

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
