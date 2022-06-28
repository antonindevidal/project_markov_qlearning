#include "ordinateur.h"

void initQTableOrdi(ordinateur_t *ordi) {
    int i, j;
    for (i=0; i<NBETATS; i++) {
        for (j=0; j<NBACTIONS; j++) {
            ordi->QTable[i][j] = 0;
        }
    }
}