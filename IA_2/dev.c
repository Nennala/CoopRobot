#include <stdio.h>
#include <bool.h>

bool suis_je_dans_un_coin(void)//retourne true si l'on est dans un coin, false sinon
{
  pivoter_droite();
  if (lire_distance() = 0)
  {
    pivoter_droite();
    pivoter_droite();
    if (lire_distance() != 0)
    {
      pivoter_droite();
      return true;
    }
    else
    {
      printf("nous somme sur la même case\n");
      return false;
    }
  }
  else
  {
    pivoter_gauche();
    pivoter_gauche();
    if (lire_distance() = 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

bool presence_bloc(void)//retourne true si le robot est devant un bloc, false sinon
{
  if (lire_distance())
  {
    return false;
  }
  else
  {
    return true
  }
}

bool trouver_coin(void)//retoune true quand le robot est dans un coin
{
  while (!suis_je_dans_un_coin())
  {
    while (presence_bloc())
      {
        avancer_robot();
      }

    pivoter_droite();

    while (!suis_je_dans_un_coin())
      {
        avancer_robot();
      }

    pivoter_gauche();
  }
  return true;
}
