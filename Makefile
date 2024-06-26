TARGET = transporte

SRCDIR = ./src/
INCDIR = ./include/

CC = gcc
CFILES = $(foreach D, $(SRCDIR), $(wildcard $(D)*.c))
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = $(foreach D, $(INCDIR), -I$(D))
OBJFILES = $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) -o $@ $^ $(LBFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES)
