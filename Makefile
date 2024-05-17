CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -Wpedantic
LDFLAGS := -static

clkdump: clkdump.o

clean:
	$(RM) clkdump clkdump.o
