/**********************************************************************
*                                                                     *
*              ####  ### ###  ### #     ##          ##                *
*              #    #    #  #  #  #    #  #        #  #               *
*              ###   ##  ###   #  #    #  #    # #   #                *
*              #       # #     #  #    #  #    # #  #                 *
*              #### ###  #    ### ####  ##      #  ####               *
*                                                                     *
*                             espilo.c                                *
*                                                                     *
**********************************************************************/

/***********************************************************************
*                                                                      *
* ESPILOv2.0                                                           *
*                                                                      *
* verkis Duncan C THOMSON                                              *
*                                                                      *
* programo por sxangxi inter diversaj formoj de la Esperanto-literoj   *
* prenas enirajxo de la norma enirejo, kaj elmetas al norma elirejo    *
*                                                                      *
* uzo:                                                                 *
*     espilo [[enira_formo] ... elira_formo]                           *
*                                                                      *
* versiono  dato      rimarkoj                                         *
*     0.0a  19930429  komencis programi                                *
*     0.4a  19930504  unua prov-programo                               *
*     1.0a  19930510  rekomencis novan version                         *
*     1.0d  19930512  dua prov-versio                                  *
*     2.0a  19930603  tria prov-versio                                 *
*     2.0b  19930609  unua publika versio                              *
*                                                                      *
***********************************************************************/

/***********************************************************************
*                                                                      *
* Cxi tiuj formoj estas uzeblaj, kaj estas difinitaj en la dosiero     *
* "espilo.h":                                                          *
*                                                                      *
* nomo ekzemplo                                             enire ele  *
*                                                                      *
* iso  ISO-8859-3 normo (ankaux ena formo)                   jes  jes  *
* px   posta ikso cx, SX, Gx, ux, hx, ktp                    jes  jes  *
* ac   antauxa cirkumflekso ^C, ^c, ^u ^s, ^h, ktp           jes  jes  *
* pc   posta cirkumflekso C^, c^, u^, s^, h^, ktp            jes  jes  *
* pt   posta tildo C~, c~, u~ s~ h~ ktp (por ordigado)       jes  jes  *
* w    sxangxas nur enira `w'                                jes   ne  *
* fun  fundamenta metodo: Ch, ch, u, sh, hh, ktp              ne  jes  *
* tex  elmetas en TeX / LaTeX formo                           ne  jes  *
*                                                                      *
* Estontece, espereble, la programo subtenos aliajn formojn, inkluzive *
* de "Unicode".  Cxu vi volas aliajn?                                  *
*                                                                      *
***********************************************************************/

/***********************************************************************
*                                                                      *
* Se vi havas iujn ajn rimarkojn pri la programo, bonvole mesagxu min  *
* <duncan@spd.eee.strathclyde.ac.uk> kaj diri al mi.  Espereble mi     *
* estontece plibonigos la programon, eble aldonante novajn enirajn kaj *
* elirajn formojn.  Cxi tiu programo estas havebla per `ftp' de la     *
* Esperanto-ftp-ejo cxe ftp.stack.urc.tue.nl (130.89.10.247) en la     *
* dosierujo /pub/esperanto/software.  Gxi eble estas havebla ankaux de *
* spd.eee.strathclyde.ac.uk (130.159.72.26) en la dosierujo            *
* /pub/misc/esperanto                                                  *
*                                                                      *
***********************************************************************/

