/*
 *	Drive Class
 *
 * 	Models an extruder drive composed of a motor (plus motor driver), 
 * 	and a encoder to read the motor speed.
 *
 */


#ifndef Drive_h_
#define Drive_h_

#include "Encoder.h"

class Drive {
	
	private:
	
	//Attributes

	char _motor_pwm_pin;
	char _motor_low_pin;
	char _encoder_1_pin;
	char _encoder_2_pin;


	double _motor_duty_cycle;
	Encoder * _encoder;
	int _encoder_steps_per_revolution;
	unsigned long _last_micros; //used to calculate motor speed

	public:
	//Constructors:

	//Empty constructor
	Drive();
	//Parametrized constructor
	Drive(char motor_pwm_pin, char motor_low_pin, char encoder_1_pin, char encoder_2_pin, int motor_encoder_steps_per_revolution);


	//Destructor:

	~Drive();

	//Methods:

	//Configuration. Code that has to be runned at setup()
	void setup();

	//Update drive output pins
	void update();

	//Checks if the motor is running (that is, _motor_duty_cycle > 0)
	bool is_ON();

	//Read the motor speed using the encoder
	double read_motor_speed();

	//Get the motor duty cycle
	double get_motor_duty_cycle();

	//Set the motor dudy cycle
	void set_motor_duty_cycle(double motor_duty_cycle);
};

#endif