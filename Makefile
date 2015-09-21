CC = gcc
CFLAGS = -O3

HEADERDIR = ./include
SRCFILES = $(wildcard ./**/*.c)
OBJFILES = $(patsubst %.c,%.o, $(SRCFILES))
PROGNAME = shell

.PHONY: all clean

all: $(PROGNAME)

$(PROGNAME): $(OBJFILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS) -I$(HEADERDIR)

clean:
	rm -rf $(OBJFILES) $(PROGNAME)
