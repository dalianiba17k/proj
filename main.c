#include "game.h"
#include "functions.h"
#include "level.h"



int game_menu(GAME *game);
int get_config(GAME *game);

int main(int argc, char *argv[]) {
    GAME game = {0}; // Initialisation à zéro pour éviter un comportement indéfini

    // Initialisation des sous-systèmes SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Définition du titre et de l'icône de la fenêtre
    SDL_WM_SetCaption("It never ends", NULL);
    SDL_Surface *icon = IMG_Load("DATA/GFX/GUI/Loupe.png");
    if (!icon) {
        fprintf(stderr, "Failed to load icon: %s\n", IMG_GetError());
    } else {
        SDL_WM_SetIcon(icon, NULL);
        SDL_FreeSurface(icon); // Libération de la surface après utilisation
    }

    // Chargement de la configuration ou utilisation des valeurs par défaut
    if (get_config(&game) == 0) {
        game.screen = SDL_SetVideoMode(game.config.resolution_w, game.config.resolution_h, 32,
                                       SDL_DOUBLEBUF | SDL_HWSURFACE);
    } else {
        // Configuration par défaut si le fichier de config est absent
        game.screen = SDL_SetVideoMode(1280, 720, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
    }

    // Vérification de l'initialisation de l'écran
    if (!game.screen) {
        fprintf(stderr, "SDL_SetVideoMode failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialisation de TTF et SDL_Mixer
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Affichage de l'écran de chargement
    loading_screen(&game);

    // Démarrage du menu du jeu
    start_menu(&game);

    // Nettoyage des ressources
    SDL_FreeSurface(game.screen);
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return EXIT_SUCCESS;
}

int get_config(GAME *game) {
    game->config.f = fopen("config/config.cfg", "r");
    if (game->config.f != NULL) {
        fscanf(game->config.f, "[resolution]\n");
        fscanf(game->config.f, "w=%d\n", &game->config.resolution_w);
        fscanf(game->config.f, "h=%d\n", &game->config.resolution_h);
        // La ligne suivante est supprimée car fullscreen n'est plus utilisé
        // fscanf(game->config.f, "fullscreen=%d\n", &game->config.fullscreen);
        fclose(game->config.f);
        return 0;
    } else {
        return -1; // Retourne -1 si le fichier est absent
    }
}

void start_menu(GAME *game) {
    if (game_menu(game) == 0) {
        playLevel(game);
    }
}
