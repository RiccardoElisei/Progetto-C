#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"

struct Giocatore* giocatore = NULL;
struct Stanza* h = NULL;
struct Stanza* z = NULL;
struct Stanza* b = NULL;
struct Stanza* p = NULL;
struct Stanza* s = NULL;
struct Stanza* stanza_inizio = NULL;
struct Stanza* New = NULL;
int n_giocatori = 0;
static struct Stanza* crea_prima_stanza();
static enum Nome_giocatore *r_giocatori= NULL;
unsigned short quest_da_finire = 0;
unsigned short quest_limite = 0;
static void crea_giocatori();
static void insert_testa();
void stampa_giocatori();
static void inizia_gioco();
static void turni_giocatori();
static void avanza();
static void esegui_quest();
static void chiamata_emergenza();
static void uccidi_astronauta();
static void usa_botola();
static void sabotaggio();
static struct Stanza* crea_stanze();



const char* get_stanza(enum Tipo_stanza tipo){
  switch(tipo){
    case vuota: return "vuota";
    case quest_semplice: return "quest_semplice";
    case quest_complicata: return "quest_complicata";
    case botola: return "botola";
  }
}

const char* get_stato(enum Stato_giocatore stato){
  switch(stato){
    case impostore: return "impostore";
    case astronauta: return "astronauta";
    case assassinato: return "assassinato";
    case defenestrato: return "defenestrato";
  }
}
const char* get_color(enum Nome_giocatore colore){
  switch(colore){
    case rosso: return "rosso";
    case blu: return "blu";
    case giallo: return "giallo";
    case verde: return "verde";
    case viola: return "viola";
    case rosa: return "rosa";
    case arancione: return "arancione";
    case bianco: return "bianco";
    case nero: return "nero";
    case grigio: return "grigio";
  }
}



void Imposta_Gioco(){
  int impostori = 0;
  int n_imposotori1 = 0;
  int n_imposotori2 = 0;
  int n_imposotori3 = 0;
  int scelta = 0;
  do{
  printf("PRIMA DI INIZIARE A GIOCARE PREMI:\n -1) PER CREARE I GIOCATORI\n -2) PER USCIRE DALL'IMPOSTA GIOCO\n");
  scanf("%d", &scelta);
  switch (scelta){
    case 1:
    do {
      printf("inserisci il numero di giocatori\n");
      scanf("%d", &n_giocatori);
    } while(n_giocatori < 4 || n_giocatori > 10);
    giocatore = (struct Giocatore*) calloc(n_giocatori, sizeof(struct Giocatore));
    r_giocatori = (enum Nome_giocatore*)calloc(n_giocatori,sizeof(int));
    crea_giocatori();
    if (n_giocatori < 4){
      impostori = 1;
    }
    else if(n_giocatori < 7){
      impostori = ((rand ()%2)+1);
    }
    else{
      impostori = ((rand ()%3)+1) ;
    }
    if(impostori == 1){
      n_imposotori1 = rand() % n_giocatori;
      giocatore[n_imposotori1].stato = 1;
    }
    else if(impostori == 2){
      do {
        n_imposotori1 = rand() % n_giocatori;
        giocatore[n_imposotori1].stato = impostore;
        n_imposotori2 = rand() % n_giocatori;
        giocatore[n_imposotori2].stato = impostore;
      } while(n_imposotori1 == n_imposotori2);
    }
    else{
      do {
        n_imposotori1 = rand() % n_giocatori;
        giocatore[n_imposotori1].stato = impostore;
        n_imposotori2 = rand() % n_giocatori;
        giocatore[n_imposotori2].stato = impostore;
        n_imposotori3 = rand() % n_giocatori;
        giocatore[n_imposotori3].stato = impostore;
      } while(n_imposotori1 == n_imposotori2 || n_imposotori3 == n_imposotori1 || n_imposotori3 == n_imposotori2 );
    }
    for ( int i = 0; i < n_giocatori; i++){
      if(giocatore[i].stato != 1){
        giocatore[i].stato = 0;
      }
    }
    printf("\n");
    crea_prima_stanza();
    printf("\n");
    printf("\n");
    printf("INSERISCI IL NUMERO DI QUEST DA FINIRE DA PARTE DEGLI ASTRONAUTI PER VINCERE: \n");
    scanf("%hd", &quest_da_finire);
    printf("\n");
    int valore = 0;
    printf("Premi 1 per vedere chi sono i giocatori\n");
    scanf("%d", &valore);
    if(valore == 1 ){
      stampa_giocatori();
      printf("\n");
    }
    break;
    case 2:
    inizia_gioco();
    break;
    default:
    printf("HAI INSERITO UN VALORE NON VALIDO\n");
   }
 } while(scelta != 2);
}

