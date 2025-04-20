#ifndef ENEMY_H
#define ENEMY_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define NUM_ENEMIES 2
#define NB_IMG 4

typedef enum {
    ENEMY_ALIVE,
    ENEMY_HURT,
    ENEMY_NEUTRALIZED
} EnemyState;

typedef struct {
    SDL_Rect position;
    SDL_Surface *t[NB_IMG];
    int speed;
    int direction;
    EnemyState state;
    int health;
    int colision;
    int level;
} Enemy;

typedef struct {
    Enemy enemies[NUM_ENEMIES];
    int currentLevel;
} EnemyManager;

typedef struct {
    SDL_Rect pos;
    SDL_Surface *img;
    int collected;
} Coin;

typedef struct {
    SDL_Rect pos;
    SDL_Surface *img;
} Player;

void initEnemies(EnemyManager *manager);
void init2(EnemyManager *manager);
void afficherEnemy(Enemy *enemy, SDL_Surface *screen, int frame);
void animer(EnemyManager *manager, SDL_Surface *screen, int frame);
void updateEnemies(EnemyManager *manager);
void deplacerEnemies(EnemyManager *manager);
void updateEnemyState(Enemy *enemy);
void touch(Enemy *enemy, SDL_Rect playerBB);
void freeEnemies(EnemyManager *manager);

void initCoin(Coin *coin);
void updateCoin(Coin *coin);
void renderCoin(Coin coin, SDL_Surface *screen);
int checkCoinCollision(Coin coin, SDL_Rect player);
void freeCoin(Coin *coin);
void renderCoinCounter(int coinCount, SDL_Surface *screen);

#endif

