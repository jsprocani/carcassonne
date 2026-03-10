#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "init.h"
#include "game.h"
#include "display.h"
#include "utils.h"

deck D;
grid G;
player *P;
rect board;
Vector2 cursor;
coord camera, current;
unsigned int width, height, n = 2;
Color ROYALBLUE = {65, 105, 175, 255};
Color FILTER1 = {255, 255, 255, 127};
Color FILTER2 = {0, 0, 0, 127};

void menu(int width, int height){
    _Bool choice = 0;
    char str[4];
    unsigned int x = 900, y = 600;
    icon logo;
    logo.image = LoadImage("images/Logo_Carcassonne_v3.png");
    logo.texture = LoadTextureFromImage(logo.image);
    while (!WindowShouldClose() && !choice){
        cursor = GetMousePosition();
        BeginDrawing();
        displayBackground(ROYALBLUE);
        DrawTexture(logo.texture, scaleX(10, width), 0, WHITE);
        // Bouton valider
        DrawRectangle(scaleX(x + 35, width), scaleY(y + 95, height),
                      scaleX(60, width), scaleY(60, height), GREEN);
        if (scaleX(x + 35, width) <= cursor.x && cursor.x < scaleX(x + 95, width)
            && scaleY(y + 95, height) <= cursor.y && cursor.y < scaleY(y + 155, height)){
            DrawRectangle(scaleX(x + 35, width), scaleY(y + 95, height),
                          scaleX(60, width), scaleY(60, height), FILTER1);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choice = 1;
        }
        // Bouton gauche
        if (scaleX(x - 5, width) <= cursor.x && cursor.x < scaleX(x + 35, width)
            && scaleY(y + 15, height) <= cursor.y && cursor.y < scaleY(y + 75, height)){
            DrawRectangle(scaleX(x - 5, width), scaleY(y + 15, height),
                          scaleX(40, width), scaleY(60, height), FILTER1);
            if (n > 2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) n--;
        }
        // Bouton droit
        if (scaleX(x + 95, width) <= cursor.x && cursor.x < scaleX(x + 135, width)
            && scaleY(y + 15, height) <= cursor.y && cursor.y < scaleY(y + 75, height)){
            DrawRectangle(scaleX(x + 95, width), scaleY(y + 15, height),
                          scaleX(40, width), scaleY(60, height), FILTER1);
            if (n < 5 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) n++;
        }
        sprintf(str, "<%d>", n);
        DrawText(str, scaleX(x, width), scaleY(y, height),
                 scaleX(100, width), WHITE);
        displayCursor(cursor, board, current, 50, GOLD, 0, 0);
        EndDrawing();
    }
    P = initPlayerList(n);
    UnloadImage(logo.image);
    UnloadTexture(logo.texture);
}

