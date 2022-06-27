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

int choixAction(ordinateur_t *ordi, int s)
{ // Prend une perception et le monde et renvoie l'action choisie
    int a=0; // Parcours de actions
    int action = NBACTIONS-1; // Action par défaut
    float Z=0; // Somme des énergies
    int E[NBACTIONS]; // Energies des actions
    float alpha; // Réel aléatoire dans [0; 1[
    int cumul = 0;
    for (a=0; a<NBACTIONS; a++) {
        E[a] = exp(ordi->QTable[s][a]);
        Z += E[a];
    }
    alpha = rand();
    for (a=0; a<NBACTIONS; a++) {
        if (alpha <= cumul) {
            action = a;
            break;
        }
    }
    return action;
}

void renforcement()
{ // Fonction principale
}