static void crea_giocatori(){

  int c[n_giocatori];
  for(int i = 0; i < n_giocatori; i++)
  {
    c[i] = i;
  }
    for (int i = 0; i < n_giocatori; i++) {
      int t = c[i];
      int random = rand() % n_giocatori;
      c[i] = c[random];
      c[random] = t;
    }
    for(int i = 0; i < n_giocatori; i++){
      r_giocatori[i] = c[i];
      for(int k = 0; k < n_giocatori; k++){
        giocatore[i].colore = r_giocatori[i];
      }
    }
  }

 void stampa_giocatori(){
  for(int i = 0; i < n_giocatori; i++){
    printf("%s", get_stato(giocatore[i].stato));
    printf(" %s\n", get_color(giocatore[i].colore));
  }
}

  static struct Stanza* crea_prima_stanza(){
  stanza_inizio = (struct Stanza*) malloc(sizeof(struct Stanza));
  stanza_inizio -> avanti = NULL;
  stanza_inizio -> sinistra = NULL;
  stanza_inizio -> destra = NULL;
  stanza_inizio -> stanza_precedente = NULL;
  stanza_inizio -> bool = false;
  int x = ((rand()%100)+1);
  if(x < 20){
    stanza_inizio -> tipo = 2;
    printf("TIPOLOGIA DELLA STANZA : quest_complicata\n");
  }
  else if(x < 50){
    stanza_inizio -> tipo = 3;
    printf("TIPOLOGIA DELLA STANZA : botola\n");
  }
  else if(x < 70){
    stanza_inizio -> tipo = 1;
    printf("TIPOLOGIA DELLA STANZA : quest_semplice\n");
  }
  else if(x > 70) {
    stanza_inizio -> tipo = 0;
    printf("TIPOLOGIA DELLA STANZA : vuota\n");
  }
  printf("\n");
  printf("L'INDIRIZZO DELLA STANZA E' : %p\n", stanza_inizio);
  printf("\n");
  for(int i = 0; i < n_giocatori; i++){
    giocatore[i].posizione = stanza_inizio;
  }
  printf("i giocatori si trovano nella stanza inziale %p\n", giocatore->posizione);
  printf("\n");
  return stanza_inizio;
}