void game(_Bool debug){
    _Bool pose;
    unsigned int pos_x, pos_y, turn = 0;
    icon meeple, star;
    meeple.image = LoadImage("images/meeple.png");
    meeple.texture = LoadTextureFromImage(meeple.image);
    star.image = LoadImage("images/star.png");
    star.texture = LoadTextureFromImage(star.image);
    setCamera(&camera, board, G);
    while (!WindowShouldClose() && D.current < D.size){
        // Coordonnées
        cursor = GetMousePosition();
        current = getTileCoord(cursor, board);
        // Dessinage de l'UI
        BeginDrawing();
        displayBackground(ROYALBLUE);
        displayBoard(board, RAYWHITE, GOLD);
        displayGrid(&G, board, camera, &meeple, debug);
        displayDeck(&D, 1, debug);
        displayPlayerTurn(P, turn);
        displayPlayersInfo(P, n, &meeple, &star);
        displayCursor(cursor, board, current, 50, P[turn].color, 1, debug);
        EndDrawing();
        // Rotation
        if (GetMouseWheelMove() > 0){
            rotateTile(pickCurrent(&D), 1);
            ImageRotate(&pickCurrent(&D)->image, -90);
            UnloadTexture(pickCurrent(&D)->texture);
            pickCurrent(&D)->texture = LoadTextureFromImage(pickCurrent(&D)->image);
        }
        else if (GetMouseWheelMove() < 0){
            rotateTile(pickCurrent(&D), -1);
            ImageRotate(&pickCurrent(&D)->image, 90);
            UnloadTexture(pickCurrent(&D)->texture);
            pickCurrent(&D)->texture = LoadTextureFromImage(pickCurrent(&D)->image);
        }
        // Commandes
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) camera.x += 100;
        else if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) camera.x -= 100;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) camera.y += 100;
        else if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) camera.y -= 100;
        if (IsKeyPressed(KEY_SPACE)) setCamera(&camera, board, G);
        else if (IsKeyPressed(KEY_TAB)) debug = !debug;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (placeableTile(&G, pickCurrent(&D), (current.x - board.x - camera.x) / 100, (current.y - board.y - camera.y) / 100)){
                placeTile(&G, &D, (current.x - board.x - camera.x) / 100, (current.y - board.y - camera.y) / 100);
                pos_x = getTilePos(cursor.x, board.x);
                pos_y = getTilePos(cursor.y, board.y);
                cursor.x = pos_x;
                cursor.y = pos_y;
                pose = 1;
                while (!WindowShouldClose() && P[turn].count &&pose){
                    cursor = GetMousePosition();
                    BeginDrawing();
                    displayBackground(ROYALBLUE);
                    displayBoard(board, RAYWHITE, GOLD);
                    displayGrid(&G, board, camera, &meeple, debug);
                    displayDeck(&D, 1, debug);
                    displayPlayerTurn(P, turn);
                    displayPlayersInfo(P, n, &meeple, &star);
                    // Poser pion
                    DrawRectangle(pos_x - 75, pos_y - 75, 250, 250, FILTER2);
                    DrawRectangle(pos_x - 75, pos_y - 75, 50, 50, RED);
                    if (pos_x - 75 <= cursor.x && cursor.x < pos_x - 25
                    && pos_y - 75 <= cursor.y && cursor.y < pos_y - 25){
                        DrawRectangle(pos_x - 75, pos_y - 75, 50, 50, FILTER1);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) pose = 0;
                    }
                    // Nord
                    if (pos_x + 42 <= cursor.x && cursor.x < pos_x + 60
                    && pos_y + 4 <= cursor.y && cursor.y < pos_y + 20){
                        DrawTexture(meeple.texture, pos_x + 42, pos_y + 4, GOLD);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                            pose = 0;
                            poseMeeple(&G, &P[turn], (current.x - board.x - camera.x) / 100,
                                       (current.y - board.y - camera.y) / 100, N);
                        }
                    }
                    else DrawTexture(meeple.texture, pos_x + 42, pos_y + 4, WHITE);
                    // Est
                    if (pos_x + 80 <= cursor.x && cursor.x < pos_x + 96
                        && pos_y + 42 <= cursor.y && cursor.y < pos_y + 60){
                        DrawTexture(meeple.texture, pos_x + 80, pos_y + 42, GOLD);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                            pose = 0;
                            poseMeeple(&G, &P[turn], (current.x - board.x - camera.x) / 100,
                                       (current.y - board.y - camera.y) / 100, E);
                        }
                    }
                    else DrawTexture(meeple.texture, pos_x + 80, pos_y + 42, WHITE);
                    // Sud
                    if (pos_x + 42 <= cursor.x && cursor.x < pos_x + 60
                        && pos_y + 80 <= cursor.y && cursor.y < pos_y + 96){
                        DrawTexture(meeple.texture, pos_x + 42, pos_y + 80, GOLD);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                            pose = 0;
                            poseMeeple(&G, &P[turn], (current.x - board.x - camera.x) / 100,
                                       (current.y - board.y - camera.y) / 100, S);
                        }
                    }
                    else DrawTexture(meeple.texture, pos_x + 42, pos_y + 80, WHITE);
                    // Ouest
                    if (pos_x + 4 <= cursor.x && cursor.x < pos_x + 20
                        && pos_y + 42 <= cursor.y && cursor.y < pos_y + 60){
                        DrawTexture(meeple.texture, pos_x + 4, pos_y + 42, GOLD);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                            pose = 0;
                            poseMeeple(&G, &P[turn], (current.x - board.x - camera.x) / 100,
                                       (current.y - board.y - camera.y) / 100, W);
                        }
                    }
                    else DrawTexture(meeple.texture, pos_x + 4, pos_y + 42, WHITE);
                    // Centre
                    if (pos_x + 42 <= cursor.x && cursor.x < pos_x + 60
                        && pos_y + 42 <= cursor.y && cursor.y < pos_y + 60){
                        DrawTexture(meeple.texture, pos_x + 42, pos_y + 42, GOLD);
                        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                            pose = 0;
                            poseMeeple(&G, &P[turn], (current.x - board.x - camera.x) / 100,
                                       (current.y - board.y - camera.y) / 100, X);
                        }
                    }
                    else DrawTexture(meeple.texture, pos_x + 42, pos_y + 42, WHITE);
                    displayCursor(cursor, board, current, 50, P[turn].color, 1, debug);
                    EndDrawing();
                }
                turn++;
                if (turn == n) turn = 0;
            }
        }
    }
    // Fin de jeu
    char str[6];
    BeginDrawing();
    displayBackground(ROYALBLUE);
    displayBoard(board, RAYWHITE, GOLD);
    displayGrid(&G, board, camera, &meeple, debug);
    displayPlayerTurn(P, turn);
    displayPlayersInfo(P, n, &meeple, &star);
    sprintf(str, "%d/%d", D.size, D.size);
    DrawText(str, 25, 50, 80, GOLD);
    EndDrawing();
    WaitTime(1);
    UnloadImage(meeple.image);
    UnloadTexture(meeple.texture);
    UnloadImage(star.image);
    UnloadTexture(star.texture);
}

void start(FILE *CSV, FILE *CFG){
    InitWindow(0, 0, "Carcassonne");
    SetTargetFPS(60);
    ToggleFullscreen();
    DisableCursor();
    srand(time(NULL));
    width = GetScreenWidth(), height = GetScreenHeight();
    board = generateBoard(350, 50, width, height);
    unsigned int len = cfgParser(CFG, CSV, &D);
    shuffle(&D);
    G = initGrid(D.tiles[0], len);
    menu(width, height); // Menu de sélection de joueurs
    game(0); // Jeu en cours / Boucle de jeu
    clearTileTextures(&G, &D);
    destroyPlayerList(P);
    destroyGrid(&G);
    destroyDeck(&D);
    CloseWindow();
}

int main(int argc, char *argv[]){
    if (argc > 1){
        _Bool bool1 = 0, bool2 = 0;
        char str1[256], str2[256];
        sprintf(str1, "%s.csv", argv[1]);
        sprintf(str2, "%s.cfg", argv[1]);
        FILE *CSV = fopen(str1, "r");
        FILE *CFG = fopen(str2, "r");
        if (CSV != NULL) bool1 = 1;
        else printf("Error: Unable to access CSV file %s\n", str1);
        if (CFG != NULL) bool2 = 1;
        else printf("Error: Unable to access CFG file %s\n", str2);
        if (bool1 && bool2) start(CSV, CFG);
    }
    else printf("Error: Requires file specification\n");
    return 0;
}
