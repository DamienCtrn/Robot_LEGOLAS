/********
* ec2c version 0.67
* context   method = STATIC
* ext call  method = PROCEDURES
* c header file generated for node : controller 
* to be used with : controller.c 
********/
#ifndef _controller_EC2C_H_FILE
#define _controller_EC2C_H_FILE
/* This program needs external declarations */
#include "controller_ext.h"
/*-------- Predefined types ---------*/
#ifndef _EC2C_PREDEF_TYPES
#define _EC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1
#endif
/*--------- Pragmas ----------------*/
//MODULE: controller 4 2
//IN: _real Cg
//IN: _real Cd
//IN: _integer Jean_Michel
//IN: _boolean Jean_Ren__
//OUT: _real v_d
//OUT: _real v_g
#ifndef _controller_EC2C_SRC_FILE
/*-------- Input procedures -------------*/
extern void controller_I_Cg(_real);
extern void controller_I_Cd(_real);
extern void controller_I_Jean_Michel(_integer);
extern void controller_I_Jean_Ren__(_boolean);
/*-------- Reset procedure -----------*/
extern void controller_reset();
/*--------Context init = context reset --------*/
#define controller_init controller_reset
/*-------- Step procedure -----------*/
extern void controller_step();
#endif
#endif
