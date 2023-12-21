CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm

all: colorb iotest

colorb: colorb.c bmp.c io.c io.h bmp.h
        $(CC) $(CFLAGS) -o colorb colorb.c bmp.c io.c $(LFLAGS)

iotest: iotest.c io.c io.h
        $(CC) $(CFLAGS) -o iotest iotest.c io.c $(LFLAGS)

clean:
        rm -f colorb iotest *.o
format:
        clang-format -i *.c *.h

.PHONY: all clean format
