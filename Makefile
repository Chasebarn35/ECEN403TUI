CC=g++
CFLAGS= -lncurses

all: freqtui

freqtui: main.cpp
	$(CC) $(CFLAGS) main.cpp -o freqtui
clean:
	rm -f freqtui
