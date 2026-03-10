#include <stdlib.h>
#include "utils.h"

int scaleX(unsigned int x, unsigned int w){
    return w / 1920. * x;
}

int scaleY(unsigned int y, unsigned int h){
    return h / 1080. * y;
}

int mod(int a, int b){
    int r = a % b;
    if (r < 0) r += b;
    return r;
}

int randint(int a, int b){
    return a + rand() % (b - a + 1);
}

void swap(tile *T1, tile *T2){
    tile tmp;
    tmp = *T1;
    *T1 = *T2;
    *T2 = tmp;
}

void shuffle(deck *D){
    for (int i = 1; i < D->size; i++) swap(pick(D, i), pick(D, randint(i, D->size - 1)));
}

void permutate(deck *D){
    for (int i = 0; i < D->size - 1; i++) swap(pick(D, i), pick(D, i + 1));
}

tile *pick(deck *D, unsigned int k){
    return &D->tiles[k];
}

tile *pickCurrent(deck *D){
    return &D->tiles[D->current];
}
