#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "periods.h"

// GLUE CODE: include the Lustre generated header
#include "controller.h"

// Calibration parameters
#define MIN 490
#define MAX 650
#define V_MAX 1

// #define DEBUG

/* OSEK specific code, DO NOT CHANGE */
DeclareCounter(SysTimerCnt);
DeclareTask(Task1);
void user_1ms_isr_type2(void) {
  StatusType ercd;
  ercd = SignalCounter(SysTimerCnt);
  /* Increment OSEK Alarm Counter */
  if(ercd != E_OK) { ShutdownOS(ercd); }
}
/* END OF OSEK specific code */

/* Init and terminate OSEK */
void ecrobot_device_initialize() {
	/* GLUE CODE:
		light sensor are ACTIVE devices and must be initialized
		(conversely to buttons, for instance)
	*/
	ecrobot_set_light_sensor_active(NXT_PORT_S1);
	ecrobot_set_light_sensor_active(NXT_PORT_S2);
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
}

void ecrobot_device_terminate() {
   /* GLUE CODE:
		light sensor must be switched off
   */
	ecrobot_set_light_sensor_inactive(NXT_PORT_S1);
	ecrobot_set_light_sensor_inactive(NXT_PORT_S2);
	ecrobot_term_sonar_sensor(NXT_PORT_S3);
}


/* UsrTask */

/* GLUE CODE
	Since a SINGLE instance of teh Lustre gen. code is used,
	we can compile it using "-ctx-static" (cf. Makefile)
   making the interface simpler:
		- In particular, we don't have to "alocate" the node context:
   	the global, unique instance is declared in the generated.
		- all the "methods" (init, step input, output) have NO parameters
*/


/* GLUE CODE
	IMPORTANT !!!
	All used Lustre nodes MUST be initialized HERE
	using the procedure provided in the generated code
*/
void usr_init(void) {
	// Calibration à faire (mutex en multi taches)
	controller_init();
}

/**
 * CALIBRATION
 */
_real raw_to_model(int min, int max, int raw) {
	if (raw < min)
		return 100.0;
	else if (raw > max)
		return 0.0;
	else
		return (_real)(100.0*((_real)max - (_real)raw)/((_real)max - (_real)min));
}

int speed_to_power(_real speed) {
	if (speed > V_MAX)
		speed = V_MAX;
	else if (speed < -V_MAX)
		speed = -V_MAX;
	return (int)((speed * 100.0) / V_MAX);
}

/* GLUE CODE
	Output procedures
	Note: we directly use here the functions from
	the "ecrobot" library (display_goto_xy, display_string etc)
*/
void controller_O_v_d(_real V) {
	int v_power = speed_to_power(V);
#ifdef DEBUG
	display_goto_xy(0,3);
	display_int(v_power, 4);
	display_string(" Sp R ");
#endif
	nxt_motor_set_speed(NXT_PORT_A, v_power, 0);
}

void controller_O_v_g(_real V) {
	int v_power = speed_to_power(V);
#ifdef DEBUG
	display_goto_xy(0,4);
	display_int(v_power, 4);
	display_string(" Sp L ");
#endif
	nxt_motor_set_speed(NXT_PORT_B, v_power, 0);
}

/*
	GLUE CODE
	The "core" of a step:
   - read inputs from sensors and copy them to Lustre code
     using the corresponding input procedures
	- calls the step proc.
*/
TASK(UsrTask)
{

	/* read and set inputs */
	controller_I_Cg(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S1)));
	controller_I_Cd(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S2)));
	controller_I_Jean_Michel(ecrobot_get_sonar_sensor(NXT_PORT_S3));

	/* performs a Lustre step
		output procs are called within the step
	*/
	controller_step();
#ifdef DEBUG
	display_goto_xy(0,0);
	display_int(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S1)), 4);
	// display_int(ecrobot_get_light_sensor(NXT_PORT_S1), 4);	// Pour Calibration
	display_string(" left ");
	display_goto_xy(0,1);
	display_int(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S2)), 4);
	// display_int(ecrobot_get_light_sensor(NXT_PORT_S2), 4);	// Pour Calibration
	display_string(" right");
	display_goto_xy(0,2);
	display_int(ecrobot_get_sonar_sensor(NXT_PORT_S3), 4);
	display_string(" dist ");
	/* refresh screen (ecrobot library)
	 */
	display_update();
#endif

	TerminateTask();
}
