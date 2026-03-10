#include <raylib.h>
#include <stdlib.h>
#include "init.h"

static Color palette[5] = {RED, BLUE, GREEN, YELLOW, BLACK};

meeple initMeeple(){
    meeple M = {0, 0, X, none};
    return M;
}

player initPlayer(int id){
    player P = {id, 7, 0, palette[id]};
    for (int i = 0; i < 7; i++) P.meeples[i] = initMeeple();
    return P;
}

player *initPlayerList(unsigned int n){
    player *P = malloc(n * sizeof(player));
    for (int i = 0; i < n; i++) P[i] = initPlayer(i);
    return P;
}

tile initTile(int id, int x, int y, land top, land right, land bottom, land left, land center){
    tile T = {id, {x, y},{top, right, bottom, left}, center};
    return T;
}

grid initGrid(tile T, unsigned int n){
    grid G;
    unsigned int N = 2 * n + 1;
    G.tiles = malloc(N * sizeof(tile*));
    for (int i = 0; i < N; i++){
        G.tiles[i] = malloc(N * sizeof(tile));
        for (int j = 0; j < N; j++)
            G.tiles[i][j] = initTile(-1, j, i, nothing, nothing, nothing, nothing, nothing);
    }
    T.position.x = n;
    T.position.y = n;
    G.tiles[n][n] = T;
    G.top = 1;
    G.right = 1;
    G.bottom = 1;
    G.left = 1;
    G.center = n;
    return G;
}

deck initDeck(unsigned int n){
    deck D;
    D.tiles = malloc(n * sizeof(tile));
    D.current = 1;
    D.size = n;
    return D;
}

void destroyPlayerList(player *P){
    free(P);
}

void destroyTile(tile *T){
    free(T);
}

void destroyGrid(grid *G){
    for (int i = 0; i < 2 * G->center + 1; i++) destroyTile(G->tiles[i]);
    free(G->tiles);
}

void destroyDeck(deck *D){
    free(D->tiles);
}
