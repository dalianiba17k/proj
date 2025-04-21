#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "perso.h"

void initialiser_leon(hero *leon);
void afficher_leon(hero leon, SDL_Surface *ecran);
int animation_perso(hero leon);

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(1400, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        fprintf(stderr, "Unable to set up video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_WM_SetCaption("Spicy Land", NULL);

    hero leon;
    initialiser_leon(&leon);
    leon.pos_hero2.x = 0;  
    leon.pos_hero2.y = screen->h - leon.afficher_hero[0]->h;

    int running = 1;
    SDL_Event event;

    // Variable to control speed increase
    int acceleration_timer = 0;
    float acceleration_rate = 0.2; // Increase this value for faster acceleration

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        leon.vx = -5;
                        leon.mouvment = 2; // Set left movement
                        break;
                    case SDLK_RIGHT:
                        leon.vx = 5;
                        leon.mouvment = 1; // Set right movement
                        break;
                    case SDLK_SPACE:
                        if (leon.vy == 0) {
                            leon.vy = -15; // Set vertical velocity for jump
                            leon.mouvment = 3; // Set jump movement
                        }
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (leon.vx < 0) { // Only reset movement if the character is currently moving left
                            leon.vx = 0; // Stop horizontal movement
                            leon.mouvment = 0; // Reset movement
                        }
                        break;
                    case SDLK_RIGHT:
                        if (leon.vx > 0) { // Only reset movement if the character is currently moving right
                            leon.vx = 0; // Stop horizontal movement
                            leon.mouvment = 0; // Reset movement
                        }
                        break;
                    case SDLK_SPACE:
                        leon.vx = 0; // Stop horizontal movement when space key is released
                        leon.mouvment = 0;
                        break;
                }
            }
        }

        // Update positions based on velocity
        leon.pos_hero2.x += leon.vx;
        leon.pos_hero2.y += leon.vy;

        // Gravity effect
        if (leon.pos_hero2.y < screen->h - leon.afficher_hero[0]->h) {
            leon.vy += 1;
        } else {
            leon.vy = 0;
            leon.pos_hero2.y = screen->h - leon.afficher_hero[0]->h; // Ensure character stays on the ground
        }

        // Update animation frames
        if (leon.vx != 0 || leon.vy != 0 || leon.mouvment != 0) {
            leon.farm = animation_perso(leon);
        }

        // Increase speed gradually
        acceleration_timer++;
        if (acceleration_timer >= 100) { // Increase speed every 100 milliseconds
            leon.vx += (leon.vx < 0) ? -acceleration_rate : acceleration_rate; // Accelerate in the direction of movement
            acceleration_timer = 0; // Reset timer
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        afficher_leon(leon, screen);
        
        SDL_Flip(screen);
        SDL_Delay(33);
    }

    SDL_Quit();
    return 0;
}
