#include "Heater.h"
	
	//Constructors:

	//Empty constructor
	Heater::Heater(){
		//not implemented, use the parametrized constructor
	}
	//Parametrized constructor
	Heater::Heater(char heater_pwm_pin, char thermistor_pin, const double * thermistor_lut, double temperature_setpoint, double max_temperature_setpoint, double min_temperature_setpoint, double k_p, double k_i, double k_d){
		_heater_pwm_pin = heater_pwm_pin;

		//Instantiate the Thermistor
		_thermistor = new Thermistor(thermistor_pin, thermistor_lut);

		//read the temperature for the first time and update the internal variable
		_temperature = _thermistor->read();

		//Set the initial setpoint, min and max values
		_temperature_setpoint = temperature_setpoint;
		_max_temperature_setpoint = max_temperature_setpoint;
		_min_temperature_setpoint = min_temperature_setpoint;

		//Set the initial duty cycle to an arbitrary value (will be updated by the PID later)
		_heater_duty_cycle = 0.5;


		//Instantiate the PID
		_heater_PID = new PID(&_temperature, &_heater_duty_cycle, &_temperature_setpoint, k_p, k_i, k_d, DIRECT);
		//Example: PID heaterPID(&temperature1, &heater_duty_cycle, &temperature1Setpoint,2.0,5.0,0.0, DIRECT);
	}

	//Destructor:

	Heater::~Heater(){
		delete _thermistor;
		delete _heater_PID;
	}

	//Methods:

	//Configuration. Code that has to be runned at setup()
	void Heater::setup(){
		//set the PWM pin to output
		pinMode(_heater_pwm_pin, OUTPUT);

		//Configure PID
		_heater_PID->SetOutputLimits(0.0, 1.0);
		_heater_PID->SetMode(AUTOMATIC);
	}

	//Update the PID and pin outputs
	void Heater::update(){

		//update the temperature
		_temperature = _thermistor->read();

		//update the PID
		_heater_PID->Compute();	//If more than 100ms (by default) have passed since the last update, 
								//it calculates new value for _heater_duty_cycle
								//(not every loop)
		
		//write the PWM value in the output pin
		analogWrite(_heater_pwm_pin, _heater_duty_cycle*255.0 );
	}

	//Set a temperature look up table
	double Heater::read_temperature(){
		return _temperature = _thermistor->read();
	}

	//Checks if the heater is powered (that is, _heater_duty_cycle > 0)
	bool Heater::is_ON(){
		if (_heater_duty_cycle > 0.0){
			return 1;
		}
		else {
			return 0;
		}
	}

	//Get the temperature setpoint
	double Heater::get_temperature_setpoint(){
		return _temperature_setpoint;
	}

	//Read the temperature value
	void Heater::set_temperature_setpoint(double temperature_setpoint){
		//Temperatures above max and below min are not allowed
		if (temperature_setpoint >= _max_temperature_setpoint) {
			_temperature_setpoint = _max_temperature_setpoint;
		}
		else if (temperature_setpoint <= _min_temperature_setpoint){
			_temperature_setpoint = _min_temperature_setpoint;
		}
		//If the temperature is in the acceptable range
		else {
			_temperature_setpoint = temperature_setpoint;
		}	
	}