prog: main.o perso.o 
	gcc  perso.o main.o  -o prog -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c

perso.o:perso.c
	gcc -c perso.c

