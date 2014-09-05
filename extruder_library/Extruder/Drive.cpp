#include "Drive.h"

#include "Arduino.h"

	//Constructors:

	//Empty constructor
	Drive::Drive(){
		//not implemented, use parametrized constructor
	}
	//Parametrized constructor
	Drive::Drive(char motor_pwm_pin, char motor_low_pin, char motor_sf_pin, char encoder_1_pin, char encoder_2_pin,  int encoder_steps_per_revolution){
		//Pins
		_motor_pwm_pin = motor_pwm_pin;
		_motor_low_pin = motor_low_pin;
		_motor_sf_pin = motor_sf_pin;
		_encoder_1_pin = encoder_1_pin;
		_encoder_2_pin = encoder_2_pin;

		//Initialize the duty cycle at 0 (motor stopped) to avoid cold extrusion
		_motor_duty_cycle = 0.0;

		_encoder = new Encoder(encoder_1_pin, encoder_2_pin);
		
		_encoder_steps_per_revolution = encoder_steps_per_revolution;

		_last_micros = 0 ;
	}


	//Destructor:

	Drive::~Drive(){
		delete _encoder;
	}

	//Methods:

	//Configuration. Code that has to be runned at setup()
	void Drive::setup(){
		pinMode(_motor_pwm_pin, OUTPUT); 	//IN2 pin, controls the red terminal of the motor (V+, PWM Speed control
		pinMode(_motor_low_pin, OUTPUT); 	//IN1 pin, controls the black terminal of the motor (GND)
		pinMode(_motor_sf_pin, INPUT); 		//SF flag
	}

	//Update drive output pins
	void Drive::update(){
		analogWrite(_motor_pwm_pin, _motor_duty_cycle*255.0);
		digitalWrite(_motor_low_pin, LOW);
	}

	//Checks if the motor is running (that is, _motor_duty_cycle > 0)
	bool Drive::is_ON(){
		if (_motor_duty_cycle > 0.0){
			return 1;
		}
		else {
			return 0;
		}
	}

	//Read the motor speed using the encoder
	double Drive::read_motor_speed(){

		double motor_speed, motor_position;
		
		//read the encoder position
		motor_position = _encoder->read();
		
		//calculate speed
		motor_speed = (motor_position/ _encoder_steps_per_revolution )/(micros()-_last_micros);
		  
		//convert from rev/us to rev/min
		motor_speed = motor_speed*600000;
		  
		//store the last_micros value and clear the encoder position
		_last_micros = micros();
		_encoder->write(0);
		  
		return motor_speed;
	}

	//Get the motor duty cycle
	double Drive::get_motor_duty_cycle(){
		return _motor_duty_cycle;
	}

	//Set the motor dudy cycle
	void Drive::set_motor_duty_cycle(double motor_duty_cycle){
		//Duty cycles above 1 or below 0 are not allowed
		if (motor_duty_cycle >= 1.0) {
			_motor_duty_cycle = 1.0;
		}
		else if (motor_duty_cycle <= 0){
			_motor_duty_cycle = 0;
		}
		//If the temperature is in the acceptable range
		else {
			_motor_duty_cycle = motor_duty_cycle;
		}	
	}