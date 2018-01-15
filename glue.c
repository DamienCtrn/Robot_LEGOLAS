#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#include "periods.h"

// GLUE CODE: include the Lustre generated header
#include "line_ctrl.h"
#include "obst_ctrl.h"

// Calibration parameters
#define MIN_LIGHT_SENSOR 0
#define MAX_LIGHT_SENSOR 1023

#define V_MAX 1

// #define DEBUG

_boolean obst = false;
// DeclareResource(obst);

/*-----------------------------
   OSEK declarations
-------------------------------
DON'T MODIFY
------------------------------*/
DeclareCounter(SysTimerCnt);
DeclareResource(lcd);
DeclareTask(LowTask);
DeclareTask(HighTask);

/*------------------------------
 Function to be invoked from a category 2 interrupt
--------------------------------
DON'T MODIFY
------------------------------*/
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	/*
	 *  Increment OSEK Alarm System Timer Count
     */
	ercd = SignalCounter( SysTimerCnt );
	if( ercd != E_OK ){
		ShutdownOS( ercd );
	}
}

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



/* GLUE CODE
	Since a SINGLE instance of teh Lustre gen. code is used,
	we can compile it using "-ctx-static" (cf. Makefile)
   making the interface simpler:
		- In particular, we don't have to "alocate" the node context:
   	the global, unique instance is declared in the generated.
		- all the "methods" (init, step input, output) have NO parameters
*/


_boolean calibration_init = _true;
int right_min = MAX_LIGHT_SENSOR,
 	right_max = MIN_LIGHT_SENSOR,
	left_min = MAX_LIGHT_SENSOR,
	left_max = MIN_LIGHT_SENSOR;
/**
 * Fonction de calibrage automatique
 * Appuyer sur le bouton orange pour finaliser la calibration
 */
void calibration_auto_step(void) {
	int right, left;

	left = ecrobot_get_light_sensor(NXT_PORT_S1);
	right = ecrobot_get_light_sensor(NXT_PORT_S2);
	if (left > left_max)
		left_max = left;
	if (left < left_min)
		left_min = left;
	if (right > right_max)
		right_max = right;
	if (right < right_min)
		right_min = right;

	GetResource(lcd);
	display_goto_xy(0,0);
	display_int(left_min, 4);
	display_string(" left min");

	display_goto_xy(0,1);
	display_int(left_max, 4);
	display_string(" left max");

	display_goto_xy(0,2);
	display_int(right_min, 4);
	display_string(" right min");

	display_goto_xy(0,3);
	display_int(right_max, 4);
	display_string(" right max");

	display_goto_xy(0,4);
	display_int(ecrobot_get_sonar_sensor(NXT_PORT_S3), 4);
	display_string(" distance");

	display_update();
	ReleaseResource(lcd);
}

/* GLUE CODE
	IMPORTANT !!!
	All used Lustre nodes MUST be initialized HERE
	using the procedure provided in the generated code
*/
void usr_init(void) {
	line_ctrl_init();
	obst_ctrl_init();
	while (calibration_init) {
		calibration_auto_step();
		if (ecrobot_is_ENTER_button_pressed()) {
			calibration_init = _false;
		}
	}
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
void line_ctrl_O_Vd(_real V) {
	int v_power = speed_to_power(V);
#ifdef DEBUG
	display_goto_xy(0,3);
	display_int(v_power, 4);
	display_string(" Sp R ");
#endif
	nxt_motor_set_speed(NXT_PORT_A, v_power, 1);
}

void line_ctrl_O_Vg(_real V) {
	int v_power = speed_to_power(V);
#ifdef DEBUG
	display_goto_xy(0,4);
	display_int(v_power, 4);
	display_string(" Sp L ");
#endif
	nxt_motor_set_speed(NXT_PORT_B, v_power, 1);
}

void obst_ctrl_O_Obst(_boolean output) {
	// GetResource(obst);
	obst = output;
	// ReleaseResource(obst);
}

/*
	GLUE CODE
	The "core" of a step:
   - read inputs from sensors and copy them to Lustre code
     using the corresponding input procedures
	- calls the step proc.
*/
TASK(LowTask) {
	/* read and set inputs */
	line_ctrl_I_Cg(raw_to_model(left_min, left_max, ecrobot_get_light_sensor(NXT_PORT_S1)));
	line_ctrl_I_Cd(raw_to_model(right_min, right_max, ecrobot_get_light_sensor(NXT_PORT_S2)));
	// GetResource(obst);
	line_ctrl_I_Obst(obst);
	// ReleaseResource(obst);

	line_ctrl_step();

#ifdef DEBUG
	GetResource(lcd);
	display_goto_xy(0,0);
	display_int(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S1)), 4);
	// display_int(ecrobot_get_light_sensor(NXT_PORT_S1), 4);	// Pour Calibration
	display_string(" left ");
	display_goto_xy(0,1);
	display_int(raw_to_model(MIN, MAX, ecrobot_get_light_sensor(NXT_PORT_S2)), 4);
	// display_int(ecrobot_get_light_sensor(NXT_PORT_S2), 4);	// Pour Calibration
	display_string(" right");
	/* refresh screen (ecrobot library)
	 */
	display_update();
	ReleaseResource(lcd);
#endif

	TerminateTask();
}

TASK(HighTask) {

	/* read and set inputs */
	obst_ctrl_I_Jean_Michel(ecrobot_get_sonar_sensor(NXT_PORT_S3));
	obst_ctrl_I_Cd(raw_to_model(right_min, right_max, ecrobot_get_light_sensor(NXT_PORT_S2)));

#ifdef DEBUG
	GetResource(lcd);
	display_goto_xy(0,2);
	display_int(ecrobot_get_sonar_sensor(NXT_PORT_S3), 4);
	display_string(" dist ");
	ReleaseResource(lcd);
#endif

	obst_ctrl_step();

	TerminateTask();
}
