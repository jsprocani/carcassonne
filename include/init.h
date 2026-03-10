#ifndef CARCASSONNE_INIT_H
#define CARCASSONNE_INIT_H
#include "structures.h"

extern meeple initMeeple();
extern player initPlayer(int id);
extern player *initPlayerList(unsigned int n);
extern tile initTile(int id, int x, int y, land top, land right, land bottom, land left, land center);
extern grid initGrid(tile T, unsigned int m);
extern deck initDeck(unsigned int m);
extern void destroyPlayerList(player *P);
extern void destroyTile(tile *T);
extern void destroyGrid(grid *G);
extern void destroyDeck(deck *D);

#endif //CARCASSONNE_INIT_H