/***********************************************************************
*                                                                      *
* Bonvole notu: la programo funkcias plej bone kiam vi uzas kiel eble  *
* plej malmultajn de eniraj formoj.  Ekzemple la antauxcirkumfleksa    *
* kaj postcirkumfleksa formoj, uzataj samtempe, povas eljxeti erarajn  *
* tekstojn.  Mi tial konsilas al vi, ke vi provu lauxeble uzi la       *
* programon en la formo "espilo enformo elformo", kaj eviti la formon  *
* "espilo elformo"                                                     *
*                                                                      *
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "espilo.h"


/************************************************************
*                                                           *
* int main(int argc, char *argv[])                          *
* cxi tiu funkcio estas la kerno de la programo.  Gxi       *
* ciklas dum estas teksto, kaj tradukas la tekston laux la  *
* eniraj sxangxoj, elmetante gxin samtempe.                 *
*                                                           *
************************************************************/
int main(argc,argv)
int argc;
char *argv[];
{
/* tiuj variabloj entenos la enirajn formojn, nombron de tiuj, kaj la
 * eliran formon */
int enira_formo_listo[MAKS_SXANGXOJ];
int eniraj_sxangxoj;
int elira_formo;

/* tiuj variabloj entenos la tri-literan tekstpecon, kiun traktas, kaj
 * la venontan literon, kiun elmetos */
unsigned char peco[3];
unsigned char elira_litero;

/* tiuj variabloj montros la staton de diversaj aferoj */

/* montros cxu litero estas preta por elmeti */
int eliro_preta;

/* montros cxu la fino de la teksto estas atingita - gxi povas preni
 * diversajn valorojn, depende de ekzakte kie estas la fino de la teksto:
 * 4 montras ke la teksto tute ne enhavas literojn (special kazo)
 * 3 montras ke peco entenas neniom da literojn
 * 2 montras ke peco entenas unu literon
 * 1 montras ke peco entenas du literojn
 */
int fino;

/* montros cxu sxangxo jam okazis.  Se la sxangxo estas ke la du unuaj
 * literoj farigxos unu litero, gxi prenas la valoron 2, se la sxangxo
 * estas ke nur unu litero sxangxis (la dua), aux ke neniu sxangxo jam
 * okazis, sed la finaj du literoj farigxos unu litero estontece, gxi
 * prenas la valoron 1 */
int jam_sxangx;

/* cikla variablo */
int i;

/* funkcioj */
void kontroli_komandlinion();
unsigned char legi_literon();
int traduki();
void elmeti();

/* eltrovi la eniran kaj elirajn formojn */
kontroli_komandlinion(argc,argv,enira_formo_listo,
    &eniraj_sxangxoj,&elira_formo);

/* statvariabloj */
fino=0; eliro_preta=0;

/* plenigi la tri-literan tekstvariablon */
peco[0]=legi_literon(&fino);
if (fino) fino++;
peco[1]=legi_literon(&fino);
peco[2]=legi_literon(&fino);

/* dum la teksto ne elcxerpigxas... */
while (fino < 3) {

  /* faru enirajn sxangxojn */
  for (i=0, jam_sxangx=0; ((i<eniraj_sxangxoj) && (!jam_sxangx)); i++)
    jam_sxangx=traduki(peco,enira_formo_listo[i]);

  /* elmeti literon, se preta */
  if (eliro_preta) elmeti(elira_litero,peco[0],elira_formo);

  /* movi venontan literon cele al eliro */
  elira_litero=peco[0];  eliro_preta=1;

  /* depende la la valoro de "jam_sxangx", decidi kiel fari */
  switch (jam_sxangx) {
    /* se jam_sxangx estas 0 aux 1, do simple movi cxiun literon en peco
     * kaj enprenu novan */
    case 0:
    case 1:
        peco[0]=peco[1]; peco[1]=peco[2];
        peco[2]=legi_literon(&fino); break;

    /* se jam_sxangx estas 2, do movi la trian literon al la unua, kaj
     * enprenu du pluajn literojn */
    case 2:
        peco[0]=peco[2];
        peco[1]=legi_literon(&fino);
        peco[2]=legi_literon(&fino); break;
    default:
        break;
    };
  };

/* se la teksto enhavis neniom da literoj, do elmetu neniun, alie jes */
if (fino != 4) elmeti(elira_litero,0,elira_formo);

return(0);
}


