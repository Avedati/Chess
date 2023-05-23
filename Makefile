CC=gcc
CFLAGS=-std=c11 `pkg-config --cflags --libs SDL2` -lSDL2_ttf -lSDL2_image
TARGETS=src/*.c
OUT=bin/c_chess

all:
	$(CC) $(CFLAGS) $(TARGETS) -o $(OUT)

clean:
	rm -rf bin/*
	rm -f .DS_Store

debug:
	$(CC) -g $(CFLAGS) $(TARGETS) -o $(OUT)

test:
	$(MAKE) all
	./$(OUT)
	$(MAKE) clean
