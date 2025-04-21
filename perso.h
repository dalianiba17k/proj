#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <unistd.h>

typedef struct hero
{
	int mouvment,mouvment2;
	SDL_Surface *afficher_hero[9];
	SDL_Surface *afficher_herod[9];
        SDL_Surface *afficher_hit;
        SDL_Rect pos_hero[9];
	SDL_Rect pos_hero2;
	int farm,farm2;
        int hit;
	int heromoved;
	int vie;
        SDL_Rect pos_vie;
	SDL_Surface *afficher_vie[3];
	int score;
	SDL_Surface *afficher_score;
	

	float vx;
	float vy;
	float x;
	float y;
	
}hero;

#endif
