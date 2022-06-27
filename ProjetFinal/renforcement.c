#include "renforcement.h"

void perception()
{ // Prend l'état du monde et renvoie l'état de perception s
}

void evolution()
{ // Prend le monde et une action et modifie l'état du monde
}

void recompense()
{ // Prend le monde et renvoie la récompense associé à cet état
}

void enumerationActions()
{ // Prend le monde et renvoie une énumération des actions possibles
}

int choixAction(ordinateur_t *ordi, int perception)
{ // Prend une perception et le monde et renvoie l'action choisie
    int i = 0; 
    float alpha;
    float sommeCummule = ordi->QTable[perception][0];
    float sommeLigne = 0;
    for (i=0; i<NBACTIONS; i++) {
        sommeLigne += ordi->QTABLE[perception][i];
    }
    alpha = rand() % sommeLigne;
    i = 0;
    while (alpha > sommeCummule) {
        i++;
        sommeCummule += ordi->QTable[perception][i];
    }
    return i
}

void renforcement()
{ // Fonction principale
}
