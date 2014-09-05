/*
 *	Thermistor Class
 *
 * 	Models a thermistor that reads temperature from an
 * 	ADC pin using a look up table.
 *
 */


#ifndef Thermistor_h_
#define Thermistor_h_

#include <Arduino.h>

class Thermistor {
	private:
	
	//Attributes

	char _thermistor_pin; 		//Pin the thermistor is connected to
	const double * _thermistor_lut; 	//Temperature Look Up Table where each ADC level is given a corresponding temperature

	public:
	
	//Constructors:

	//Empty constructor
	Thermistor();
	//Parametrized constructor
	Thermistor(char thermistor_pin, const double * thermistor_lut);

	//Destructor:

	~Thermistor();

	//Methods:

	//Set a temperature look up table
	void set_pin(char thermistor_pin);

	//Set a temperature look up table
	void set_lut(const double * thermistor_lut);

	//Read the temperature value
	double read();
};

#endif