void Gioca(){
  int q = 0;
  int w = 0;
  int e = 0;
  int *g;
  int *u;
  int *o;
  int *x;
  int y = 0;
  int v = 0;
  int *c;
  int scelta = 0;
  printf("\n");
  printf("BENVENUTO IN GIOCA QUI POTRAI SCEGLIERE TUTTE LE AZIONE POSSIBILI DA FARE. BUONA PARTITA\n");
  printf("\n");
  printf("ORA SCOPRI IL TURNO DEI GIOCATORI\n");
  do{
    for(int j = 0; j < n_giocatori; j++){
      q = 0;
      w = 0;
      e = 0;
      u = &q;
      o = &w;
      x = &e;
      turni_giocatori(giocatore, n_giocatori);
      for(int i = 0; i < n_giocatori; i++){
        c = &i;
        printf("\n");
        printf("Turno del %s\n", get_color(giocatore[i].colore));
        if(giocatore[i].stato == assassinato || giocatore[i].stato == defenestrato){
          printf("\n");
          printf("NON TI PUOI MUOVERE SEI STATO ASSASSINATO O DEFENESTRATO\n");
          printf("\n");
          continue;
        }
        else{
          printf("\n");
          printf("Nella tua stanza che è di tipo %s si trovano i giocatori : \n", get_stanza((giocatore[i].posizione)->tipo));
          printf("\n");
          for(int v = 0; v < n_giocatori; v++){
            if(v != i){
              if(giocatore[v].posizione == giocatore[i].posizione){
                printf("%s\n", get_color(giocatore[v].colore));
              }
            }
            else{
              continue;
            }
          }
          printf("\n");
          do{
            printf("PREMI UN VALORE PER SCEGLIERE COSA FARE :\n 1) AVANZA\n 2) ESEGUI_QUEST\n 3) CHAIMATA_EMERGENZA\n 4) UCCIDI_ASTRONAUTA\n 5) USA_BOTOLA\n 6) SABOTAGGIO\n");
            scanf("%d", &scelta);
            switch(scelta){
              case 1:
              avanza(giocatore[i], u, o, x);
              giocatore[i].posizione = p;
              giocatore[i].posizione -> stanza_precedente = s;
              break;
              case 2:
              if(giocatore[i].stato == astronauta){
                if(giocatore[i].posizione -> tipo == 1 || giocatore[i].posizione -> tipo == 2){
                  esegui_quest(giocatore[i]);
                  giocatore[i].posizione -> tipo = vuota;
                }
                else{
                  printf("NON SEI IN UNA STANZA DI TIPO QUEST_SEMPLICE O COMPLICATA OPPURE LA QUEST E' STATA ELIMINATA\n");
                  i--;
                }
              }
              else{
                printf("NON SEI UN ASTRONAUTA\n");
                i--;
              }
              break;
              case 3:
              for(int a = 0; a < n_giocatori; a++){
                if(giocatore[a].posizione == giocatore[i].posizione){
                  if(giocatore[a].stato == assassinato){
                    v = v + 1;
                  }
                }
              }
              if(v >= 1){
                printf(" NELLA TUA STANZA SONO PRESENTI %d ASSSASSINATI", v);
                chiamata_emergenza(giocatore, c);
              }
              else{
                printf("NON PUOI EFFETTUARE LA CHIAMATA DI EMERGENZA SCEGLI UN'ALTRA AZIONE\n");
                i--;
              }
              break;
              case 4:
              if(giocatore[i].stato == impostore){
                for(int t = 0; t < n_giocatori; t++){
                  if(giocatore[t].posizione == giocatore[i].posizione -> stanza_precedente){
                    y = y + 1;
                  }
                  g = &y;
                }
                uccidi_astronauta(giocatore, c, g);
              }
              else{
                printf("NON PUOI SCEGLIERE QUESTA AZIONE NON SEI UN IMPOSTORE\n");
                i--;
              }
              break;
              case 5:
              if(giocatore[i].stato == impostore){
                if((giocatore[i].posizione) -> tipo == botola){
                  usa_botola(giocatore[i]);
                }
                else{
                  printf("LA STANZA IN CUI TI TROVI NON E' DI TIPO BOTOLA\n");
                  i--;
                }
              }
              else{
                printf("NON SEI UN IMPOSTORE\n");
                i--;
              }
              break;
              case 6:
              if(giocatore[i].stato == impostore){
                if(giocatore[i].posizione -> tipo == quest_semplice || giocatore[i].posizione -> tipo == quest_complicata){
                  sabotaggio();
                }
                else{
                  printf("NON TI TROVI IN UNA STANZA DI TIPO QUEST SEMPLICE O COMPLICATA\n");
                  i--;
                }
              }
              else{
                printf("NON SEI UN IMPOSTORE\n");
                i--;
              }
              break;
              default:
              printf("\n");
              printf("HAI IMMESSO UN VALORE ERRATO\n");
              printf("\n");
            }
          }while(scelta > 6);
        }
      }
    }
  } while(scelta != 6);
}

