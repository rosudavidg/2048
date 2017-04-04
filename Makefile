all: build play clean
build: play_2048
play_2048: main.o
	gcc main.o -o play_2048
main.o: main.c
	gcc -c main.c -o main.o
play:
	./play_2048
clean:
	rm -f main.o play_2048
