
.SILENT: clean
.IGNORE: clean

CC = g++
LDLIBS = -lcups

build:
	mkdir bin
	$(CC) src/main.cpp -o bin/print-function $(LDLIBS)

clean:
	rm -rf bin
