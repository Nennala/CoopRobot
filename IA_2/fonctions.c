#include "fonctions.h"

int posyr;
int posxr;
int posrecu;
int pos;

void initialisation(void) //permet d'innitaliser les tableaux à une valeur choisi, poru l'instant 0
{
  int i = 0;
  int j = 0;

  printf("\ndébut de l'innitialisation\n\n");
  printf("tableau 1\n\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du premier tableau
    {
      for (j = 0; j < SIZETAB; j++) {
        tab1[i][j] = '-';
        //printf("tab1[%d][%d]= %c  ", i,j, tab1[i][j]);
      }
    //printf("\n");
    }

    printf("\n");
    printf("tableau 2\n\n");

  for (i = 0; i < SIZETAB; i++)// innitialisation du second tableau
    {
      for (j = 0; j < SIZETAB; j++) {
        tab2[i][j] = '-';
        //printf("tab2[%d][%d]= %c  ", i,j, tab2[i][j]);
      }
    //printf("\n");
    }

    carte_vierge();

    printf("\nfin de l'innitialisation\n\n");
}

void affichage(int choix)//permet d'afficher les deux tableaux dans le terminal
{
  int i = 0;
  int j = 0;


  if (choix == 1)
  {
    printf("affichage du tableau 1\n\n");
    for (i = 0; i < SIZETAB; i++)
      {
        for (j = 0; j < SIZETAB; j++) {
          printf(" %c ",tab1[i][j]);
        }

          printf("\n");
      }
  }
        printf("\n");

  if (choix == 2) {
    printf("affichage du tableau 2\n\n");
    for (i = 0; i < SIZETAB; i++)
      {
        for (j = 0; j < SIZETAB; j++) {
          printf(" %c ",tab2[i][j]);
        }

          printf("\n");
      }
    }

  if (choix == 0) {
    printf("affichage du terrain\n\n");
    for (i = 0; i < SIZETAB; i++)
      {
        for (j = 0; j < SIZETAB; j++) {
          printf(" %c ",tab0[i][j]);
        }

          printf("\n");
      }
    }
  printf("\n affichage terminé\n\n");
}

void put(int tab, int posx, int posy, char car)// permet de placer un caractère 'x' dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau
{
  //printf("positionnement d'un caractère en position ( %d, %d ) du tableau %d\n\n", posx, posy, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 0 : tab0[posx][posy] = car;
    break;

    case 1 : tab1[posx][posy] = car;
    break;

    case 2 : tab2[posx][posy] = car;
    break;

    default : printf("error_put\n");// message d'erreur si le tableau n'existe pas
  }
}

void sppr(int tab, int posx, int posy)// permet de supprimer un caractère dans un tableau. Le premier argument est le tableau à modifier et le second argument est la position dans ce tableau. Le caractère est remplacé par '-'.
{
 //  printf("suppression du caractère en position ( %d, %d ) du tableau %d\n\n", posx, posy, tab );
  switch (tab) { //avec un switch il sera possible rajouter des tableaux si nécéssaire
    case 1 : tab1[posx][posy] = '-';
    break;

    case 2 : tab2[posx][posy] = '-';
    break;

    default : printf("error_sppr\n");// message d'erreur si le tableau n'existe pas
  }
}

void compare(void)// voici le but de tout ce code, écrire une foncion permettant parcourir deux tableaux, comparer leur valeur, identifier, signaler et dénombrer les caractères différents.
{
  int i = 0;
  int j = 0;
  char caractere;// me sert à afficher le caractère
  int denombrement =0;// contient le nombre de caractères identiques
  for (i = 0; i < SIZETAB; i++)
  {
    for (j = 0; j < SIZETAB; j++)
    {
      if (tab1[i][j] != tab2[i][j] && !(tab1[i][j] == '-' && tab2[i][j] == '-'))// on ne prend pas en compte le caractère '-' comme ressemblance
      {
        caractere = tab1[i][j];// pas encore trés pertinent, mais ce n'est pas forcément utile pour le moment
        printf("caractère différent : %c, en position ( %d, %d )\n\n", caractere, i, j);// signalement
        denombrement ++;
      }
    }
  }
  printf("%d caractère(s) différent(s)\n\n", denombrement);//affichage du nombre de caractères identiques
}

void carte_vierge(void)
{
  int i=0;
  int j=0;

  for (i = 0; i < SIZETAB; i++)// innitialisation du tableau
    {
      for (j = 0; j < SIZETAB; j++) {
        tab0[i][j] = '-';
      }
    //printf("\n");
    }

    printf("\n");

  for (i = 0; i < SIZETAB; i++)
  {
    put(0,0,i,'X'); //haut
    put(0,SIZETAB-1,i,'X');//bas
    put(0,i,0,'X'); //droite
    put(0,i,SIZETAB-1,'X'); //gauche
  }

  put(0,5,3,'X');
  put(0,5,2,'X');
  put(0,4,3,'X');
  put(0,4,2,'X');

  put(0,5,7,'X');
  put(0,5,6,'X');
  put(0,4,7,'X');
  put(0,4,6,'X');
}

