prog: main.o ennemie.o
	gcc main.o ennemie.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

ennemie.o: ennemie.c ennemie.h
	gcc -c ennemie.c -g

main.o: main.c ennemie.h
	gcc -c main.c -g

clean:
	rm -f *.o prog