/************************************************************
*                                                           *
* void kontroli_komandlinion(int argc, char *argv[],        *
*     int *enira_formo_listo, int *eniraj_sxangxoj,         *
*     int *elira_formo)                                     *
* Cxi tiu funkcio kontrolas la komandlinion, kaj prenas el  *
* gxi la enirajn kaj eliran formojn.  Se neniu argumento    *
* ekzistas, la eniraj formoj estas cxiuj, kaj la elira      *
* formo estas ISO; se unu argumento ekzistas, gxi estas la  *
* elira formo - eliraj formoj estas cxiuj; se estas pli ol  *
* unu argumento, la fina estas la elira formo, la aliaj     *
* estas la eniraj formojn lauxorde.  La funkcio kontrolas   *
* la gxustecon de cxiu argumento                            *
*                                                           *
************************************************************/
void kontroli_komandlinion
(argc,argv,enira_formo_listo,eniraj_sxangxoj,elira_formo)
int argc;
char *argv[];
int *enira_formo_listo;
int *eniraj_sxangxoj;
int *elira_formo;
{
int i;
int dumtempa;

/* funkcioj */
int argv_al_numero();

*elira_formo=NEKONATA;

/* kalkulas la enirajn sxangxojn */
switch (argc) {
  /* se la komandlinio havas neniun argumenton, donas eraron */
  case 0: /* neniam okazos was 0*/
      fprintf(stderr,"Uzo: espilo [enira_formo] ... elira_formo\n"); exit(1);

  /* se neniu argumento cxeestas, uzu "ISO" kiel elira formo */
  case 1: /* was 1*/
      *elira_formo=ISO;
      /* kaj uzu cxiujn enirajn formojn, kiel por unu argumento (tial `break'
       * ne cxeestas) */

  /* se la komandlinio havas unu argumenton, faras liston de cxiuj eblaj
   * eniraj formoj */
  case 2: /* was 2*/
      dumtempa=0;
      for (i=UNUA_ENIRA+1; i<UNUA_ELIRA; i++) enira_formo_listo[dumtempa++]=i;
      for (i=UNUA_ELIRA+1; i<FINA_ENIRA; i++) enira_formo_listo[dumtempa++]=i;
      i=dumtempa;
      break;

  /* se la komandlinio havas pli ol unu argumentojn, eltrovas ilin */
  default:
      for (i=0; i<argc-2; i++) {
        dumtempa=argv_al_numero(argv[i+1]);
        if (dumtempa == NEKONATA) {
          fprintf(stderr,"Nekonata formo: %s\n",argv[i+1]); exit(1);};
        if ((dumtempa < UNUA_ENIRA) || (dumtempa > FINA_ENIRA)) {
          fprintf(stderr,"`%s' ne estas uzebla kiel enira formo\n",argv[i+1]);
          exit(1);};
        enira_formo_listo[i]=dumtempa;
        };
  };

/* kalkulas la nombron de eniraj sxangxoj */
*eniraj_sxangxoj=i;

/* kalkulas la eliran sxangxon, se gxi ne jam estas kalkulita */
if (*elira_formo == NEKONATA) {
  dumtempa=argv_al_numero(argv[argc-1]);
  if (dumtempa == NEKONATA) {
    fprintf(stderr,"Nekonata formo: %s\n",argv[argc-1]); exit(1);};
  if ((dumtempa < UNUA_ELIRA) || (dumtempa > FINA_ELIRA)) {
    fprintf(stderr,"`%s' ne estas uzebla kiel elira formo\n",argv[argc-1]);
    exit(1);};
  *elira_formo=dumtempa;
  };
}


/************************************************************
*                                                           *
* int argv_al_numero(char arg[])                            *
* Cxi tiu funkcio eltrovas la formon per kontroli cxu la    *
* donita tekstpeco samas unu el la permesataj formoj.  Gxi  *
* retrodonas la numeron de tiu formo, aux NEKONATA, se gxi  *
* konas tiun formon                                         *
*                                                           *
************************************************************/
int argv_al_numero(arg)
char arg[];
{
/* kalkulas la formon */
if (!strcmp(arg,"iso")) {
  return(ISO); }
else if (!strcmp(arg,"px")) {
  return(PX); }
else if (!strcmp(arg,"ac")) {
  return(AC); }
else if (!strcmp(arg,"pc")) {
  return(PC); }
else if (!strcmp(arg,"pt")) {
  return(PT); }
else if (!strcmp(arg,"w")) {
  return(W); }
else if (!strcmp(arg,"fun")) {
  return(FUN); }
else if (!strcmp(arg,"tex")) {
  return(TEX); }

/* nekonataj argumentoj */
else { return(NEKONATA);};
}


