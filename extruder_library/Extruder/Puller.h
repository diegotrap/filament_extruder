/*
 *	Puller Class
 *
 * 	Models an extruder puller composed operated by a continuous 
 * 	rotation servo with adjustable speed.
 *
 */


#ifndef Puller_h_
#define Puller_h_

#include "Servo.h"

class Puller {
	
	private:
	
	//Attributes

	char _puller_pin;
	int _pulse_width; //width of the pulse that the servo receives (in microseconds)
	Servo * _servo;

	public:
	//Constructors:

	//Empty constructor
	Puller();
	//Parametrized constructor
	Puller(char puller_pin);


	//Destructor:

	~Puller();

	//Methods:

	//Configuration. Code that has to be runned at setup()
	void setup();

	//Update puller, write speed
	void update();

	//Get the servo pulse width
	int get_pulse_width();

	//Get the servo pulse width
	void set_pulse_width(int pulse_width);
};

#endif