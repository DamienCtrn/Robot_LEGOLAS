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
   _boolean _Jean_Reset;
   //OUTPUTS
   _real _v_d;
   _real _v_g;
   //REGISTERS
   _real M42;
   _boolean M42_nil;
   _boolean M17;
   _boolean M17_nil;
   _boolean M27;
   _boolean M27_nil;
   _boolean M22;
   _boolean M22_nil;
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
void controller_I_Jean_Reset(_boolean V){
   ctx._Jean_Reset = V;
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
   ctx.M42_nil = _true;
   ctx.M17_nil = _true;
   ctx.M27_nil = _true;
   ctx.M22_nil = _true;
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
   _boolean L16;
   _boolean L15;
   _boolean L14;
   _boolean L5;
   _real L40;
   _real L38;
   _real L47;
   _real L50;
   _real L46;
   _real L51;
   _real L37;
   _real L59;
   _boolean L58;
   _real L60;
   _real L57;
   _real L56;
   _real L63;
   _real L61;
   _real L55;
   _real L53;
   _real L36;
   _real L34;
   _real L4;
   _real L67;
   _real L66;
   _real L71;
   _real L70;
   _real L69;
   _real L65;
   _real L44;
   _real L43;
   _real T42;
   _boolean L21;
   _boolean L26;
   _boolean L29;
   _boolean L28;
   _boolean L25;
   _boolean L24;
   _boolean L31;
   _boolean L23;
   _boolean L20;
   _boolean L19;
   _boolean L18;
   _boolean T17;
   _boolean T27;
   _boolean T22;
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
      L16 = _false;
   } else {
      L16 = ctx.M17;
   }
   L15 = (L16 || ctx._Jean_Reset);
   L14 = (! L15);
   L5 = (L6 && L14);
   if (ctx.M8) {
      L40 = 0.000000;
   } else {
      L40 = ctx.M42;
   }
   L38 = (ki_teta * L40);
   L47 = (pi / 200.000000);
   L50 = (ctx._Cd - ctx._Cg);
   L46 = (L47 * L50);
   L51 = (kp_teta * L46);
   L37 = (L38 + L51);
   L59 = (2.000000 * L37);
   L58 = (L59 < 0.000000);
   L60 = (- L59);
   if (L58) {
      L57 = L60;
   } else {
      L57 = L59;
   }
   L56 = (- L57);
   L63 = (ctx._Cd + ctx._Cg);
   L61 = (0.005000 * L63);
   L55 = (L56 + L61);
   L53 = (2.000000 * L55);
   L36 = (L37 + L53);
   L34 = (0.500000 * L36);
   if (L5) {
      L4 = 0.200000;
   } else {
      L4 = L34;
   }
   controller_O_v_d(L4);
   L67 = (- 1.000000);
   L66 = (L67 * 0.200000);
   L71 = (- L37);
   L70 = (L71 + L53);
   L69 = (0.500000 * L70);
   if (L5) {
      L65 = L66;
   } else {
      L65 = L69;
   }
   controller_O_v_g(L65);
   L44 = (Te * L46);
   L43 = (L44 + L40);
   T42 = L43;
   if (ctx.M8) {
      L21 = _false;
   } else {
      L21 = ctx.M22;
   }
   if (ctx.M8) {
      L26 = _false;
   } else {
      L26 = ctx.M27;
   }
   L29 = (ctx._Cd <= 30.000000);
   L28 = (L5 && L29);
   L25 = (L26 || L28);
   L24 = (L25 && L14);
   L31 = (ctx._Cd >= 70.000000);
   L23 = (L24 && L31);
   L20 = (L21 || L23);
   L19 = (L20 && L14);
   L18 = (L19 && L29);
   T17 = L18;
   T27 = L24;
   T22 = L19;
   T11 = L5;
   ctx.M42 = T42;
   ctx.M42_nil = _false;
   ctx.M17 = T17;
   ctx.M17_nil = _false;
   ctx.M27 = T27;
   ctx.M27_nil = _false;
   ctx.M22 = T22;
   ctx.M22_nil = _false;
   ctx.M11 = T11;
   ctx.M11_nil = _false;
   ctx.M8 = ctx.M8 && !(_true);
}
