#include "renforcement.h"

void perception()
{ // Prend l'état du monde et renvoie l'état de perception s
}

void evolution(ordinateur_t *ordi, int *suiteEtats, int *suiteActions, int *suiteRecompenses, int n)
{ // Prend le monde et une action et modifie l'état du monde
    int i, max, a;
    ordi->QTable[suiteEtats[n - 1]][suiteActions[n - 1]] += XI * (suiteActions[n] - ordi->QTable[suiteActions[n - 1]][suiteEtats[n - 1]]);
    for (i = n - 2; i > 0; i--)
    {
        max = ordi->QTable[suiteEtats[i + 1]][0];
        for (a = 1; a < NBACTIONS; a++)
        {
            if (max < ordi->QTable[i + 1][a])
            {
                max = ordi->QTable[i + 1][a];
            }
            ordi->QTable[suiteEtats[i]][suiteActions[i]] += XI * (suiteRecompenses[i + 1] + GAMMA * max - ordi->QTable[suiteEtats[i]][suiteActions[i]]);
        }
    }
}

void recompense()
{ // Prend le monde et renvoie la récompense associé à cet état
}

int *enumerationActions(int *tailleActions)
{ // Prend le monde et renvoie une énumération des actions possibles
}

int choixAction(ordinateur_t *ordi, int s, int T, int tailleActions)
{                               // Prend une perception et le monde et renvoie l'action choisie
    int a = 0;                  // Parcours de actions
    int *listeActions;
    listeActions = enumerationActions(&tailleActions); // NBACTIONS maximum
    int action = tailleActions - 1; // Action par défaut
    float Z = 0;      // Somme des énergies
    int E[tailleActions]; // Energies des actions
    float alpha;      // Réel aléatoire dans [0; 1[
    int cumul = 0;
    for (a = 0; a < tailleActions; a++)
    {
        E[listeActions[a]] = exp(ordi->QTable[s][listeActions[a]] / T);
        Z += E[listeActions[a]];
    }
    alpha = rand();
    for (a = 0; a < tailleActions; a++)
    {
        cumul += E[listeActions[a]] / Z;
        if (alpha <= cumul)
        {
            action = listeActions[a];
            break;
        }
    }
    return action;
}

void renforcement()
{ // Fonction principale
}
