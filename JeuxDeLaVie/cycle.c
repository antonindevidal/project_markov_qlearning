int detection_etat_stable(int **anc, int **nouv, int taille_x, int taille_y) {
    int i=0, j=0;
    int stable = 1;
    while ((i < taille_x) && stable)) {
        while ((j < taille_h) && stable)) {
            if (anc[i][j] != nouv[i][j]) {
                stable = 0;
            }
        }
    }
    return stable;
}