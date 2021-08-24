
TARGET = demo

SOURCES_DIR = .

C_INCLUDES = \
-I. \
-I../src \
-I../fonts

CC = gcc

LDFLAGS = 

$(TARGET): main.c ../src/demo.c Makefile
	$(CC) $(C_INCLUDES) $(LDFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
