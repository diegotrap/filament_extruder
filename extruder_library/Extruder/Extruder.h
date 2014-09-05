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
//#include "Arduino.h"
#include <PID_v1.h>
#include <Encoder.h>
//#include <avr/pgmspace.h> //to use PROGMEM

//Classes
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
		Heater * _heater[NUMBER_OF_HEATERS+1]; //Index correspond to heater number. _heater[0] is empty
		Drive * _drive;
		Puller * _puller;
		bool _cold_extrusion;
	public:
		Extruder();
		~Extruder();
		void setup();
		void update_heaters();
		void update_drive();
		void update_puller();
		double read_heater_temperature(char heater_number);
		bool is_heater_ON(char heater_number);
		double get_heater_temperature_setpoint(char heater_number);
		void set_heater_temperature_setpoint(char heater_number, double temperature_setpoint);
		double read_motor_speed();
		double get_motor_duty_cycle();
		void set_motor_duty_cycle(double motor_duty_cycle);
		int get_puller_pulse_width();
		void set_puller_pulse_width(int pulse_width);
};

#endif