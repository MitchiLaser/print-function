
.SILENT: clean
.IGNORE: clean
.PHONY: debug build clean

CC = g++
LDLIBS = -lcups -lncurses

debug: $(shell find . -name '*.cpp')
	- mkdir bin
	$(CC) src/main.cpp -o bin/print $(LDLIBS) -D LOG_LEVEL=LOG_DEBUG

build: $(shell find . -name '*.cpp')
	- mkdir bin
	$(CC) src/main.cpp -o bin/print $(LDLIBS) -D LOG_LEVEL=LOG_NOLOG

clean:
	rm -rf bin
