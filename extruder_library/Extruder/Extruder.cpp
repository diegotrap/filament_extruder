#include "Extruder.h"

Extruder::Extruder(){
	
	int i = 0;
	for (i = 1; i <= NUMBER_OF_HEATERS; i++ ){ //start from 1 because _heater[0] should be empty
		_heater[i] = new Heater(HEATER_PWM_PIN[i], HEATER_THERMISTOR_PIN[i], thermistor_lut, HEATER_SETPOINT[i], HEATER_MAX_TEMPERATURE, HEATER_MIN_TEMPERATURE, HEATER_K_P[i], HEATER_K_I[i], HEATER_K_D[i] );
	}

	_drive = new Drive( MOTOR_PWM_PIN, MOTOR_LOW_PIN, MOTOR_ENCODER_1_PIN, MOTOR_ENCODER_2_PIN, MOTOR_ENCODER_STEPS_PER_REVOLUTION);
	//Drive(char motor_pwm_pin, char motor_low_pin, char encoder_1_pin, char encoder_2_pin,  int motor_encoder_steps_per_revolution);

	_puller = new Puller(PULLER_PIN);

	_fan_pin = FAN_PIN;
	_fan_state = 0;

	_cold_extrusion = 0;
}

Extruder::~Extruder(){
	int i = 0;
	for (i = 1; i <= NUMBER_OF_HEATERS; i++ ){ //start from 1 because _heater[0] should be empty
		delete _heater[i];
	}

	delete _drive;

	delete _puller;
}

void Extruder::setup(){
	
	int i = 0;
	for (i = 1; i <= NUMBER_OF_HEATERS; i++ ){ //start from 1 because _heater[0] should be empty
		_heater[i]->setup();
	}

	_drive->setup();

	_puller->setup();

	pinMode(_fan_pin, OUTPUT);
}

void Extruder::update_heaters(){
	int i = 0;
	for (i = 1; i <= NUMBER_OF_HEATERS; i++ ){ //start from 1 because _heater[0] should be empty
		_heater[i]->update();
	}
}

void Extruder::update_drive(){

	//to avoid cold extrusion, check if the melting heaters are above MELTING_TEMPERATURE
	for (int i = 1; i <= MELTING_HEATERS; i++){
		if (_heater[i]->read_temperature() < MELTING_TEMPERATURE){
			_cold_extrusion = 1;
		}
		else {
			_cold_extrusion = 0;
		}
	}
	//if there is cold extrusion, turn off the motor
	if (_cold_extrusion == 1) {
		_drive->set_motor_duty_cycle(0);
	}

	//update the drive (set the output pins to desired values)
	_drive->update();
}

void Extruder::update_puller(){
	_puller->update();
}

void Extruder::update_fan(){
		if (_fan_state == 0){
			digitalWrite(_fan_pin, LOW);
		}
		else{
			digitalWrite(_fan_pin, HIGH);
		}
}

double Extruder::read_heater_temperature(char heater_number){
	return _heater[heater_number]->read_temperature();
}

bool Extruder::is_heater_ON(char heater_number){
	return _heater[heater_number]->is_ON();
}

double Extruder::get_heater_temperature_setpoint(char heater_number){
	_heater[heater_number]->get_temperature_setpoint();
}

double Extruder::read_motor_speed(){
	return _drive->read_motor_speed();
}

void Extruder::set_heater_temperature_setpoint(char heater_number, double temperature_setpoint){
	_heater[heater_number]->set_temperature_setpoint(temperature_setpoint);
}

double Extruder::get_motor_duty_cycle(){
	return _drive->get_motor_duty_cycle();
}

void Extruder::set_motor_duty_cycle(double motor_duty_cycle){
	//motor can only be turned on if there is no cold extrusion
	if (_cold_extrusion == 0) {
		_drive->set_motor_duty_cycle(motor_duty_cycle);
	}
}

int Extruder::get_puller_pulse_width(){
	return _puller->get_pulse_width();
}

void Extruder::set_puller_pulse_width(int pulse_width){
	_puller->set_pulse_width(pulse_width);
}

bool Extruder::is_fan_ON(){
	return _fan_state;
}

void Extruder::set_fan_ON(){
	_fan_state = 1;
}

void Extruder::set_fan_OFF(){
	_fan_state = 0;
}
