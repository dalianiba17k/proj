#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"perso.h"
#include <time.h>
void initialiser_leon(hero *leon){
		
		leon->afficher_hero[0]=NULL;
		leon->afficher_hero[1]=NULL;
		leon->afficher_hero[2]=NULL;
		leon->afficher_hero[3]=NULL;
		leon->afficher_hero[4]=NULL;
		leon->afficher_hero[5]=NULL;
		leon->afficher_hero[6]=NULL;
		leon->afficher_hero[7]=NULL;
		leon->afficher_hero[8]=NULL;

		leon->afficher_herod[0]=NULL;
		leon->afficher_herod[1]=NULL;
		leon->afficher_herod[2]=NULL;
		leon->afficher_herod[3]=NULL;
		leon->afficher_herod[4]=NULL;
		leon->afficher_herod[5]=NULL;
		leon->afficher_herod[6]=NULL;
		leon->afficher_herod[7]=NULL;
		leon->afficher_herod[8]=NULL;
                
                leon->afficher_hit=NULL;


		leon->afficher_hero[0]=IMG_Load("r1.png");
		leon->afficher_hero[1]=IMG_Load("r2.png");
		leon->afficher_hero[2]=IMG_Load("r3.png");
		leon->afficher_hero[3]=IMG_Load("r4.png");
		leon->afficher_hero[4]=IMG_Load("r5.png");
		leon->afficher_hero[5]=IMG_Load("r6.png");
		leon->afficher_hero[6]=IMG_Load("r7.png");
		leon->afficher_hero[7]=IMG_Load("r8.png");
		leon->afficher_hero[8]=IMG_Load("r9.png");

		leon->afficher_herod[0]=IMG_Load("l1.png");
		leon->afficher_herod[1]=IMG_Load("l2.png");
		leon->afficher_herod[2]=IMG_Load("l3.png");
		leon->afficher_herod[3]=IMG_Load("l4.png");
		leon->afficher_herod[4]=IMG_Load("l5.png");
		leon->afficher_herod[5]=IMG_Load("l6.png");
		leon->afficher_herod[6]=IMG_Load("l7.png");
		leon->afficher_herod[7]=IMG_Load("l8.png");
		leon->afficher_herod[8]=IMG_Load("l9.png");
		      
                leon->afficher_hit=IMG_Load("hit.png");

	
	leon->vie=3;

	leon->farm=0;
	leon->hit=0;
	
	leon->pos_hero2.x=0;
	leon->pos_hero2.y=0;
	leon->pos_vie.y=0;
	leon->pos_vie.x=0;
	leon->heromoved=0;

	leon->vx =leon->vy = 0.0f;
}
void afficher_leon(hero leon, SDL_Surface *ecran) {
    if (leon.mouvment == 1) {
        SDL_BlitSurface(leon.afficher_hero[leon.farm], NULL, ecran, &(leon.pos_hero2));
    } else if (leon.mouvment == 2) {
        SDL_BlitSurface(leon.afficher_herod[leon.farm], NULL, ecran, &(leon.pos_hero2));
    } else if (leon.mouvment == 3) { // Jumping animation
        SDL_BlitSurface(leon.afficher_hero[leon.farm], NULL, ecran, &(leon.pos_hero2));
    } else { // Idle state
        SDL_BlitSurface(leon.afficher_hero[0], NULL, ecran, &(leon.pos_hero2));
    }
}

int animation_perso(hero leon) {
    if (leon.mouvment == 1 || leon.mouvment == 2) {
        if (leon.farm < 8) {
            leon.farm++;
        } else {
            leon.farm = 0;
        }
    } else if (leon.mouvment == 3) { // Jumping animation
        // Update jump animation frames here if needed
        if (leon.farm < 8) {
            leon.farm++;
        } else {
            leon.farm = 0;
        }
    } else { // Idle state
        leon.farm = 0;
    }
    return leon.farm;
}

