/*
LCD and Encoder test code

Coding convention:

	* Variables in lowercase and underscore
	* Constants in uppercase
	* Classes starting with uppercase
	* Objects in lowercase
	* Methods and attributes in lowercase and underscore

Structure:

	* Libraries
	* Configuration
	* Constants
	* Global variables
	* setup()
	* loop()

*/

/***************
	Libraries
****************/
#include <LiquidCrystal.h>
#include <Encoder.h>

//The next is a fix for the R_AVR_13_PCREL, "relocation truncated to fit" error.
//Found in here: http://forum.arduino.cc/index.php/topic,127861.0.html
//Deeper explanation here: http://stackoverflow.com/questions/8188849/avr-linker-error-relocation-truncated-to-fit
//#include <avr/pgmspace.h>
//const char pad[100] PROGMEM = { 0 };

/***************
	Configuration
****************/


/***************
	Constants
****************/

//Pin Constants

//LCD Pins
#define LCD_RS_PIN 48 
#define LCD_EN_PIN 49
#define LCD_D4_PIN 47
#define LCD_D5_PIN 46
#define LCD_D6_PIN 45
#define LCD_D7_PIN 44

//Screen Encoder Pins
#define S_ENC_1_PIN 2     //Encoder signal 1
#define S_ENC_2_PIN 3     //Encoder signal 2
#define S_ENC_BTN_PIN 41  //Encoder button


//Screen Constants
#define SCREEN_REFRESH_PERIOD 200	//in milliseconds. Values below 100 seems to loose encoder steps. Large values cause lag in response.
#define ENCODER_STEPS_PER_UNIT 2 	//How many steps of the encoder position are necessary to change one menu item or one variable unit
#define CURSOR_SELECT_CHARACTER 62 	//ACII code for the cursor selection character (by default 62, '>')
#define CURSOR_EDIT_CHARACTER 35

//Menu positions
#define NUMBER_OF_MENU_POSITIONS 6

#define MOTOR_MENU 0
#define HEATER_1_MENU 1
#define HEATER_2_MENU 2
#define HEATER_3_MENU 3
#define FAN_MENU 4
#define PULLER_MENU 5
//falta el winder



/***************
	Global variables
****************/

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
Encoder screen_encoder(S_ENC_1_PIN, S_ENC_2_PIN);


// LCD custom chars
// Custom characters generated thanks to lcdchargen tool by Omer Kilic
// URL: http://omerk.github.io/lcdchargen/

byte motor_char[8] = {
	0b00100,
	0b00100,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110
};

byte thermometer_char[8] = {
	0b00100,
	0b01010,
	0b01010,
	0b01010,
	0b01010,
	0b10001,
	0b10001,
	0b01110
};

byte fan_char[8] = {
	0b00000,
	0b11001,
	0b01011,
	0b00100,
	0b11010,
	0b10011,
	0b00000,
	0b00000
};

byte puller_char[8] = {
	0b00000,
	0b00100,
	0b01111,
	0b11111,
	0b01111,
	0b00100,
	0b00000,
	0b00000
};

//Screen encoder global variables
//we choose int because when the encoder lecture overflows the increment is calculated with an error, so we want it to happen as rarely as possible
int old_screen_encoder_position = 0;
int new_screen_encoder_position;
int delta_encoder_position;
char cursor_position = 0;
char delta_cursor;
char delta_variable;


//Extruder state global variables
//declared as double to make them compatible with the PID library

double motor_speed = 18;
double heater_1_temperature = 126;
double heater_2_temperature = 179;
double heater_3_temperature = 231;
double puller_speed = 4;
bool fan_on = 1;

//motor duty cycle
double motor_duty_cycle = 50;


//setpoints
double heater_1_setpoint = 125;
double heater_2_setpoint = 180;
double heater_3_setpoint = 225;

//heater duty cycles
double heater_1_duty_cycle = 0;
double heater_2_duty_cycle = 0;
double heater_3_duty_cycle = 0;

