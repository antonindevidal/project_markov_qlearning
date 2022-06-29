#ifndef CONST_H
#define CONST_H

#define WINDOWH 640
#define WINDOWW 1200
#define WALLW 40
#define WALLH 8
#define GOALSIZE 300

#define TIMEGAME 60

#define NBEPOCH 12 
#define MAXEPOCH 10000
#define XI 0.01
#define GAMMA 0.8
#define TEMPERATURE 24

#define DISTANCE1 60
#define DISTANCE2 80


//Direction pour l'orientation du joueur
enum DIRECTION{HAUTD=-90,GAUCHED=180,BASD=90,DROITD=0,HGD=135,HDD=45,BGD=225,BDD=-45};

enum EQUIPE{EQUIPEGAUCHE=1,EQUIPEDROITE=-1};
//int epochActuelle=0;

//#define NBETATS 24
#define NBETATS 24

//enum des états, position par rapport à la balle + distance
//Exemple: UL3 = UP et LEFT à une distance de 3
/*#define NBETATDISTANCE1 8
enum ETATS{UP1,DOWN1,LEFT1,RIGHT1,UL1,UR1,DL1,DR1,UP2,UP3,DOWN2,DOWN3,LEFT2,LEFT3,RIGHT2,RIGHT3,UL2,UL3,UR2,UR3,DL2,DL3,DR2,DR3};
*/

// multiplier par 2 le nb d'état pour ajouter si adversaire loin ou proche
// direction du joueur + la distance du joueur + distance de l'adversaire
#define NBETATDISTANCE1 8
enum ETATS{UP11,DOWN11,LEFT11,RIGHT11,UL11,UR11,DL11,DR11,UP21,UP31,DOWN21,DOWN31,
LEFT21,LEFT31,RIGHT21,RIGHT31,UL21,UL31,UR21,UR31,DL21,DL31,DR21,DR31};


#define NBACTIONS 9
enum ACTIONS{HAUT,BAS,GAUCHE,DROIT,HG,HD,BG,BD,TIR};

enum REWARDS{
But=9,
balleRapprocheBut=3,
balleEloigneBut=-1,
balleBeacoupRapprocheBut=4,
balleEloigneBeaucoupbut=-3,
seRapprocheDeLaBalle=1,
sEloigneDeLaBalle=-2,
rateLeTir=-3};

// enum REWARDS{
// But=12,
// balleRapprocheBut=5,
// balleEloigneBut=-6,
// balleBeacoupRapprocheBut=9,
// balleEloigneBeaucoupbut=-8,
// seRapprocheDeLaBalle=3,
// sEloigneDeLaBalle=-4,
// rateLeTir=-3};

#endif
