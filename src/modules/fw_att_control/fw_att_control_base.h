/*
 * fw_att_control_base.h
 *
 *  Created on: Sep 24, 2014
 *      Author: roman
 */

#ifndef FW_ATT_CONTROL_BASE_H_
#define FW_ATT_CONTROL_BASE_H_

#include <ecl/attitude_fw/ecl_pitch_controller.h>
#include <ecl/attitude_fw/ecl_roll_controller.h>
#include <ecl/attitude_fw/ecl_yaw_controller.h>

#include <uORB/topics/airspeed.h>
#include <uORB/topics/vehicle_attitude_setpoint.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/actuator_controls.h>
#include <uORB/topics/vehicle_rates_setpoint.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_control_mode.h>
#include <uORB/topics/parameter_update.h>
#include <uORB/topics/vehicle_global_position.h>
#include <uORB/topics/vehicle_status.h>
#include <drivers/drv_accel.h>

#include <systemlib/perf_counter.h>

class FixedwingAttitudeControlBase
{
public:
	/**
	 * Constructor
	 */
	FixedwingAttitudeControlBase();

	/**
	 * Destructor, also kills the sensors task.
	 */
	~FixedwingAttitudeControlBase();


protected:

	bool		_task_should_exit;		/**< if true, sensor task should exit */
	bool		_task_running;			/**< if true, task is running in its mainloop */
	int		_control_task;			/**< task handle for sensor task */



	struct vehicle_attitude_s			_att;			/**< vehicle attitude */
	struct accel_report				_accel;			/**< body frame accelerations */
	struct vehicle_attitude_setpoint_s		_att_sp;		/**< vehicle attitude setpoint */
	struct manual_control_setpoint_s		_manual;		/**< r/c channel data */
	struct airspeed_s				_airspeed;		/**< airspeed */
	struct vehicle_control_mode_s			_vcontrol_mode;		/**< vehicle control mode */
	struct actuator_controls_s			_actuators;		/**< actuator control inputs */
	struct actuator_controls_s			_actuators_airframe;	/**< actuator control inputs */
	struct vehicle_global_position_s		_global_pos;		/**< global position */
	struct vehicle_status_s				_vehicle_status;	/**< vehicle status */

	perf_counter_t	_loop_perf;			/**< loop performance counter */
	perf_counter_t	_nonfinite_input_perf;		/**< performance counter for non finite input */
	perf_counter_t	_nonfinite_output_perf;		/**< performance counter for non finite output */

	bool		_setpoint_valid;		/**< flag if the position control setpoint is valid */
	bool		_debug;				/**< if set to true, print debug output */

	struct {
		float tconst;
		float p_p;
		float p_d;
		float p_i;
		float p_ff;
		float p_rmax_pos;
		float p_rmax_neg;
		float p_integrator_max;
		float p_roll_feedforward;
		float r_p;
		float r_d;
		float r_i;
		float r_ff;
		float r_integrator_max;
		float r_rmax;
		float y_p;
		float y_i;
		float y_d;
		float y_ff;
		float y_roll_feedforward;
		float y_integrator_max;
		float y_coordinated_min_speed;
		float y_rmax;

		float airspeed_min;
		float airspeed_trim;
		float airspeed_max;

		float trim_roll;
		float trim_pitch;
		float trim_yaw;
		float rollsp_offset_deg;			/**< Roll Setpoint Offset in deg */
		float pitchsp_offset_deg;			/**< Pitch Setpoint Offset in deg */
		float rollsp_offset_rad;			/**< Roll Setpoint Offset in rad */
		float pitchsp_offset_rad;			/**< Pitch Setpoint Offset in rad */
		float man_roll_max;						/**< Max Roll in rad */
		float man_pitch_max;					/**< Max Pitch in rad */

	}		_parameters;			/**< local copies of interesting parameters */




	ECL_RollController				_roll_ctrl;
	ECL_PitchController				_pitch_ctrl;
	ECL_YawController				_yaw_ctrl;

	void control_attitude();




};



#endif /* FW_ATT_CONTROL_BASE_H_ */