void Termina_Gioco(){
  if(giocatore != NULL){
    free(giocatore);
    giocatore = NULL;
  }
  else{
    printf("NON CI SONO GIOCATORI\n");
  }
  if(stanza_inizio != NULL){
    free(stanza_inizio);
    stanza_inizio = NULL;
  }
  else{
    printf("NON E' PRESENTE LA STANZA INIZIALE\n");
  }
  if(r_giocatori != NULL){
    free(r_giocatori);
    r_giocatori = NULL;
  }
  else{
    printf("NON CI SONO GIOCATORI\n");
  }
  if(New != NULL){
    free(New);
    New = NULL;
  }
  else{
    printf("NON SONO PRESENTI STANZE\n");
  }
  printf("************************\n");
  printf("*   GIOCO CONCLUSO     *\n");
  printf("************************\n");
  exit(0);
}

static void inizia_gioco(){

  if(giocatore == NULL){
      printf("\n");
      printf("RITORNA ALLA IMPOSTA GIOCO\n");
      printf("\n");
      Imposta_Gioco();
      printf("\n");
    }
    else{
      printf("\n");
      printf("PUOI INIZIARE A GIOCARE");
      printf("\n");
      printf("\n");
      Gioca();
    }
    return;
  }

static void avanza (struct Giocatore giocatore, int* u, int* o, int* x){
  int direzione = 0;
  do {
    printf("SCEGLI IN QUALE DIREZIONE ANDARE : -1) AVANTI\n -2) DESTRA\n -3) SINISTRA\n -4)RIMANI FERMO\n");
    scanf("%d", &direzione);
    switch(direzione){
    case 1:
    if((*u) <= 0){
      if(giocatore.posizione -> avanti == NULL){
        giocatore.posizione -> avanti = crea_stanze(giocatore, direzione);
        printf("\n");
        printf("Il giocatore si trova nella stanza %p\n",giocatore.posizione -> avanti);
        h = giocatore.posizione -> avanti;
        p = giocatore.posizione -> avanti;
        (*u) = (*u) + 1;
      }
    }
    else{
      giocatore.posizione = h;
      printf("\n");
      printf("Il giocatore si trova nella stanza %p\n",giocatore.posizione);
      p = giocatore.posizione;
    }
    break;
    case 2:
    if((*o) <= 0){
      if(giocatore.posizione -> destra == NULL){
        giocatore.posizione -> destra = crea_stanze(giocatore, direzione);
        printf("\n");
        printf("Il giocatore si trova nella stanza %p\n",giocatore.posizione -> destra);
        z = giocatore.posizione -> destra;
        p = giocatore.posizione -> destra;
        (*o) = (*o) + 1;
      }
    }
    else{
      giocatore.posizione = z;
      printf("\n");
      printf("Il giocatore si trova nella stanza %p\n", giocatore.posizione);
      p = giocatore.posizione;
    }
    break;
    case 3:
    if((*x) <= 0){
      if(giocatore.posizione -> sinistra == NULL){
        giocatore.posizione -> sinistra = crea_stanze(giocatore, direzione);
        printf("\n");
        printf("Il giocatore si trova nella stanza %p\n", giocatore.posizione -> sinistra);
        b = giocatore.posizione -> sinistra;
        p = giocatore.posizione -> sinistra;
        (*x) = (*x) + 1;
      }
    }
    else{
      giocatore.posizione = b;
      printf("\n");
      printf("Il giocatore si trova nella stanza %p\n", giocatore.posizione);
      p = giocatore.posizione;
    }
    break;
    case 4:
    New = giocatore.posizione;
    printf("Sei rimasto fermo nella stanza %p\n", New);
    p = New;
    break;
    default:
    printf("HAI INSERITO UN VALORE ERRATO\n");
   }
  }while(direzione > 4);
}

