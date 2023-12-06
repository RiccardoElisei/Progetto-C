#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

int main(){
  time_t t;
  srand((unsigned) time(&t));
  int scelta=3;
  printf("\n");
  printf("*****************************************************************************\n");
  printf("*                                 TRANNOI                                   *\n");
  printf("*****************************************************************************\n");
  printf("\n");
  printf("\n");
  printf("*****************************************************************************\n");
  printf("*                        BENVENUTO NEL MENU' PRINCIPALE                     *\n");
  printf("*****************************************************************************\n");
  printf("\n");
  printf("\n");
  do  {
      printf ("INSERISCI ORA UN COMANDO PER DECIDERE COSA FARE:\n\n-Inserisci 1 per impostare il gioco\n-Inserisci 2 per iniziare a giocare\n-Inserisci 3 per uscire dal gioco\n\n");
      scanf ("%d",&scelta);
      switch (scelta)
      {
          case 1:
              Imposta_Gioco();
              break;
          case 2:
              Gioca();
              break;
          case 3:
              Termina_Gioco();
              break;
          default:
              printf("\nIl valore inserito non è valido, si prega di inserire un valore intero compreso tra 1 e 3.\n\n");
      }
  } while (scelta !=3);
return 0;
}
