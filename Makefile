CC=gcc
CFLAGS=-Wall -Wextra -m32 -Wpedantic

build:
	gcc crypto.c -o crypto
	gcc stocks.c -o stocks
	gcc valley.c -o valley
	gcc ridge.c -o ridge
	gcc trigigel.c -o trigigel

run-p1: 
	./crypto
run-p2:
	./stocks
run-p3:
	./valley
run-p4:
	./ridge
run-p5:
	./trigigel

clean:
	rm -rf crypto stocks valley ridge trigigel