static struct Stanza* crea_stanze(struct Giocatore giocatore, int direzione){
  New = (struct Stanza*) malloc (sizeof(struct Stanza));
  int x = ((rand()%100)+1);
  if(x < 20){
    New -> tipo = 2;
    printf("TIPOLOGIA DELLA STANZA : quest_complicata\n");
  }
  else if(x < 50){
    New -> tipo = 3;
    printf("TIPOLOGIA DELLA STANZA : botola\n");
  }
  else if(x < 70){
    New -> tipo = 1;
    printf("TIPOLOGIA DELLA STANZA : quest_semplice\n");
  }
  else if(x > 70) {
    New -> tipo = 0;
    printf("TIPOLOGIA DELLA STANZA : vuota\n");
  }
  New -> avanti = NULL;
  New -> sinistra = NULL;
  New -> destra = NULL;
  New -> stanza_precedente = giocatore.posizione;
  New -> bool = false;
  New -> next = NULL;
  if(direzione == 1){
    giocatore.posizione -> avanti = New;
  }
  if(direzione == 2){
    giocatore.posizione -> destra = New;
  }
  if(direzione == 3){
    giocatore.posizione -> sinistra = New;
  }
  s = New -> stanza_precedente;
  insert_testa(New);
  return New;
}

static void insert_testa(struct Stanza *New){
  if(stanza_inizio == NULL){
    stanza_inizio = New;
  }
  else{
    New -> next = stanza_inizio;
    stanza_inizio = New;
  }
}

static void turni_giocatori(struct Giocatore *giocatore){
  int array[n_giocatori];
  struct Giocatore x[n_giocatori];
  for (int i = 0; i < n_giocatori ; i++) {
    array[i] = rand() % n_giocatori;
    for (int v = 0; v < i ; v++){
      if(array[i] == array[v]){
        i--;
        break;
      }
    }
  }
  for(int j = 0; j < n_giocatori; j++){
    x[j] = giocatore[array[j]];
  }
  for(int c = 0; c < n_giocatori; c++){
    giocatore[c] = x[c];
  }
}

  static void esegui_quest(struct Giocatore giocatore){
    if(((giocatore.posizione) -> tipo) == quest_semplice){
      quest_limite = quest_limite + 1;
     }
     else if(((giocatore.posizione) -> tipo) == quest_complicata){
       quest_limite = quest_limite + 2;
     }
     if(quest_limite >= quest_da_finire){
       printf("******************************************\n");
       printf("* GLI ASTRONAUTI HANNO VINTO COMPLIMENTI *\n");
       printf("******************************************\n");
       Termina_Gioco();
     }
  }

  static void chiamata_emergenza(struct Giocatore *giocatore, int* c){
    int d = 0;
    int b = 0;
    int x = ((rand()%125)+1);
    int s = (rand()%n_giocatori);
    for(int i = 0; i < n_giocatori; i++){
      if(giocatore[i].posizione == giocatore[*c].posizione){
        if(giocatore[i].stato == impostore){
        d = d + 1;
      }
      else if(giocatore[i].stato == astronauta){
        b = b + 1;
      }
    }
  }
  if(giocatore[s].posizione == giocatore[*c].posizione){
    if(giocatore[s].stato == impostore){
      if(x <= (30 + ((20 * b) - (30 * d)))){
        giocatore[s].stato = defenestrato;
        printf("GIOCATORE %s SEI STATO DEFENESTRATO.\n", get_color(giocatore[s].colore));
        printf("*******************\n");
        printf("*    GAME OVER    *\n");
        printf("*******************\n");
      }
    }
    else if(giocatore[s].stato == astronauta){
      if(x <= (30 + ((20 * b) - (30 * d)))){
        giocatore[s].stato = defenestrato;
        printf("GIOCATORE %s SEI STATO DEFENESTRATO\n", get_color(giocatore[s].colore));
        printf("*******************\n");
        printf("*    GAME OVER    *\n");
        printf("*******************\n");
      }
    }
  }
  giocatore[*c].posizione -> bool = true;
}

  static void uccidi_astronauta(struct Giocatore *giocatore, int* c, int* g){
    int d = 0;
    int a = 0;
    int scelta = 0;
    int x = ((rand()%125)+1);
    printf("I GIOCATORI CHE PUOI UCCIDERE SONO : \n");
    for(int i = 0; i < n_giocatori; i++){
      if(giocatore[i].colore != giocatore[*c].colore){
        if((giocatore[i].posizione) == (giocatore[*c].posizione)){
          if(giocatore[i].stato == astronauta){
            printf("%d) %s\n",i, get_color(giocatore[i].colore));
            a = a + 1;
          }
        }
      }
    }
    for(int i = 0; i < n_giocatori; i++){
      if(giocatore[i].posizione == giocatore[*c].posizione && giocatore[i].stato == astronauta){
        printf("\n");
        d = d + i;
      }
    }
    if(d < 0){
      printf("\n");
      printf("NON CI SONO ASTRONAUTI DA UCCIDERE\n");
    }
    else{
    do{
      printf("\n");
      printf("SCEGLI QUALE GIOCATORE UCCIDERE\n");
      scanf("%d", &scelta);
      printf("\n");
      if(giocatore[scelta].posizione == giocatore[*c].posizione && giocatore[scelta].stato == astronauta){
        printf("HAI SCELTO DI UCCIDERE IL GIOCATORE %s\n", get_color(giocatore[scelta].colore));
        printf("\n");
        giocatore[scelta].stato = assassinato;
        printf("\n");
        printf("IL GIOCATORE %s E' DIVENTATO %s\n", get_color(giocatore[scelta].colore), get_stato(giocatore[scelta].stato));
        printf("\n");
        a--;
        printf("\n");
        if(x <= (a * 50) + ((*g) * 20)){
          giocatore[*c].stato = defenestrato;
          printf("GIOCATORE %s SEI STATO SCOPERTO.\n", get_color(giocatore[*c].colore));
          printf("*******************\n");
          printf("*    GAME OVER    *\n");
          printf("*******************\n");
        }
        else{
          printf("GIOCATORE %s NON SEI STATO SCOPERTO\n", get_color(giocatore[*c].colore));
        }
      }
    }while(giocatore[scelta].posizione != giocatore[*c].posizione && giocatore[scelta].stato == astronauta);
  }
}


