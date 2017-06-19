#include "fonctions_2.h"
int main(void)
{
  //int i = 0;
  posx = INITX;
  posy = INITY;
  orientation = 6;
  deplacement_effectue = false;

  initialisation();
  affichage(0);
  placer_robot(posx,posy,orientation);
  affichage(1);/*
  deplacement(&posx,&posy,orientation,6);
  affichage(1);
  pivoter_droite(&posx,&posy,&orientation);
  affichage(1);
  deplacement(&posx,&posy,orientation,5);
  affichage(1);
  reculer_robot(&posx,&posy,orientation);
  affichage(1);
  reculer_robot(&posx,&posy,orientation);
  affichage(1);
  reculer_robot(&posx,&posy,orientation);
  affichage(1);
  deplacement(&posx,&posy,orientation,-1);*/
  trouver_coin(&posx, &posy, orientation);
  printf("%s\n", (suis_je_dans_un_coin(&posx, &posy, &orientation) ? "oui":"non"));
  affichage(1);

  emission("message");
  wait_for("message");

  orienter_nord();
  quel_angle();

  correction_position();

  check();
  verifier_position();
  determinerRDV();
  allerRDV();
  return 0;
}


/*


trouver_coin(&posx, &posy, orientation);
//affichage(2);
deplacement(&posx, &posy, orientation, 1);
affichage(1);
pivoter_droite(&posx,&posy,&orientation);
affichage(1);
deplacement(&posx, &posy, orientation, 3);
affichage(1);
pivoter_droite(&posx,&posy,&orientation);
pivoter_droite(&posx,&posy,&orientation);
deplacement(&posx, &posy, orientation, 5);
affichage(1);
pivoter_gauche(&posx,&posy,&orientation);
deplacement(&posx, &posy, orientation, 3);*/
