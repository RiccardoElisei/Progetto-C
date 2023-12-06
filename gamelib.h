#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Imposta_Gioco();
void Gioca();
void Termina_Gioco();



enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};
enum Nome_giocatore {rosso, blu, giallo, verde, viola, rosa, arancione, bianco, nero, grigio};
enum Tipo_stanza {vuota, quest_semplice, quest_complicata, botola};
enum chiamata_emergenza {false, true};

struct Stanza {
  struct Stanza *avanti;
  struct Stanza *sinistra;
  struct Stanza *destra;
  struct Stanza *stanza_precedente;
  struct Stanza *next;
  enum Tipo_stanza tipo;
  enum chiamata_emergenza bool;
};

struct Giocatore {
   struct Stanza *posizione;
   enum Stato_giocatore stato;
   enum Nome_giocatore colore;
 };

void Imposta_Gioco();
void Gioca();
void Termina_Gioco();
