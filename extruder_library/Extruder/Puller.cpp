#include "Puller.h"

//Constructors:

//Empty constructor
Puller::Puller(){
	//not implemented, use the parametrized constructor
}
//Parametrized constructor
Puller::Puller(char puller_pin){
	//initialize attributes
	_puller_pin = puller_pin;
	_pulse_width = 1500; //1500 us is the rest position

	_servo = new Servo;
}


//Destructor:

Puller::~Puller(){
	delete _servo;
}

//Methods:

//Configuration. Code that has to be runned at setup()
void Puller::setup(){
	_servo->attach(_puller_pin);
}

//Update puller, write speed
void Puller::update(){
	_servo->writeMicroseconds( _pulse_width );
}

//Get the servo pulse width
int Puller::get_pulse_width(){
	return _pulse_width;
}

//Get the servo pulse width
void Puller::set_pulse_width(int pulse_width){
	_pulse_width = pulse_width;
}