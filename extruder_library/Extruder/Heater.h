/*
 *	Heater Class
 *
 * 	Models an extruder heater composed of a heating element, 
 * 	a thermistor and a PID to control the temperature.
 *
 */


#ifndef Heater_h_
#define Heater_h_

#include "PID_v1.h"
#include "Thermistor.h"

class Heater {
	
	private:
	
	//Attributes

	char _heater_pwm_pin;
	Thermistor * _thermistor;
	//The next three variables are used by the PID and have to be double to be type compatible with the PID library.
	//In Arduino, double has the same byte size as float, so it does't imply increased memory usage.
	double _heater_duty_cycle;
	double _temperature;
	double _temperature_setpoint;
	double _max_temperature_setpoint;
	double _min_temperature_setpoint;
	PID * _heater_PID;

	public:

	//Constructors:

	//Empty constructor
	Heater();
	//Parametrized constructor
	Heater(char heater_pwm_pin, char thermistor_pin, const double * thermistor_lut, double temperature_setpoint, double max_temperature_setpoint, double min_temperature_setpoint, double k_p, double k_i, double k_d);

	//Destructor:

	~Heater();

	//Methods:

	//Configuration. Code that has to be runned at setup()
	void setup();

	//Update PID and pin output
	void update();

	//Read the thermistor temperature
	double read_temperature();

	//Checks if the heater is powered (that is, _heater_duty_cycle > 0)
	bool is_ON();

	//Get the temperature setpoint
	double get_temperature_setpoint();

	//Set the temperature setpoint
	void set_temperature_setpoint(double temperature_setpoint);
};

#endif