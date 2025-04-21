#include "ennemie.h"
#include <stdlib.h>

int intersects(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x && b.x + b.w > a.x &&
            a.y + a.h > b.y && b.y + b.h > a.y);
}

void initEnemies(EnemyManager *manager) {
    manager->currentLevel = 1;

    Enemy *e = &manager->enemies[0];
    e->pos.x = 100;
    e->pos.y = 300;
    e->pos.w = 129;
    e->pos.h = 167;
    e->speed = 1;
    e->direction = -1;
    e->state = ENEMY_ALIVE;
    e->health = 100;
    e->colision = 0;
    e->level = 1;

    SDL_Surface *sheet = IMG_Load("55555.png");
    if (!sheet) {
        printf("Erreur chargement sprite sheet: %s\n", IMG_GetError());
        return;
    }

    for (int i = 0; i < NB_IMG; i++) {
        e->t[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 129, 167, 32, 0, 0, 0, 0);
        SDL_Rect src = { i * 129, 0, 129, 167 };
        SDL_BlitSurface(sheet, &src, e->t[i], NULL);
    }

    SDL_FreeSurface(sheet);

    init2(manager); // initialise le deuxième ennemi
}

void init2(EnemyManager *manager) {
    Enemy *e = &manager->enemies[1];
    e->pos.x = 400;
    e->pos.y = 300;
    e->pos.w = 118;
    e->pos.h = 200;
    e->speed = 3;
    e->direction = -1;
    e->state = ENEMY_ALIVE;
    e->health = 100;
    e->colision = 0;
    e->level = 2;

    SDL_Surface *sheet = IMG_Load("8888.png");
    for(int i = 0; i < NB_IMG2; i++) {
        e->t[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 118, 200, 32, 0, 0, 0, 0);
        SDL_Rect src = {i * 118, 0, 118, 118};
        SDL_BlitSurface(sheet, &src, e->t[i], NULL);
    }
    SDL_FreeSurface(sheet);
}

void deplacerEnemies(EnemyManager *manager) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        Enemy *e = &manager->enemies[i];
        if(e->level == manager->currentLevel && e->state != ENEMY_NEUTRALIZED) {
            e->pos.x += e->speed * e->direction;
            if(e->level == 1)
                e->pos.y += (SDL_GetTicks() / 100) % 3 - 1;

            if(e->pos.x <= 0 || e->pos.x + e->pos.w >= 640)
                e->direction *= -1;
        }
    }
}

void updateEnemies(EnemyManager *manager) {
    deplacerEnemies(manager);
}

void afficherEnemy(Enemy *e, SDL_Surface *screen, int frame) {
    SDL_BlitSurface(e->t[frame], NULL, screen, &e->pos);
    SDL_Rect bar = {e->pos.x, e->pos.y - 10, e->health * e->pos.w / 100, 5};
    SDL_FillRect(screen, &bar, SDL_MapRGB(screen->format, 255, 0, 0));
}

void animer(EnemyManager *manager, SDL_Surface *screen, int frame) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        if(manager->enemies[i].level == manager->currentLevel &&
           manager->enemies[i].state != ENEMY_NEUTRALIZED) {
            afficherEnemy(&manager->enemies[i], screen, frame);
        }
    }
}

void touch(Enemy *e, SDL_Rect playerPos) {
    if(intersects(e->pos, playerPos)) {
        e->state = ENEMY_HURT;
        e->health -= 1;
    }
}

void updateEnemyState(Enemy *e) {
    if(e->health <= 0) {
        e->state = ENEMY_NEUTRALIZED;
    }
}

void freeEnemies(EnemyManager *manager) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        for(int j = 0; j < NB_IMG; j++) {
            SDL_FreeSurface(manager->enemies[i].t[j]);
        }
    }
}

void initCoin(Coin *c) {
    c->pos.x = 100;
    c->pos.y = 50;
    c->pos.w = 32;
    c->pos.h = 32;
    c->img = IMG_Load("coin.png");
    c->collected = 0;
}

void updateCoin(Coin *c) {
    if(!c->collected) {
        c->pos.x += (rand() % 3) - 1;
        c->pos.y += (rand() % 3) - 1;
        if(c->pos.x < 0) c->pos.x = 0;
        if(c->pos.y < 0) c->pos.y = 0;
        if(c->pos.x + c->pos.w > 1000) c->pos.x = 1000 - c->pos.w;
        if(c->pos.y + c->pos.h > 600) c->pos.y = 600 - c->pos.h;
    }
}

void renderCoin(Coin c, SDL_Surface *screen) {
    if(!c.collected) {
        SDL_BlitSurface(c.img, NULL, screen, &c.pos);
    }
}

int checkCoinCollision(Coin c, SDL_Rect playerPos) {
    return intersects(c.pos, playerPos);
}

void freeCoin(Coin *c) {
    SDL_FreeSurface(c->img);
}

void renderCoinCounter(int coinCount, SDL_Surface *screen) {
    static TTF_Font *font = NULL;
    static SDL_Color white = {255, 255, 255, 255};

    if(!font) {
        font = TTF_OpenFont("arial.ttf", 24);
        if(!font) {
            printf("Erreur chargement police: %s\n", TTF_GetError());
            return;
        }
    }

    char text[32];
    snprintf(text, sizeof(text), "Coins: %d", coinCount);
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, white);
    if(text_surface) {
        SDL_Rect pos = {10, 10, 0, 0};
        SDL_BlitSurface(text_surface, NULL, screen, &pos);
        SDL_FreeSurface(text_surface);
    }
}
