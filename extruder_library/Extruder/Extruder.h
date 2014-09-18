/*
 *	Extruder Library
 *
 * 	This library contains the abstraction of a filament extruder.
 *	It's designed to be included in any Arduino Sketch to let the user 
 *	access to the functionality of the machine in an object-oriented way.
 *
 *	Author: Diego Trapero
 *
 *	More info at https://github.com/diegotrap/filament_extruder
 *
 */


#ifndef Extruder_h_
#define Extruder_h_

//Libraries
#include <PID_v1.h>
#include <Encoder.h>

//Custom classes
#include "Thermistor.h"
#include "Heater.h"
#include "Drive.h"
#include "Puller.h"

//Extruder configuration file
#include "Configuration.h"


/***************************
 *	Extruder class
****************************/

class Extruder
{
	private:

		//Attributes

		Heater * _heater[NUMBER_OF_HEATERS+1]; //Index correspond to heater number. _heater[0] is empty
		Drive * _drive;
		Puller * _puller;
		bool _fan_state;
		char _fan_pin;
		bool _cold_extrusion;

	public:

		//Constructor:
		Extruder();

		//Destructor:
		~Extruder();


		//Methods:


		// Setup and update methods:
		//--------------------------

		//Initial setup: pin modes, configuration, etc.
		void setup();

		//Update the heaters' pins, temperatures, etc.
		void update_heaters();

		//Update the drive, check cold extrusion, etc.
		void update_drive();

		//Update the puller pin
		void update_puller();

		//Update the fan pins
		void update_fan();


		// Heater methods:
		//------------------

		//Read the heater temperature using the thermistor
		double read_heater_temperature(char heater_number);

		//Returns 1 if the chose extruder is powered
		bool is_heater_ON(char heater_number);

		//Get one of the heater's setpoint
		double get_heater_temperature_setpoint(char heater_number);

		//Set one of the heater's setpoint
		void set_heater_temperature_setpoint(char heater_number, double temperature_setpoint);


		// Drive methods:
		//---------------

		//Returns the motor speed as read by the encoder
		double read_motor_speed();

		//Set the motor duty cycle (if there isn't cold extrusion)
		double get_motor_duty_cycle();

		//Set the motor duty cycle
		void set_motor_duty_cycle(double motor_duty_cycle);


		// Puller methods:
		//------------------

		//Get the puller pulse width
		int get_puller_pulse_width();

		//Set the puller pulse width
		void set_puller_pulse_width(int pulse_width);


		// Fan methods:
		//------------------

		//Returns 1 if the fan is working
		bool is_fan_ON();

		//Turn the fan on
		void set_fan_ON();

		//Turn the fan off
		void set_fan_OFF();
};

#endif