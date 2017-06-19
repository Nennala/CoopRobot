#include <stdio.h>
#include <stdbool.h>

#define SIZETAB 10  //taille des tableaux
#define INITX 5 //position de départ de robot
#define INITY 4

int posx;
int posy;
int orientation;

char tab1[SIZETAB][SIZETAB]; // je défini ici trois tableaux afin qu'ils soient accessibles dans tout mon code
char tab2[SIZETAB][SIZETAB];
char tab0[SIZETAB][SIZETAB]; //carte vierge

bool deplacement_effectue;

void deplacement(int *posx, int *posy, int orientation, int distance);
void pivoter_gauche(int *posx, int *posy, int *orientation);
void pivoter_droite(int *posx, int *posy, int *orientation);
void reculer_robot(int *posx, int *posy, int orientation);
void avancer_robot(int *posx, int *posy, int orientation);
void placer_robot(int posx, int posy, int orientation);
void carte_vierge(void);
void compare(void);// voici le but de tout ce code, écrire une foncion permettant
//parcourir deux tableaux, comparer leur valeur, identifier, signaler et dénombrer les caractères différents.
void sppr(int tab, int posx, int posy);// permet de supprimer un caractère dans un tableau. Le premier argument
//est le tableau à modifier et le second argument est la position dans ce tableau. Le caractère est remplacé par '0'.
void put(int tab, int posx, int posy, char car);// permet de placer un caractère 'x' dans un tableau.
//Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau
void affichage(int choix);//permet d'afficher les deux tableaux dans le terminal
void initialisation(void); //permet d'innitaliser les tableaux à une valeur choisi, poru l'instant 0
bool trouver_coin(int *posx, int *posy, int orientation);//retoune true quand le robot est dans un coin
bool test_deplacement(int posx, int posy);//retourne true si un bloc est sur cette case, false sinon
bool presence_bloc(int *posx, int *posy, int orientation);//retourne true si le robot est devant un bloc, false sinon
bool suis_je_dans_un_coin(int *posx, int *posy, int *orientation);//retourne true si l'on est dans un coin, false sinon
int lire_distance(int *posx, int *posy, int orientation);