static void usa_botola(struct Giocatore giocatore){
  int count_botole = 0;
  int count_stanze = 0;
  int count_stanze1 = 0;
  int var_botola = 0;
  int var_stanza = 0;
  int i = 0;
  struct Stanza* punt_scorr = stanza_inizio;
  while(punt_scorr != NULL){
    if(punt_scorr -> tipo == 3){
      count_botole = count_botole + 1;
      punt_scorr = punt_scorr -> next;
      count_stanze = count_stanze + 1;
    }
    else{
      punt_scorr = punt_scorr -> next;
      count_stanze = count_stanze + 1;
    }
    count_stanze1 = count_stanze1 + 1;
  }
  if(count_botole > 1){
    struct Stanza* punt_scorr = stanza_inizio;
    do {
      punt_scorr = NULL;
      punt_scorr = stanza_inizio;
      int var_botola = (rand()%count_stanze);
      while(var_botola >= 0){
        punt_scorr = punt_scorr -> next;
        var_botola--;
      }
      if(punt_scorr != giocatore.posizione){
      if(punt_scorr -> tipo == 3){
        giocatore.posizione = punt_scorr;
        printf("Il giocatore si trova nella stanza di tipo %s con indirizzo %p\n", get_stanza(giocatore.posizione->tipo), giocatore.posizione);
        break;
      }
    }
      else{
        punt_scorr = NULL;
        punt_scorr = stanza_inizio;
        continue;
      }
    } while(punt_scorr != NULL);
  }
  else{
    struct Stanza* punt_scorr = stanza_inizio;
    do {
      punt_scorr = NULL;
      punt_scorr = stanza_inizio;
      var_stanza = (rand()%count_stanze1);
      while(var_stanza >= 0){
        punt_scorr = punt_scorr -> next;
        var_stanza--;
      }
      if(punt_scorr != giocatore.posizione){
        giocatore.posizione = punt_scorr;
        printf("Il giocatore si trova nella stanza di tipo %s con indirizzo %p\n", get_stanza(giocatore.posizione->tipo), giocatore.posizione);
        break;
      }
      else{
        punt_scorr = NULL;
        punt_scorr = stanza_inizio;
        continue;
      }
    } while(punt_scorr != NULL);
  }
}

  static void sabotaggio(struct Giocatore giocatore){
    giocatore.posizione -> tipo = vuota;
    printf("La stanza è diventata vuota\n");
  }
