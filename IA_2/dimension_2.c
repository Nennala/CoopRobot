#include <stdio.h>

#define SIZETAB 8 //taille des tableaux

char tab1[SIZETAB][SIZETAB]; // je défini ici deux tableaux afin qu'ils soient accessibles dans tout mon code
char tab2[SIZETAB][SIZETAB];



void initialisation(void) //permet d'innitaliser les tableaux à une valeur choisi, poru l'instant 0
{
  int i = 0;
  int j = 0;

  printf("\ndébut de l'innitialisation\n\n");
  printf("tableau 1\n\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du premier tableau
    {
      for (j = 0; j < SIZETAB; j++) {
        tab1[i][j] = '0';
        printf("tab1[%d][%d]= %c  ", i,j, tab1[i][j]);
      }
    printf("\n");
    }

    printf("\n");
    printf("tableau 2\n\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du second tableau
    {
      for (j = 0; j < SIZETAB; j++) {
        tab2[i][j] = '0';
        printf("tab2[%d][%d]= %c  ", i,j, tab2[i][j]);
      }
    printf("\n");
    }

    printf("\nfin de l'innitialisation\n\n");
}

void affichage(void)//permet d'afficher les deux tableaux dans le terminal
{
  int i = 0;
  int j = 0;

  printf("affichage du tableau 1\n\n");

  for (i = 0; i < SIZETAB; i++)
    {
      for (j = 0; j < SIZETAB; j++) {
        printf("tab1[%d][%d]= %c  ", i, j, tab1[i][j]);
      }

        printf("\n");
    }

        printf("\n");
        printf("affichage du tableau 2\n\n");

  for (i = 0; i < SIZETAB; i++)
    {
      for (j = 0; j < SIZETAB; j++) {
        printf("tab2[%d][%d]= %c  ", i, j, tab2[i][j]);
      }

        printf("\n");
    }

  printf("\n affichage terminé\n\n");
}

void put(int tab, int posx, int posy)// permet de placer un caractère 'x' dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau
{
  printf("positionnement d'un caractère en position ( %d, %d ) du tableau %d\n\n", posx, posy, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 1 : tab1[posx][posy] = 'x';
    break;

    case 2 : tab2[posx][posy] = 'x';
    break;

    default : printf("error_put\n");// message d'erreur si le tableau n'existe pas
  }
}

void sppr(int tab, int posx, int posy)// permet de supprimer un caractère dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau. Le caractère est remplacé par '0'.
{
  printf("suppression du caractère en position ( %d, %d ) du tableau %d\n\n", posx, posy, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 1 : tab1[posx][posy] = '0';
    break;

    case 2 : tab2[posx][posy] = '0';
    break;

    default : printf("error_sppr\n");// message d'erreur si le tableau n'existe pas
  }
}

void compare(void){// voici le but de tout ce code, écrire une foncion permettant parcourir deux tableaux, comparer leur valeur, identifier, signaler et dénombrer les caractères différents.
  int i = 0;
  int j = 0;
  char caractere;// me sert à afficher le caractère
  int denombrement =0;// contient le nombre de caractères identiques
  for (i = 0; i < SIZETAB; i++)
  {
    for (j = 0; j < SIZETAB; j++)
    {
      if (tab1[i][j] != tab2[i][j] && !(tab1[i][j] == '0' && tab2[i][j] == '0'))// on ne prend pas en compte le caractère '0' comme ressemblance
      {
        caractere = tab1[i][j];// pas encore trés pertinent, mais ce n'est pas forcément utile pour le moment
        printf("caractère différent : %c, en position ( %d, %d )\n\n", caractere, i, j);// signalement
        denombrement ++;
      }
    }
  }
  printf("%d caractère(s) différent(s)\n\n", denombrement);//affichage du nombre de caractères identiques
}


int main(void)
{
  initialisation();
  affichage();
  put(1,0,0);
  compare();
  put(1,0,1);
  compare();
  affichage();
  sppr(1,0,1);
  compare();
  affichage();
  return 0;
}