void placer_robot(int posx, int posy, int orientation)
{
  char car = 'O';

  switch (orientation)
  {
    case 0:
    car = 'O';
    break;

    case 6:
    car = '6';
    break;

    case 8:
    car = '8';
    break;

    case 4:
    car = '4';
    break;

    case 2:
    car = '2';
    break;

    default:
    break;
  }

  put(1,posx,posy,car);
}

void avancer_robot(int *posx, int *posy, int orientation)
{
  sppr(1,*posx,*posy);//on enlève le robot de la position actuelle

  switch (orientation) {//on modifie la valeur pointée par posx et posy pour qu'elles contiennent la nouvelle position
    case 0:
    printf("orientation inconue\n");
    break;

    case 6:
    *posy = (*posy)+1;
    break;

    case 8:
    *posx = (*posx)-1;
    break;

    case 4:
    *posy = (*posy)-1;
    break;

    case 2:
    *posx = (*posx)+1;
    break;

    default:
    printf("orientation inconue\n");
    break;
  }
  if (test_deplacement(*posx,*posy))
  {
    put(1,*posx,*posy,'X');
    switch (orientation) {//remet les bonnes valeurs dans posx et posy
      case 0:
      break;

      case 6:
      *posy = (*posy)-1;
      break;

      case 8:
      *posx = (*posx)+1;
      break;

      case 4:
      *posy = (*posy)+1;
      break;

      case 2:
      *posx = (*posx)-1;
      break;

      default:
      break;
    }
    placer_robot(*posx,*posy,orientation);//on place le robot sur la case suivante
    deplacement_effectue = true;
  }
  else
  {
    placer_robot(*posx,*posy,orientation);//on replace le robot sur la case
    deplacement_effectue = false;
  }
}

void reculer_robot(int *posx, int *posy, int orientation)
{
  sppr(1,*posx,*posy);//on enlève le robot de la position actuelle

  switch (orientation)//on modifie la valeur pointée par posx et posy pour qu'elles contiennent la nouvelle position
  {
    case 0:
    printf("orientation inconue\n");
    break;

    case 6:
    *posy = (*posy)-1;
    break;

    case 8:
    *posx = (*posx)+1;
    break;

    case 4:
    *posy = (*posy)+1;
    break;

    case 2:
    *posx = (*posx)-1;
    break;

    default:
    printf("orientation inconue\n");
    break;
  }
  if (test_deplacement(*posx,*posy))
    {
      switch (orientation)//remet les bonnes valeurs dans posx et posy
        {
          case 0:
          break;

          case 6:
          *posy = (*posy)+1;
          break;

          case 8:
          *posx = (*posx)-1;
          break;

          case 4:
          *posy = (*posy)-1;
          break;

          case 2:
          *posx = (*posx)+1;
          break;

          default:
          break;
        }
      placer_robot(*posx,*posy,orientation);//on replace le robot sur la case initiale
      deplacement_effectue = true;
    }
  else
    {
      placer_robot(*posx,*posy,orientation);//on replace le robot sur la case
      deplacement_effectue = false;
    }
}

void pivoter_droite(int *posx, int *posy, int *orientation)
{
  switch (*orientation)
  {
    case 0:
    *orientation = 0;
    break;

    case 6:
    *orientation = 2;
    break;

    case 8:
    *orientation = 6;
    break;

    case 4:
    *orientation = 8;
    break;

    case 2:
    *orientation = 4;
    break;

    default:
    break;
  }
  placer_robot(*posx,*posy,*orientation);
}

void pivoter_gauche(int *posx, int *posy, int *orientation)
{
  switch (*orientation)
  {
    case 0:
    *orientation = 0;
    break;

    case 6:
    *orientation = 8;
    break;

    case 8:
    *orientation = 4;
    break;

    case 4:
    *orientation = 2;
    break;

    case 2:
    *orientation = 6;
    break;

    default:
    break;
  }
  placer_robot(*posx,*posy,*orientation);
}

void deplacement(int *posx, int *posy, int orientation, int distance)
{
  int i =0;
  if (distance > 0)
  {
    for (i = 0; i < distance; i++)
    {
      avancer_robot(posx, posy,orientation);
      affichage(1);
    }
  }
  else
  {
    for (size_t i = 0; i < -distance; i++)
    {
      reculer_robot(posx, posy, orientation);
      affichage(1);
    }
  }
}

bool test_deplacement(int posx, int posy)//retourne true si un bloc est sur cette case, false sinon
{
  if (tab0[posx][posy] == 'X')
  {
    printf("déplacement impossible\n\n");
    put(1,posx,posy,'X');
    return true;
  }
  else
  {
    printf("déplacement possible\n\n");
    return false;
  }
}

