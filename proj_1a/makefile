run: mp3
	./mp3
mp3: mp3.o
	gcc mp3.o -o mp3
mp3.o: mp3.c mp3.h
	gcc -c mp3.c
clean:
	rm *.o mp3
val:
	gcc -g mp3.c -o mp3
	valgrind --leak-check=yes ./mp3