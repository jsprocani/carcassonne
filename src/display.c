#include <raylib.h>
#include <stdio.h>
#include "display.h"
#include "utils.h"

static Color palette[7] = {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, {0, 255, 255, 255}};

_Bool cursorInBoardWidth(rect board, int x){
    return x >= board.x && x < board.x + board.w;
}

_Bool cursorInBoardHeight(rect board, int y){
    return y >= board.y && y < board.y + board.h;
}

_Bool cursorInBoard(rect board, coord current){
    return cursorInBoardWidth(board, current.x) && cursorInBoardHeight(board, current.y);
}

_Bool tileInBoardWidth(coord camera, int x, int w){
    return camera.x + x >= 0 && camera.x + x <= w - 100;
}

_Bool tileInBoardHeight(coord camera, int y, int h){
    return camera.y + y >= 0 && camera.y + y <= h - 100;
}

_Bool tileInBoard(coord camera, int x, int y, int w, int h){
    return tileInBoardWidth(camera, x, w) && tileInBoardHeight(camera, y, h);
}


void displayTile(tile *T, rect board, coord camera, icon *meeple, _Bool debug){
    int x = T->position.x * 100, y = T->position.y * 100;
    if (tileInBoard(camera, x, y, board.w, board.h)){
        x += board.x + camera.x;
        y += board.y + camera.y;
        DrawTexture(T->texture, x, y, WHITE);
        if (T->meeple != NULL){
            if (T->meeple->position == N) DrawTexture(meeple->texture, x + 42, y + 4, T->meeple->color);
            else if (T->meeple->position == E) DrawTexture(meeple->texture, x + 84, y + 42, T->meeple->color);
            else if (T->meeple->position == S) DrawTexture(meeple->texture, x + 42, y + 84, T->meeple->color);
            else if (T->meeple->position == W) DrawTexture(meeple->texture, x + 4, y + 42, T->meeple->color);
            else DrawTexture(meeple->texture, x + 42, y + 42, T->meeple->color);
        }
    }
    if (debug){
        char id[3];
        DrawRectangle(x + 40, y, 20, 20, palette[T->sides[0]]);
        DrawRectangle(x + 80, y + 40, 20, 20, palette[T->sides[1]]);
        DrawRectangle(x + 40, y + 80, 20, 20, palette[T->sides[2]]);
        DrawRectangle(x, y + 40, 20, 20, palette[T->sides[3]]);
        DrawRectangle(x + 40, y + 40, 20, 20, palette[T->center]);
        sprintf(id, "%d", T->id);
        DrawText(id, x + 5, y, 30, BLACK);
    }
}

void displayGrid(grid *G, rect board, coord camera, icon *meeple, _Bool debug){
    for (int i = G->center - G->top; i <= G->center + G->bottom; i++)
        for (int j = G->center - G->left; j <= G->center + G->right; j++)
            if (G->tiles[i][j].id != -1) displayTile(&G->tiles[i][j], board, camera, meeple, debug);
}

void displayDeck(deck *D, _Bool info, _Bool debug){
    tile *T = pickCurrent(D);
    int x = T->position.x * 100, y = T->position.y * 100;
    DrawTexture(T->texture, 15, 15, WHITE);
    if (info){
        char str[8];
        sprintf(str, "%d/%d", D->current, D->size);
        DrawText(str, 25, 125, 40, WHITE);
    }
    if (debug){
        char id[3];
        DrawRectangle(x + 55, y + 15, 20, 20, palette[T->sides[0]]);
        DrawRectangle(x + 95, y + 55, 20, 20, palette[T->sides[1]]);
        DrawRectangle(x + 55, y + 95, 20, 20, palette[T->sides[2]]);
        DrawRectangle(x + 15, y + 55, 20, 20, palette[T->sides[3]]);
        DrawRectangle(x + 55, y + 55, 20, 20, palette[T->center]);
        sprintf(id, "%d", T->id);
        DrawText(id, x + 20, y + 15, 30, BLACK);
    }
}

void displayPlayerTurn(player *P, unsigned int turn){
    char str[3];
    sprintf(str, "P%d", turn + 1);
    DrawText("PLAYER TURN :", 15, 200, 30, WHITE);
    DrawText(str, 265, 200, 30, P[turn].color);
}

void displayPlayersInfo(player *P, unsigned int n, icon *meeple, icon *star){
    char str1[4], str2[4];
    for (int i = 0; i < n; i++){
        sprintf(str1, "×%d", P[i].count);
        DrawTexture(meeple->texture, 15, 250 + 50 * P[i].id, P[i].color);
        DrawText(str1, 40, 243 + 50 * P[i].id, 30, WHITE);
        sprintf(str2, "×%d", P[i].score);
        DrawTexture(star->texture, 100, 250 + 50 * P[i].id, GOLD);
        DrawText(str2, 125, 243 + 50 * P[i].id, 30, WHITE);
    }
}

void displayBackground(Color c){
    ClearBackground(c);
}

void displayBoard(rect board, Color c1, Color c2){
    unsigned int var = 5;
    Rectangle rec = {board.x - var, board.y - var, board.w + var * 2, board.h + var * 2};
    DrawRectangle(board.x, board.y, board.w, board.h, c1);
    DrawRectangleLinesEx(rec, var, c2);
}

void displayCursor(Vector2 cursor, rect board, coord current, unsigned int size, Color c, _Bool draw, _Bool debug){
    char str[13];
    if (debug) sprintf(str, "+[%.0f×%.0f]", cursor.x, cursor.y);
    else sprintf(str, "+");
    DrawText(str, cursor.x - 15, cursor.y - 25, size, c);
    if (draw && cursorInBoard(board, current)){
        DrawRectangleLines(current.x, current.y, 100, 100, c);
        if (debug){
            sprintf(str, "%d×%d", current.x, current.y);
            DrawText(str, current.x, current.y, 20, c);
        }
    }
}

void setCamera(coord *camera, rect board, grid G){
    camera->x = board.w / 2 - (board.w / 2 % 100) - G.center * 100;
    camera->y = board.h / 2 - (board.h / 2 % 100) - G.center * 100;
}

int getTilePos(int k, unsigned int offset){
    int res = 0;
    offset %= 100;
    k -= offset;
    while (1){
        k -= 100;
        if (k < 0){
            k += 100;
            break;
        }
        else res += 100;
    }
    if (k >= 0 && k < 100) k = 0;
    return res + k + offset;
}

coord getTileCoord(Vector2 cursor, rect board){
    coord current = {getTilePos(cursor.x, board.x), getTilePos(cursor.y, board.y)};
    return current;
}

rect generateBoard(int x, int y, int w, int h){
    double offset = (1920. / w - 1) * 100;
    w = w / 1920. * 1500 - offset, h = h / 1080. * 1000;
    w -= w % 100, h -= h % 100;
    rect board = {x, y, w, h};
    return board;
}

void clearTileTextures(grid *G, deck *D){
    for (int i = G->center - G->top; i <= G->center + G->bottom; i++)
        for (int j = G->center - G->left; j <= G->center + G->right; j++)
            if (G->tiles[i][j].id != -1){
                UnloadImage(G->tiles[i][j].image);
                UnloadTexture(G->tiles[i][j].texture);
            }
    UnloadImage(D->tiles[D->current].image);
    UnloadTexture(D->tiles[D->current].texture);
}