/************************************************************
*                                                           *
* unsigned char legi_literon(int *fino)                     *
* Cxi tiu funkcio legas la venontan literon.  Gxi redonas   *
* 0 kaj plialtigas la variablo "fino" po unu, se gxi trovis *
* EOF (fino de dosiero)                                     *
*                                                           *
************************************************************/
unsigned char legi_literon(fino)
int *fino;
{
int dumtempa;
dumtempa=getchar();
if (dumtempa == EOF) {
  (*fino)++;
  dumtempa=0;
  };
return(dumtempa);
}


/************************************************************
*                                                           *
* int traduki(unsigned char peco[3], int formo)             *
* Cxi tiu funkcio tradukas la tekstpecon laux la donita     *
* (enira) formo.  Se gxi sxangxas la du unuajn literojn al  *
* alia litero, gxi retrodonas "2".  Se gxi faras unuliteran *
* sxangxon, aux trovas du sxangxontajn literojn je la fino  *
* de la tekstpeco, gxi redonas "1".  Se gxi faras nenion    *
* kaj sxangxis nenion, gxi retrodonas "0"                   *
*                                                           *
************************************************************/
int traduki(peco,formo)
unsigned char peco[3];
int formo;
{
int i;
int sxangx;

/* komenca valoro */
sxangx=0;

/* elektu laux formo... */
switch (formo) {
  /* ISO -> neniu sxangxo */
  case ISO:
      break;

  /* PX -> ebleco de dulitera sxangxo */
  case PX:
      for (i=0; i<PX_TABULO; i++) {
        if ((peco[0] == px_tabulo[i][0]) && (peco[1] == px_tabulo[i][1])) {
          peco[0]=px_tabulo[i][2];  sxangx=2; break;};
        if ((peco[1] == px_tabulo[i][0]) && (peco[2] == px_tabulo[i][1])) {
          sxangx=1; break;};
        };
      break;

  /* AC -> ebleco de dulitera sxangxo */
  case AC:
      for (i=0; i<AC_TABULO; i++) {
        if ((peco[0] == ac_tabulo[i][0]) && (peco[1] == ac_tabulo[i][1])) {
          peco[0]=ac_tabulo[i][2];  sxangx=2; break;};
        if ((peco[1] == ac_tabulo[i][0]) && (peco[2] == ac_tabulo[i][1])) {
          sxangx=1; break;};
        };
      break;

  /* PC -> ebleco de dulitera sxangxo */
  case PC:
      for (i=0; i<PC_TABULO; i++) {
        if ((peco[0] == pc_tabulo[i][0]) && (peco[1] == pc_tabulo[i][1])) {
          peco[0]=pc_tabulo[i][2];  sxangx=2; break;};
        if ((peco[1] == pc_tabulo[i][0]) && (peco[2] == pc_tabulo[i][1])) {
          sxangx=1; break;};
        };
      break;

  /* PT -> ebleco de dulitera sxangxo *.
  case PT:
      for (i=0; i<PT_TABULO; i++) {
        if ((peco[0] == pt_tabulo[i][0]) && (peco[1] == pt_tabulo[i][1])) {
          peco[0]=pt_tabulo[i][2];  sxangx=2; break;};
        if ((peco[1] == pt_tabulo[i][0]) && (peco[2] == pt_tabulo[i][1])) {
          sxangx=1; break;};
        };
      break;

  /* W -> ebleco de nur unulitera sxangxo */
  case W:
      if (peco[1] == 'w') {peco[1]=U_ETA; sxangx=1;};
      if (peco[1] == 'W') {peco[1]=U_EGA; sxangx=1;};
      if (peco[0] == 'w') {peco[0]=U_ETA; sxangx=1;};
      if (peco[0] == 'W') {peco[0]=U_EGA; sxangx=1;};
      break;

  /* neniu alia formo */
  default:
        break;
  };

/* retrodoni */
return(sxangx);
}


