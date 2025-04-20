#include "ennemie.h"
#include <stdlib.h> 

int checkCollision(SDL_Rect a, SDL_Rect b) {
    if(a.x + a.w <= b.x) return 0;
    if(a.x >= b.x + b.w) return 0;
    if(a.y + a.h <= b.y) return 0;
    if(a.y >= b.y + b.h) return 0;
    return 1;
}

void initEnemies(EnemyManager *manager) {
    manager->currentLevel = 1;

    Enemy *e = &manager->enemies[0];
    e->position.x = 100;
    e->position.y = 300;
    e->position.w = 64;
    e->position.h = 64;
    e->speed = 2;
    e->direction = 1;
    e->state = ENEMY_ALIVE;
    e->health = 100;
    e->colision = 0;
    e->level = 1;

    SDL_Surface *sheet = IMG_Load("55555.png");
    for(int i = 0; i < NB_IMG; i++) {
        e->t[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
        SDL_Rect src = {i * 64, 0, 64, 64};
        SDL_BlitSurface(sheet, &src, e->t[i], NULL);
    }
    SDL_FreeSurface(sheet);

    init2(manager);
}

void init2(EnemyManager *manager) {
    Enemy *e = &manager->enemies[1];
    e->position.x = 400;
    e->position.y = 300;
    e->position.w = 64;
    e->position.h = 64;
    e->speed = 3;
    e->direction = -1;
    e->state = ENEMY_ALIVE;
    e->health = 100;
    e->colision = 0;
    e->level = 2;

    SDL_Surface *sheet = IMG_Load("8888.png");
    for(int i = 0; i < NB_IMG; i++) {
        e->t[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, 32, 0, 0, 0, 0);
        SDL_Rect src = {i * 64, 0, 64, 64};
        SDL_BlitSurface(sheet, &src, e->t[i], NULL);
    }
    SDL_FreeSurface(sheet);
}

void updateEnemies(EnemyManager *manager) {
    deplacerEnemies(manager);
}

void deplacerEnemies(EnemyManager *manager) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        Enemy *e = &manager->enemies[i];

        if(e->level == manager->currentLevel && e->state != ENEMY_NEUTRALIZED) {
            e->position.x += e->speed * e->direction;
            if(e->level == 1)
                e->position.y += (SDL_GetTicks() / 100) % 3 - 1;

            if(e->position.x <= 0 || e->position.x + e->position.w >= 640)
                e->direction *= -1;
        }
    }
}

void afficherEnemy(Enemy *enemy, SDL_Surface *screen, int frame) {
    SDL_BlitSurface(enemy->t[frame], NULL, screen, &enemy->position);

    SDL_Rect healthBar;
    healthBar.x = enemy->position.x;
    healthBar.y = enemy->position.y - 10;
    healthBar.w = (enemy->health * enemy->position.w) / 100;
    healthBar.h = 5;

    SDL_FillRect(screen, &healthBar, SDL_MapRGB(screen->format, 255, 0, 0));
}

void animer(EnemyManager *manager, SDL_Surface *screen, int frame) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        if(manager->enemies[i].level == manager->currentLevel && 
           manager->enemies[i].state != ENEMY_NEUTRALIZED) {
            afficherEnemy(&manager->enemies[i], screen, frame);
        }
    }
}

void touch(Enemy *enemy, SDL_Rect playerBB) {
    if(checkCollision(enemy->position, playerBB)) {
        enemy->state = ENEMY_HURT;
        enemy->health -= 1;
    }
}

void updateEnemyState(Enemy *enemy) {
    if(enemy->health <= 0) {
        enemy->state = ENEMY_NEUTRALIZED;
    }
}

void freeEnemies(EnemyManager *manager) {
    for(int i = 0; i < NUM_ENEMIES; i++) {
        for(int j = 0; j < NB_IMG; j++) {
            SDL_FreeSurface(manager->enemies[i].t[j]);
        }
    }
}

void initCoin(Coin *coin) {
    coin->pos.x = 100;
    coin->pos.y = 50;
    coin->pos.w = 32;
    coin->pos.h = 32;
    coin->img = IMG_Load("coin.png");
    coin->collected = 0;
}

void updateCoin(Coin *coin) {
    if (!coin->collected) {
        int dx = (rand() % 3) - 1; // -1, 0, 1
        int dy = (rand() % 3) - 1;
        coin->pos.x += dx;
        coin->pos.y += dy;

        if (coin->pos.x < 0) coin->pos.x = 0;
        if (coin->pos.y < 0) coin->pos.y = 0;
        if (coin->pos.x + coin->pos.w > 1000) coin->pos.x = 1000 - coin->pos.w;
        if (coin->pos.y + coin->pos.h > 600) coin->pos.y = 600 - coin->pos.h;
    }
}

void renderCoin(Coin coin, SDL_Surface *screen) {
    if(!coin.collected) {
        SDL_BlitSurface(coin.img, NULL, screen, &coin.pos);
    }
}

int checkCoinCollision(Coin coin, SDL_Rect player) {
    return checkCollision(coin.pos, player);
}

void freeCoin(Coin *coin) {
    SDL_FreeSurface(coin->img);
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

