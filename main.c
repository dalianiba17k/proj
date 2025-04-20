#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "ennemie.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define FPS 60

void movePlayer(Player *player, SDL_Event *event) {
    const int SPEED = 5;

    if(event->key.keysym.sym == SDLK_UP) player->pos.y -= SPEED;
    if(event->key.keysym.sym == SDLK_DOWN) player->pos.y += SPEED;
    if(event->key.keysym.sym == SDLK_LEFT) player->pos.x -= SPEED;
    if(event->key.keysym.sym == SDLK_RIGHT) player->pos.x += SPEED;
}

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if(TTF_Init() == -1) {
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Niveaux avec Ennemis", NULL);
    IMG_Init(IMG_INIT_PNG);

    srand(time(NULL));

    EnemyManager manager;
    initEnemies(&manager);

    Player player;
    player.pos.x = 300;
    player.pos.y = 300;
    player.pos.w = 64;
    player.pos.h = 64;
    player.img = IMG_Load("joueur.png");

    SDL_Event event;
    int running = 1;
    int frame = 0;
    Uint32 lastFrameTime = SDL_GetTicks();

    SDL_Rect playerBB = {player.pos.x, player.pos.y, 64, 64};
    int coinCount = 0;
    Coin coin;
    initCoin(&coin);

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                running = 0;
            if(event.type == SDL_KEYDOWN) {
                movePlayer(&player, &event);  
                playerBB.x = player.pos.x;
                playerBB.y = player.pos.y;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if(currentTime > lastFrameTime + 1000/FPS) {
            frame = (frame + 1) % NB_IMG;
            lastFrameTime = currentTime;

            updateEnemies(&manager);

            for(int i = 0; i < NUM_ENEMIES; i++) {
                if(manager.enemies[i].level == manager.currentLevel && 
                   manager.enemies[i].state != ENEMY_NEUTRALIZED) {
                    touch(&manager.enemies[i], playerBB);
                    updateEnemyState(&manager.enemies[i]);

                    if(manager.enemies[i].state == ENEMY_NEUTRALIZED && manager.currentLevel == 1) {
                        manager.currentLevel = 2;
                    }
                }
            }

            updateCoin(&coin);

            if(!coin.collected && checkCoinCollision(coin, playerBB)) {
                coin.collected = 1;
                coinCount++;
            }

            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            animer(&manager, screen, frame);
            renderCoin(coin, screen);
            renderCoinCounter(coinCount, screen);
            SDL_BlitSurface(player.img, NULL, screen, &player.pos);
            SDL_Flip(screen);
        }
    }

    freeEnemies(&manager);
    freeCoin(&coin);
    SDL_FreeSurface(player.img);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

