#ifndef CARCASSONNE_DISPLAY_H
#define CARCASSONNE_DISPLAY_H
#include "structures.h"

extern _Bool cursorInBoardWidth(rect board, int x);
extern _Bool cursorInBoardHeight(rect board, int y);
extern _Bool cursorInBoard(rect board, coord current);
extern _Bool tileInBoardWidth(coord camera, int x, int w);
extern _Bool tileInBoardHeight(coord camera, int y, int h);
extern _Bool tileInBoard(coord camera, int x, int y, int w, int h);
extern void displayTile(tile *T, rect board, coord camera, icon *meeple, _Bool debug);
extern void displayGrid(grid *G, rect board, coord camera, icon *meeple, _Bool debug);
extern void displayDeck(deck *D, _Bool info, _Bool debug);
extern void displayPlayerTurn(player *P, unsigned int turn);
extern void displayPlayersInfo(player *P, unsigned int n, icon *meeple, icon *star);
extern void displayBackground(Color c);
extern void displayBoard(rect board, Color c1, Color c2);
extern void displayCursor(Vector2 cursor, rect board, coord current, unsigned int size, Color c, _Bool draw, _Bool debug);
extern void setCamera(coord *camera, rect board, grid G);
extern int getTilePos(int k, unsigned int offset);
extern coord getTileCoord(Vector2 cursor, rect board);
extern rect generateBoard(int x, int y, int w, int h);
extern void clearTileTextures(grid *G, deck *D);

#endif //CARCASSONNE_DISPLAY_H
