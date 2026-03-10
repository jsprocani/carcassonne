#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "init.h"
#include "game.h"

unsigned int cfgParser(FILE *CFG, FILE *CSV, deck *D){
    int var;
    char fname[24], c;
    unsigned int len;
    fscanf(CFG, "LEN:%d", &len);
    fscanf(CFG, "%c", &c);
    *D = initDeck(len);
    csvParser(CSV, D->tiles);
    for (int i = 0; i < len; i++){
        fscanf(CFG, "%c", &c);
        sprintf(fname, "images/tiles/Tile_%c.png", c);
        D->tiles[i].image = LoadImage(fname);
        D->tiles[i].texture = LoadTextureFromImage(D->tiles[i].image);
        fscanf(CFG, "%c", &c);
        fscanf(CFG, "%d", &var);
        rotateTile(&D->tiles[i], var);
        fscanf(CFG, "%c", &c);
    }
    fclose(CFG);
    return len;
}

void csvParser(FILE *F, tile *list){
    int k;
    char c, tmp[8];
    land sides[4], center;
    for (int i = 0; i < 72; i++){
        for (int j = 0; j < 4; j++){
            k = 0;
            fscanf(F, "%c", &c);
            while (c != ',' && c != '\n'){
                tmp[k] = c;
                k++;
                fscanf(F, "%c", &c);
            }
            tmp[k] = '\0';
            if (!strcmp(tmp, "ville")) sides[j] = city;
            else if (!strcmp(tmp, "pre")) sides[j] = pre;
            else if (!strcmp(tmp, "route")) sides[j] = road;
            else if (!strcmp(tmp, "blason")) sides[j] = blazon;
        }
        k = 0;
        fscanf(F, "%c", &c);
        while (c != ',' && c != '\n'){
            tmp[k] = c;
            k++;
            fscanf(F, "%c", &c);
        }
        tmp[k] = '\0';
        if (!strcmp(tmp, "ville")) center = city;
        else if (!strcmp(tmp, "pre")) center = pre;
        else if (!strcmp(tmp, "route")) center = road;
        else if (!strcmp(tmp, "blason")) center = blazon;
        else if (!strcmp(tmp, "abbaye")) center = abbey;
        else if (!strcmp(tmp, "village")) center = village;
        list[i] = initTile(i, 0, 0, sides[0], sides[1], sides[2], sides[3], center);
    }
    fclose(F);
}
