
.SILENT: clean
.IGNORE: clean

CC = g++
LDLIBS = -lcups -lncurses

build: clean
	- mkdir bin
	$(CC) src/main.cpp -o bin/print $(LDLIBS)

clean:
	rm -rf bin
