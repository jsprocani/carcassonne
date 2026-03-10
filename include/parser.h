#ifndef CARCASSONNE_CSV_H
#define CARCASSONNE_CSV_H
#include "structures.h"

extern void csvParser(FILE *F, tile *list);
extern unsigned int cfgParser(FILE *CFG, FILE *CSV, deck *D);

#endif //CARCASSONNE_CSV_H