bool trouver_coin(int *posx, int *posy, int orientation)//retoune true quand le robot est dans un coin
{
  while (!suis_je_dans_un_coin(posx,posy,&orientation))
  {
    while (presence_bloc(posx,posy, orientation))
      {
        avancer_robot(posx,posy, orientation);
      }

    pivoter_droite(posx,posy,&orientation);

    while (presence_bloc(posx,posy,orientation))
      {
        avancer_robot(posx,posy, orientation);
      }

    pivoter_gauche(posx,posy,&orientation);
  }
  return true;
}

bool suis_je_dans_un_coin(int *posx, int *posy, int *orientation)// version 1 retourne true si l'on est dans un coin, false sinon
{
  int somme_ponderee = 0;

  if (tab0[*posx+1][*posy] == 'X')
  {
    somme_ponderee += 1;
  }
  if (tab0[*posx][*posy+1] == 'X')
  {
    somme_ponderee += 2;
  }
  if (tab0[*posx-1][*posy] == 'X')
  {
    somme_ponderee += 1;
  }
  if (tab0[*posx][*posy-1] == 'X')
  {
    somme_ponderee += 2;
  }
  printf("somme = %d\n", somme_ponderee);
  return (somme_ponderee == 3);
}
/*
bool suis_je_dans_un_coin(int *posx, int *posy, int *orientation)// version 1 retourne true si l'on est dans un coin, false sinon
{
  int i=0;
  int somme_ponderee = 0;
  for ( i = 0; i < 4; i++)
  {
    if(!presence_bloc(posx,posy,*orientation))
    {
      switch (i)
      {
        case 0:
        case 2:
          somme_ponderee += 1;
          break;
        case 1:
        case 3:
          somme_ponderee += 2;
          break;
        default:
          break;
      }
    }
    pivoter_droite(posx,posy,orientation);
    sppr(1,*posx,*posy);
    printf("somme_ponderee = %d\n", somme_ponderee);
  }
  return (somme_ponderee == 3);
}*/

bool presence_bloc(int *posx, int *posy, int orientation)//retourne true si le robot est devant un bloc, false sinon
{
  if (lire_distance(posx,posy,orientation) != 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}


int lire_distance(int *posx, int *posy, int orientation)//simulation : retourne 1 si il y a un bloc devant, 0 sinon
{
  switch (orientation)//on modifie la valeur pointée par posx et posy pour qu'elles contiennent la futur position
  {
    case 0:
    printf("orientation inconue\n");
    break;

    case 6:
    *posy = (*posy)+1;
    break;

    case 8:
    *posx = (*posx)-1;
    break;

    case 4:
    *posy = (*posy)-1;
    break;

    case 2:
    *posx = (*posx)+1;
    break;

    default:
    printf("orientation inconue\n");
    break;
  }

  if (test_deplacement(*posx,*posy))// test si il y a une bloc demain
    {
      switch (orientation)//remet les bonnes valeurs dans posx et posy
        {
          case 0:
          break;

          case 6:
          *posy = (*posy)-1;
          break;

          case 8:
          *posx = (*posx)+1;
          break;

          case 4:
          *posy = (*posy)+1;
          break;

          case 2:
          *posx = (*posx)-1;
          break;

          default:
          break;
        }
      return 1;
    }
  else
    {
      switch (orientation)//remet les bonnes valeurs dans posx et posy
        {
          case 0:
          break;

          case 6:
          *posy = (*posy)-1;
          break;

          case 8:
          *posx = (*posx)+1;
          break;

          case 4:
          *posy = (*posy)+1;
          break;

          case 2:
          *posx = (*posx)-1;
          break;

          default:
          break;
        }
      return 0;
    }


}

void emission(char *message)
{
  printf("%s\n", message);
}

bool wait_for(char *message)
{
  printf("wait for %s\n", message);
  return true;
}

void orienter_nord()
{
  while (orientation != 8)
  {
    pivoter_droite(&posx,&posy,&orientation);
  }
}

void quel_angle()
{
  if (presence_bloc(&posx,&posy,orientation))
    {
      posyr = 1;
    }
  else
    {
      posyr = 8;
    }
  emission("je suis dans tel angle");
}

void check()
{
  if (posrecu != pos)
    {
      emission("on continue");
      wait_for("on continue");
    }
  else
    {
      emission("on est sur la même case");
      verifier_position();
    }
}

bool verifier_position()
{
  pivoter_gauche(&posx,&posy,&orientation);
  if (presence_bloc(&posx,&posy,orientation))
    {
      emission("je suis face à un bloc");
      return true;
    }
  else
    {
      emission("tu es dans l'angle");
      correction_position();
      return false;
    }
}

void determinerRDV()
{
  switch (pos)
  {
    case 1:break;
  }
}


void correction_position()
{

}

void allerRDV()
{

}
