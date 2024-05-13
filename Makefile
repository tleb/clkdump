CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -Wextra -Wpedantic

clkdump: clkdump.o

clean:
	$(RM) clkdump clkdump.o
