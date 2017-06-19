#include "fonctions_2.h"

int posyr;
int posxr;
int posrecu;
int pos;

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
