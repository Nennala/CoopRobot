#include <stdio.h>

#define SIZETAB 8 //taille des tableaux

char tab1[SIZETAB] = { 0 }; // je défini ici deux tableaux afin qu'ils soient accéssibles dans tout mon code
char tab2[SIZETAB] = { 0 };

void initialisation(void) //permet d'innitaliser les tableaux à une valeur choisi, poru l'instant 0
{
  int i = 0;

  printf("\ndébut de l'innitialisation\n\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du premier tableau
    {
      tab1[i] = '0';
      printf("tab1[%d] = %c \n\r", i, tab1[i]);
    }

    printf("\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du second tableau
    {
      tab2[i] = '0';
      printf("tab2[%d] = %c \n\r", i, tab2[i]);
    }

    printf("\nfin de l'innitialisation\n\n");
}

void affichage(void)//permet d'afficher les deux tableaux dans le terminal
{
  int i = 0;
  for (i = 0; i < SIZETAB; i++)
    {
      printf("tab1[%d] = %c \n\r", i, tab1[i]);
    }

  printf("\n");

  for (i = 0; i < SIZETAB; i++)
    {
      printf("tab2[%d] = %c \n\r", i, tab2[i]);
    }

  printf("\n affichage terminé\n\n");
}

void put(int tab, int pos)// permet de placer un caractère 'x' dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau
{
  printf("positionnement d'un caractère en position %i du tableau %d\n\n", pos, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 1 : tab1[pos] = 'x';
    break;

    case 2 : tab2[pos] = 'x';
    break;

    default : printf("error_put\n");// message d'erreur si le tableau n'existe pas
  }
}

void sppr(int tab, int pos)// permet de supprimer un caractère dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau. Le caractère est remplacé par '0'.
{
  printf("suppression du caractère en position %i du tableau %d\n\n", pos, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 1 : tab1[pos] = '0';
    break;

    case 2 : tab2[pos] = '0';
    break;

    default : printf("error_sppr\n");// message d'erreur si le tableau n'existe pas
  }
}

void compare(void){// voici le but de tout ce code, écrire une foncion permettant parcourir deux tableaux, comparer leur valeur, identifier, signaler et dénombrer les caractères différents.
  int i = 0;
  char caractere;// me sert à afficher le caractère
  int denombrement =0;// contient le nombre de caractères identiques
  for (i = 0; i < SIZETAB; i++) {
    if (tab1[i] != tab2[i] && !(tab1[i] == '0' && tab2[i] == '0'))// on ne prend pas en compte le caractère '0' comme ressemblance
    {
      caractere = tab1[i];// pas encore trés pertinent, mais ce n'est pas forcément utile pour le moment
      printf("caractère différent : %c, en position %d\n\n", caractere, i);// signalement
      denombrement ++;
    }
  }
  printf("%d caractère(s) différent(s)\n\n", denombrement);//affichage du nombre de caractères identiques
}

int main(void) {//ma fonction main, relativement simple en somme

  initialisation();//initialise et affiche les tableaux à l'état initial
  put(1,2);// je place un caractère dans le tableau 1, en position 2
  put(2,2);// je place un même caractère dans le tableau 2, aussi en position 2
  affichage();// j'affiche le deux tableaux afin de pouvoir vérifier le bon fonctionnement de mes fonctions
  compare();// je compare, je devrai donc n'avoir aucun caractères différents
  sppr(1,2);// je supprime le caractère précédement placé dans le tableau 1
  compare();// je compare une seconde fois, je devrais maintenant avoir une différence entre les deux tableaux
  affichage();// là encore j'affiche pour pouvoir vérifier moi même

  return 0;
}
