#ifndef CARCASONNE_UTILS_H
#define CARCASONNE_UTILS_H
#include "structures.h"

extern int scaleX(unsigned int x, unsigned int w);
extern int scaleY(unsigned int y, unsigned int h);
extern int mod(int a, int b);
extern void swap(tile *T1, tile *T2);
extern int randint(int a, int b);
extern void shuffle(deck *D);
extern void permutate(deck *D);
extern tile *pick(deck *D, unsigned int k);
extern tile *pickCurrent(deck *D);

#endif //CARCASONNE_UTILS_H
