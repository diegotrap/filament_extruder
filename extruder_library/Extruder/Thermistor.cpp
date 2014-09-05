#include "Thermistor.h"




//Empty constructor
Thermistor::Thermistor(){
	_thermistor_pin = 0;
	_thermistor_lut = 0;
}

//Parametrized constructor
Thermistor::Thermistor(char thermistor_pin, const double * thermistor_lut){
	_thermistor_pin = thermistor_pin;
	_thermistor_lut = thermistor_lut;
}

//Destructor
Thermistor::~Thermistor(){

}

//Methods:

//Set a temperature look up table
void Thermistor::set_pin(char thermistor_pin){
	_thermistor_pin = thermistor_pin;
}
//Set a temperature look up table
void Thermistor::set_lut(const double * thermistor_lut){
	_thermistor_lut = thermistor_lut;
}
//Read the temperature value
double Thermistor::read(){
	//read the termistor pin
	int ADC_value = analogRead( _thermistor_pin );

	//get the temperature accessing to the correspondent position of the LUT

	double temperature = _thermistor_lut[ADC_value];

	return temperature;
}
