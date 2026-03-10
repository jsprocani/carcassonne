#include "game.h"
#include "utils.h"

void rotateTile(tile *T, int k){
    if (k){
        land tmp[4];
        for (int i = 0; i < 4; i++) tmp[i] = T->sides[mod(i + k, 4)];
        for (int i = 0; i < 4; i++) T->sides[i] = tmp[i];
    }
}

_Bool placeableTile(grid *G, tile *T, unsigned int x, unsigned int y){
    //cas simple qui rendent la pose imposible
    if (G->tiles[y][x].id != -1) return 0; // il y a deja une tuile
    if (G->tiles[y - 1][x].id == -1 && G->tiles[y][x - 1].id == -1
    && G->tiles[y + 1][x].id == -1 && G->tiles[y][x + 1].id == -1)//il n'y a aucune tuile à coté
        return 0;
    //verification corespondance cote haut/Nord de la tuile
    if (G->tiles[y - 1][x].id != -1 && !((T->sides[0] == city && G->tiles[y - 1][x].sides[2] == blazon) ||
    (T->sides[0] == blazon && G->tiles[y - 1][x].sides[2] == city)) && T->sides[0] != G->tiles[y - 1][x].sides[2])
        return 0;
    //verification corespondance cote droit/Est de la tuile
    if (G->tiles[y][x + 1].id != -1 && !((T->sides[1] == city && G->tiles[y][x + 1].sides[3] == blazon) ||
    (T->sides[1] == blazon && G->tiles[y][x + 1].sides[3] == city)) && T->sides[1] != G->tiles[y][x + 1].sides[3])
        return 0;
    //verification corespondance cote bas/Sud de la tuile
    if (G->tiles[y + 1][x].id != -1 && !((T->sides[2] == city && G->tiles[y + 1][x].sides[0] == blazon) ||
    (T->sides[2] == blazon && G->tiles[y + 1][x].sides[0] == city)) && T->sides[2] != G->tiles[y + 1][x].sides[0])
        return 0;
    //verification corespondance cote gauche/Ouest de la tuile
    if (G->tiles[y][x - 1].id != -1 && !((T->sides[3] == city && G->tiles[y][x - 1].sides[1] == blazon) ||
    (T->sides[3] == blazon && G->tiles[y][x - 1].sides[1] == city)) && T->sides[3] != G->tiles[y][x - 1].sides[1])
        return 0;
    return 1;//Si la fonction tourne toujours la tuile est posable
}

void placeTile(grid *G, deck *D, unsigned int x, unsigned int y){
    G->tiles[y][x] = D->tiles[D->current];
    G->tiles[y][x].position.x = x;
    G->tiles[y][x].position.y = y;
    D->current++;
    if (x >= G->center + G->right) G->right++;
    else if (x <= G->center - G->left) G->left++;
    if (y >= G->center + G->bottom) G->bottom++;
    else if (y <= G->center - G->top) G->top++;
}

void poseMeeple(grid *G, player *P, unsigned int x, unsigned int y, cardinal pos){
    G->tiles[y][x].meeple = &P->meeples[--P->count];
    G->tiles[y][x].meeple->posed = 1;
    G->tiles[y][x].meeple->position = pos;
    G->tiles[y][x].meeple->color = P->color;
}
