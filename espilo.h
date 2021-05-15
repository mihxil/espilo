
/**********************************************************************
*                                                                     *
*              ####  ### ###  ### #     ##          ##                *
*              #    #    #  #  #  #    #  #        #  #               *
*              ###   ##  ###   #  #    #  #    # #   #                *
*              #       # #     #  #    #  #    # #  #                 *
*              #### ###  #    ### ####  ##      #  ####               *
*                                                                     *
*                             espilo.h                                *
*                                                                     *
**********************************************************************/

/* gxeneralaj difinoj */
#define MAKS_SXANGXOJ   32

/* ISO 8859-3 Esperanto-literoj */
#define C_EGA   198     /* Ccircumflex */
#define C_ETA   230     /* ccircumflex */
#define G_EGA   216     /* Gcircumflex */
#define G_ETA   248     /* gcircumflex */
#define H_EGA   166     /* Hcircumflex */
#define H_ETA   182     /* hcircumflex */
#define J_EGA   172     /* Jcircumflex */
#define J_ETA   188     /* jcircumflex */
#define S_EGA   222     /* Scircumflex */
#define S_ETA   254     /* scircumflex */
#define U_EGA   221     /* Ubreve */
#define U_ETA   253     /* ubreve */

/* eniraj kaj eliraj formoj */
typedef enum {
  NEKONATA,
  UNUA_ENIRA,
  W,
  UNUA_ELIRA,
  ISO, PX, AC, PC, PT,
  FINA_ENIRA,
  FUN, TEX,
  FINA_ELIRA } FORMO;

/* tradukaj tabuloj */
#define PX_TABULO       24
unsigned char px_tabulo[PX_TABULO][3]={
    {'c','x',C_ETA}, {'c','X',C_ETA}, {'C','x',C_EGA}, {'C','X',C_EGA},
    {'g','x',G_ETA}, {'g','X',G_ETA}, {'G','x',G_EGA}, {'G','X',G_EGA},
    {'h','x',H_ETA}, {'h','X',H_ETA}, {'H','x',H_EGA}, {'H','X',H_EGA},
    {'j','x',J_ETA}, {'j','X',J_ETA}, {'J','x',J_EGA}, {'J','X',J_EGA},
    {'s','x',S_ETA}, {'s','X',S_ETA}, {'S','x',S_EGA}, {'S','X',S_EGA},
    {'u','x',U_ETA}, {'u','X',U_ETA}, {'U','x',U_EGA}, {'U','X',U_EGA}};

#define AC_TABULO       12
unsigned char ac_tabulo[AC_TABULO][3]={
    {'^','c',C_ETA}, {'^','C',C_EGA}, {'^','g',G_ETA}, {'^','G',G_EGA},
    {'^','h',H_ETA}, {'^','H',H_EGA}, {'^','j',J_ETA}, {'^','J',J_EGA},
    {'^','s',S_ETA}, {'^','S',S_EGA}, {'^','u',U_ETA}, {'^','U',U_EGA}};

#define PC_TABULO       12
unsigned char pc_tabulo[PC_TABULO][3]={
    {'c','^',C_ETA}, {'C','^',C_EGA}, {'g','^',G_ETA}, {'G','^',G_EGA},
    {'h','^',H_ETA}, {'H','^',H_EGA}, {'j','^',J_ETA}, {'J','^',J_EGA},
    {'s','^',S_ETA}, {'S','^',S_EGA}, {'u','^',U_ETA}, {'U','^',U_EGA}};

#define PT_TABULO       12
unsigned char pt_tabulo[PT_TABULO][3]={
    {'c','~',C_ETA}, {'C','~',C_EGA}, {'g','~',G_ETA}, {'G','~',G_EGA},
    {'h','~',H_ETA}, {'H','~',H_EGA}, {'j','~',J_ETA}, {'J','~',J_EGA},
    {'s','~',S_ETA}, {'S','~',S_EGA}, {'u','~',U_ETA}, {'U','~',U_EGA}};

#define FUN_TABULO      10
unsigned char fun_tabulo[FUN_TABULO][3]={
    {'c','h',C_ETA}, {'C','h',C_EGA}, {'g','h',G_ETA}, {'G','h',G_EGA},
    {'h','h',H_ETA}, {'H','h',H_EGA}, {'j','h',J_ETA}, {'J','h',J_EGA},
    {'s','h',S_ETA}, {'S','h',S_EGA}};

