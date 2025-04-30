#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "game.h"

void level1(GAME *game);
void level2(GAME *game);
void level3(GAME *game);
void level4(GAME *game);
void playLevel(GAME *game);
void update_screen(GAME *game);
void getPositions(GAME *game);
void mouvement_level4(GAME *game);
void teleport_next_door(GAME *game);
void movement(GAME *game);
void movement_npc(GAME *game, int n);
int onTexte(GAME *game);
int collision_cercle(Cercle c1, Cercle c2);
void save_level(GAME *game);
void play_music(Music *musique);
void saving_menu(GAME *game, Dialogue dialogue);
int manage_events(GAME *game, SDL_Event *event);
void movement_level3(GAME *game);  // Changed from struct Game* to GAME*
int collision_fall(GAME *game);    // Changed from struct Game* to GAME*
int onGround(GAME *game, Character character);  // Add this declaration
int collision_pente(GAME *game);
void load_level(GAME *game);

#endif // LEVEL_H_INCLUDED