/***************
	setup()
****************/

void setup() {
	
	//Part of the fix for theR_AVR_13_PCREL relocation truncated to fit error
	//pad[0];
	
	//Pin setup
	
	//LCD Pins
	pinMode(LCD_RS_PIN, OUTPUT);
	pinMode(LCD_EN_PIN, OUTPUT);
	pinMode(LCD_D4_PIN, OUTPUT);
	pinMode(LCD_D5_PIN, OUTPUT);
	pinMode(LCD_D6_PIN, OUTPUT);
	pinMode(LCD_D7_PIN, OUTPUT);
	
	
	//Screen Encoder Pins
	//S_ENC_1_PIN and S_ENC_2_PIN must not be initialized for the encoder to work correctly
	pinMode(S_ENC_BTN_PIN, INPUT_PULLUP); //must be connected to an internal pullup resistor
	
	// set up the LCD's number of columns and rows: 
	lcd.begin(20, 4);
	
	// setup of the custom characters
	lcd.createChar(0, motor_char);
	lcd.createChar(1, thermometer_char);
	lcd.createChar(2, fan_char);
	lcd.createChar(3, puller_char);

}


/***************
	loop()
****************/

void loop() {

	static unsigned long last_screen_update; //type is return type of the millis() function
	static bool is_clicked, is_editing;


	if (millis() - last_screen_update >= SCREEN_REFRESH_PERIOD) {

		last_screen_update = millis();

		//update the button state
		if ( digitalRead(S_ENC_BTN_PIN) == HIGH ){
			is_clicked = 0;  //button is pulled up and gives a HIGH when its not pushed
		} else {
			is_clicked = 1;
		}

		//update the menu mode (selecting or editing)
		if ( is_editing == 0 && is_clicked == 1){ //if we are in selecting mode and the button is pushed, enter editing mode
		    is_editing = 1;
		} else if (is_editing == 1 && is_clicked == 1){ //if we are in editing mode and the button is pushed, leave editing mode
			is_editing = 0;
		}

		//Represent the custom characters in the screen
		lcd.setCursor(1, 0);
		lcd.write((uint8_t)0); //motor_char
	 
		lcd.setCursor(1, 1);
		lcd.write((uint8_t)1); //thermometer_char
		
		lcd.setCursor(1, 2);
		lcd.write((uint8_t)1); //thermometer_char
		
		lcd.setCursor(1, 3);
		lcd.write((uint8_t)1); //thermometer_char
		
		lcd.setCursor(10, 0);
		lcd.write((uint8_t)2); //fan_char
		
		lcd.setCursor(10, 1);
		lcd.write((uint8_t)3); //puller_char

		//Motor
		
		lcd.setCursor(2, 0);
		lcd.print( dto3char(motor_speed) );
		
		lcd.setCursor(5, 0);
		lcd.print('/');
		
		lcd.setCursor(6, 0);
		lcd.print( dto3char(motor_duty_cycle) );
		
		//Heater 1
		lcd.setCursor(2, 1);
		lcd.print( dto3char(heater_1_temperature) );
		
		lcd.setCursor(5, 1);
		lcd.print('/');
		
		lcd.setCursor(6, 1);
		lcd.print( dto3char(heater_1_setpoint) );
		
		//Heater 2
		lcd.setCursor(2, 2);
		lcd.print( dto3char(heater_2_temperature) );
		
		lcd.setCursor(5, 2);
		lcd.print('/');
		
		lcd.setCursor(6, 2);
		lcd.print( dto3char(heater_2_setpoint) );
		
		//Heater 3
		lcd.setCursor(2, 3);
		lcd.print( dto3char(heater_3_temperature) );
		
		lcd.setCursor(5, 3);
		lcd.print('/');
		
		lcd.setCursor(6, 3);
		lcd.print( dto3char(heater_3_setpoint) );
		
		//Fan
		lcd.setCursor(11, 0);
		lcd.print(fan_on);
		
		//Puller
		lcd.setCursor(11, 1);
		lcd.print( dto3char(puller_speed) );


		//read the screen encoder position
		new_screen_encoder_position = screen_encoder.read();
		
		//calculate the increment (delta) in encoder position since last execution
		delta_encoder_position = new_screen_encoder_position - old_screen_encoder_position;
		
		//once we have finished calculating, store the last value of the screen encoder
		old_screen_encoder_position = new_screen_encoder_position;
		
		//if the screen encoder position is "about" to overflow the int range, return it to zero
		if ( (screen_encoder.read() >= 32000) || (screen_encoder.read() < -32000) ) {
			screen_encoder.write(0);
		}

		// if we are in selecting mode, update the cursor
		if (is_editing == 0) {
		
			//Calculate the increment (delta) in the position of the cursor
			delta_cursor = delta_encoder_position / ENCODER_STEPS_PER_UNIT;

			//Clear the cursor character in the old position before the cursor is updated
			if (cursor_position <= 3){
				lcd.setCursor(0, cursor_position);
			}
			//if the menu item is in the right column
			else {
				lcd.setCursor(9, cursor_position - 4);
			}
			lcd.write(' ');

			//Calculate the new cursor position
			//If the cursor position has gone out of the range determined by NUMBER_OF_MENU_POSITIONS, return it back
			cursor_position = cursor_position + delta_cursor;
			
			while(cursor_position >= NUMBER_OF_MENU_POSITIONS ){
				cursor_position = cursor_position - NUMBER_OF_MENU_POSITIONS;
			}
			
			while(cursor_position < 0){
				cursor_position = cursor_position + NUMBER_OF_MENU_POSITIONS;
			}
			
			// Print the selection cursor
			//if the menu item is in the left column
			if (cursor_position <= 3){
				lcd.setCursor(0, cursor_position);
			}
			//if the menu item is in the right column
			else {
				lcd.setCursor(9, cursor_position - 4);
			}
			lcd.write(CURSOR_SELECT_CHARACTER);
		}

		
		if (is_editing == 1){
			
			//if is editing, firstly substitute the selection character by the edition character
			if (cursor_position <= 3){
				lcd.setCursor(0, cursor_position);
			}
			//if the menu item is in the right column
			else {
				lcd.setCursor(9, cursor_position - 4);
			}
			lcd.write(CURSOR_EDIT_CHARACTER);

			// update the increment (delta) of the variable to edit
			delta_variable = delta_encoder_position / ENCODER_STEPS_PER_UNIT;

			switch (cursor_position) { //depending on the menu selected, perform the editing action
			    
			    case MOTOR_MENU:

			    	motor_duty_cycle += delta_variable;
			    	break;

			    case HEATER_1_MENU:

			    	heater_1_setpoint += delta_variable;
			    	break;

			    case HEATER_2_MENU:

			    	heater_2_setpoint += delta_variable;
			    	break;

			    case HEATER_3_MENU:
			    	heater_3_setpoint += delta_variable;
			    	break;

			    case FAN_MENU:
			    	fan_on += delta_variable;
			    	break;

			    case PULLER_MENU:
			    	puller_speed += delta_variable;
			    	break;
			}


		}


		//debugging aides
		// lcd.setCursor(11,2);
		// lcd.write( (int)is_clicked );

		// lcd.setCursor(15,2);
		// lcd.write( (int)cursor_position );

		// lcd.setCursor(11,3);
		// lcd.write( (int)is_editing );

	}

}


char conv[4];

char * dto3char(double d){
	//takes the double d and returns the string in format "123" (no decimals, three digits)
	int i = (int)d;
	
	//hundreds
	if (d >= 100.0){
		conv[0] = (i/100) + '0';
	}
	else {
		conv[0] = ' ';
	}
	//tens
	if (d >= 10.0){
		conv[1] = (i%100)/10 + '0';
	}
	else {
		conv[1] = ' ';
	}
	//units
	conv[2] = (i%10) + '0';
	
	//end of string
	conv[3] = 0;

	return conv;
}