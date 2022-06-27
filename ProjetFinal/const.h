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
//#define NBETATS 48

//enum des états, position par rapport à la balle + distance
//Exemple: UL3 = UP et LEFT à une distance de 3
enum ETATS{UP1,UP2,UP3,DOWN1,DOWN2,DOWN3,LEFT1,LEFT2,LEFT3,RIGHT1,RIGHT2,RIGHT3,UL1,UL2,UL3,UR1,UR2,UR3,DL1,DL2,DL3,DR1,DR2,DR3};

// multiplier par 2 le nb d'état pour ajouter si adversaire loin ou proche
/*enum ETATS{UP11,UP21,UP31,DOWN11,DOWN21,DOWN31,LEFT11,LEFT21,LEFT31,RIGHT11,RIGHT21,RIGHT31,UL11,UL21,UL31,UR11,UR21,UR31,DL11,DL21,DL31,DR11,DR21,DR31
           UP12,UP22,UP32,DOWN12,DOWN22,DOWN32,LEFT12,LEFT22,LEFT32,RIGHT12,RIGHT22,RIGHT32,UL12,UL22,UL32,UR12,UR22,UR32,DL12,DL22,DL32,DR12,DR22,DR32};
*/

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
