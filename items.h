#ifndef ITEMS_H
#define ITEMS_H
#include "collision.h"
#define MAX_ITEMS 10  // Keep this as the only definition
typedef struct Item
{
int number;
SDL_Surface *image, *description;
SDL_Rect position, blit_pos;
Cercle cercle;
int have, selected, disposable;
}Item;

typedef struct Inventory
{
int count;
Item item[MAX_ITEMS];

}Inventory;

#endif