/************************************************************
*                                                           *
* void elmeti(unsigned char litero, unsigned char venonta,  *
*     int formo)                                            *
* Cxi tiu funkcio elmetas literon laux la donita (elira)    *
* formo.  Gxi uzas la sekvontan literon por decidi kiel     *
* aperigi eventualajn duliterajn elmetajxojn (Cx aux CX?)   *
*                                                           *
************************************************************/
void elmeti(litero,venonta,formo)
unsigned char litero, venonta;
int formo;
{
int i;
int jam;

/* funkcioj */
int majuskla();

/* elmeti malsame, depende de la formo */
switch (formo) {
  /* ISO: tute simple elmeti */
  case ISO:
      printf("%c",litero);
      break;

  /* PX: postiksa formo - laux la tabulo, kaj kontroli la sekvantan literon
   * por decidi kian ikson uzi */
  case PX:
      for (jam=0,i=0;i<PX_TABULO;i+=2)
        if (litero==px_tabulo[i][2]) {
          printf("%c%c",px_tabulo[i][0],px_tabulo[i][1]-
              (32*(majuskla(litero) && majuskla(venonta))));
          jam=1;
          };
      if (!jam)
        printf("%c",litero);
      break;

  /* AC: laux la tabulo */
  case AC:
      for (jam=0,i=0;i<AC_TABULO;i++)
        if (litero==ac_tabulo[i][2]) {
          printf("%c%c",ac_tabulo[i][0],ac_tabulo[i][1]); jam=1;
          };
      if (!jam)
        printf("%c",litero);
      break;

  /* PC: laux la tabulo */
  case PC:
      for (jam=0,i=0;i<PC_TABULO;i++)
        if (litero==pc_tabulo[i][2]) {
          printf("%c%c",pc_tabulo[i][0],pc_tabulo[i][1]); jam=1;
          };
      if (!jam)
        printf("%c",litero);
      break;

  /* PT: laux la tabulo */
  case PT:
      for (jam=0,i=0;i<PT_TABULO;i++)
        if (litero==pt_tabulo[i][2]) {
          printf("%c%c",pt_tabulo[i][0],pt_tabulo[i][1]); jam=1;
          };
      if (!jam)
        printf("%c",litero);
      break;

  /* FUN: fundamenta - kontroli la sekvantan literon por decidu kia `h'
   * uzi.  Ankaux elmetu nur `u' por `ux' */
  case FUN:
      for (jam=0,i=0;i<FUN_TABULO;i++)
        if (litero==fun_tabulo[i][2]) {
          printf("%c%c",fun_tabulo[i][0],fun_tabulo[i][1]-
              (32*(majuskla(litero) && majuskla(venonta))));
          jam=1;
          };
      if (litero==U_ETA) {printf("u"); jam=1; }
      if (litero==U_EGA) {printf("U"); jam=1; }
      if (!jam)
        printf("%c",litero);
      break;

  /* TEX: simple elektu el la eblecoj */
  case TEX:
      switch (litero) {
        case C_ETA: printf("\\^{c}"); break;
        case G_ETA: printf("\\^{g}"); break;
        case H_ETA: printf("\\^{h}"); break;
        case J_ETA: printf("\\^{\\j}"); break;
        case S_ETA: printf("\\^{s}"); break;
        case U_ETA: printf("\\u{u}"); break;
        case C_EGA: printf("\\^{C}"); break;
        case G_EGA: printf("\\^{G}"); break;
        case H_EGA: printf("\\^{H}"); break;
        case J_EGA: printf("\\^{J}"); break;
        case S_EGA: printf("\\^{S}"); break;
        case U_EGA: printf("\\u{U}"); break;
        default: printf("%c",litero); break;
        };
      break;

  /* neniu alia formo */
  default: break;
  };
}


/************************************************************
*                                                           *
* int majuskla(unsigned char litero)                        *
* Cxi tiu funkcio retrodonas informon pri la majuskleco de  *
* litero.  Se la litero estas `a'-'z', aux unu el la        *
* malmajusklaj esperanto-literoj, gxi ne estas majuskla.    *
* Alie gxi ja estas.                                        *
*                                                           *
************************************************************/
int majuskla(litero)
unsigned char litero;
{
/* dumtempa variablo */
int dumtempa;
dumtempa=( ((litero>='a') && (litero<='z')) || (litero==C_ETA) ||
    (litero==G_ETA) || (litero==H_ETA) || (litero==J_ETA) ||
    (litero==S_ETA) || (litero==U_ETA) );
return(!dumtempa);
}

