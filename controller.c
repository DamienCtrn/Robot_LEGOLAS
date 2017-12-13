/********
* ec2c version 0.67
* c file generated for node : controller 
* context   method = STATIC
* ext call  method = PROCEDURES
********/
/* This program needs external declarations */
#define _controller_EC2C_SRC_FILE
#include "controller.h"
/*--------
 * the following ``constants'' must be defined:
extern _real kp_teta;
extern _real ki_teta;
extern _real Te;
extern _real pi;
--------*/
/*--------
Internal structure for the call
--------*/
typedef struct  {
   
   //INPUTS
   _real _Cg;
   _real _Cd;
   _integer _Jean_Michel;
   //OUTPUTS
   _real _v_d;
   _real _v_g;
   //REGISTERS
   _real M30;
   _boolean M30_nil;
   _boolean M16;
   _boolean M16_nil;
   _boolean M11;
   _boolean M11_nil;
   _boolean M8;
} controller_ctx;

// Single Static Context
static controller_ctx ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void controller_I_Cg(_real V){
   ctx._Cg = V;
}
void controller_I_Cd(_real V){
   ctx._Cd = V;
}
void controller_I_Jean_Michel(_integer V){
   ctx._Jean_Michel = V;
}
extern void controller_O_v_d(_real);
extern void controller_O_v_g(_real);
#ifdef CKCHECK
extern void controller_BOT_v_d();
extern void controller_BOT_v_g();
#endif
/*--------
Internal reset input procedure
--------*/
static void controller_reset_input(){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void controller_reset(){
   ctx.M30_nil = _true;
   ctx.M16_nil = _true;
   ctx.M11_nil = _true;
   ctx.M8 = _true;
   controller_reset_input();
}
/*--------
Step procedure
--------*/
void controller_step(){
//LOCAL VARIABLES
   _boolean L7;
   _boolean L12;
   _boolean L6;
   _boolean L15;
   _boolean L14;
   _boolean L5;
   _boolean L19;
   _boolean L18;
   _boolean L17;
   _boolean L4;
   _real L28;
   _real L26;
   _real L35;
   _real L38;
   _real L34;
   _real L39;
   _real L25;
   _real L47;
   _boolean L46;
   _real L48;
   _real L45;
   _real L44;
   _real L51;
   _real L49;
   _real L43;
   _real L41;
   _real L24;
   _real L22;
   _real L3;
   _real L55;
   _real L54;
   _real L59;
   _real L58;
   _real L57;
   _real L53;
   _real L32;
   _real L31;
   _real T30;
   _boolean T16;
   _boolean T11;
//CODE
   if (ctx.M8) {
      L7 = _false;
   } else {
      L7 = ctx.M11;
   }
   L12 = (ctx._Jean_Michel <= 10);
   L6 = (L7 || L12);
   if (ctx.M8) {
      L15 = _false;
   } else {
      L15 = ctx.M16;
   }
   L14 = (! L15);
   L5 = (L6 && L14);
   L19 = (ctx._Cg <= 50.000000);
   L18 = (L5 && L19);
   L17 = (! L18);
   L4 = (L5 && L17);
   if (ctx.M8) {
      L28 = 0.000000;
   } else {
      L28 = ctx.M30;
   }
   L26 = (ki_teta * L28);
   L35 = (pi / 200.000000);
   L38 = (ctx._Cd - ctx._Cg);
   L34 = (L35 * L38);
   L39 = (kp_teta * L34);
   L25 = (L26 + L39);
   L47 = (2.000000 * L25);
   L46 = (L47 < 0.000000);
   L48 = (- L47);
   if (L46) {
      L45 = L48;
   } else {
      L45 = L47;
   }
   L44 = (- L45);
   L51 = (ctx._Cd + ctx._Cg);
   L49 = (0.005000 * L51);
   L43 = (L44 + L49);
   L41 = (2.000000 * L43);
   L24 = (L25 + L41);
   L22 = (0.500000 * L24);
   if (L4) {
      L3 = 100.000000;
   } else {
      L3 = L22;
   }
   controller_O_v_d(L3);
   L55 = (- 1.000000);
   L54 = (L55 * 100.000000);
   L59 = (- L25);
   L58 = (L59 + L41);
   L57 = (0.500000 * L58);
   if (L4) {
      L53 = L54;
   } else {
      L53 = L57;
   }
   controller_O_v_g(L53);
   L32 = (Te * L34);
   L31 = (L32 + L28);
   T30 = L31;
   T16 = L4;
   T11 = L5;
   ctx.M30 = T30;
   ctx.M30_nil = _false;
   ctx.M16 = T16;
   ctx.M16_nil = _false;
   ctx.M11 = T11;
   ctx.M11_nil = _false;
   ctx.M8 = ctx.M8 && !(_true);
}
