#ifndef CARCASSONNE_GAME_H
#define CARCASSONNE_GAME_H
#include "structures.h"

extern void rotateTile(tile *T, int k);
extern _Bool placeableTile(grid *G, tile *T, unsigned int x, unsigned int y);
extern void placeTile(grid *G, deck *D, unsigned int x, unsigned int y);
extern void poseMeeple(grid *G, player *P, unsigned int x, unsigned int y, cardinal pos);

#endif //CARCASSONNE_GAME_H
