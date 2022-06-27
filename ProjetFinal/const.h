#ifndef CONST_H
#define CONST_H

#define WINDOWH 600
#define WINDOWW 1200
#define WALLW 40

#define NBEPOCH 6
#define XI 0.5
#define GAMMA 0.5

//Direction pour l'orientation du joueur
enum DIRECTION{HAUTD=-90,GAUCHED=180,BASD=90,DROITD=0,HGD=135,HDD=45,BGD=225,BDD=-45};
//int epochActuelle=0;

#define NBETATS 24

//enum des états, position par rapport à la balle + distance
enum ETATS{UP1,UP2,UP3,DOWN1,DOWN2,DOWN3,LEFT1,LEFT2,LEFT3,RIGHT1,RIGHT2,RIGHT3,UL1,UL2,UL3,UR1,UR2,UR3,DL1,DL2,DL3,DR1,DR2,DR3};

// multiplier par 2 le nb d'état pour ajouter si adversaire loin ou proche

#define NBACTIONS 9
enum ACTIONS{HAUT,GAUCHE,BAS,DROIT,HG,HD,BG,BD,TIR};

enum REWARDS{
But=12,
balleRapprocheBut=5,
balleEloigneBut=-6,
balleBeacoupRapprocheBut=9,
balleEloigneBeaucoupbut=-8,
seRapprocheDeLaBalle=3,
sEloigneDeLaBalle=-4,
rateLeTir=-3};

#endif
