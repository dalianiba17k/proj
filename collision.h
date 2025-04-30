#ifndef COLLISIONS_H
#define COLLISIONS_H


#include "game.h"

struct GAME;        // Forward declaration
struct Character;

extern int collision_fall(struct GAME *game);
extern int onGround(struct GAME *game, struct Character perso);
extern int collision_pente(struct GAME *game);
extern int Collision_PPP(struct GAME *game, struct Character perso);

typedef struct 
{
int x,y;
int h,w;
}Box;


typedef struct 
{
int x,y;
int r;
}Cercle;



#endif // COLLISIONS_H
