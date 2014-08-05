#include <Encoder.h>
#include <LiquidCrystal.h>

// LCD Keyboard buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Display screens
#define screenScrewSpeed    0
#define screenTemperature1  1
#define screenTemperature2  2

//RGB LED Pins
#define redRGBLEDPin 13
#define greenRGBLEDPin 12
#define blueRGBLEDPin 11

// LCD panel pins

#define LCD_RS_PIN 8 
#define LCD_EN_PIN 9
#define LCD_D4_PIN 4
#define LCD_D5_PIN 5
#define LCD_D6_PIN 6
#define LCD_D7_PIN 7

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_screen = 0; //selected screen
int previous_lcd_screen = 1; //last screen, used to update the setpoint values

int lcd_key = 0; //pressed key
int previous_lcd_key = 1; //last pressed key, used to detect state changes


// Extruder variables
float screwSpeed = 1;
float temperature1 = 2;
float temperature2 = 3;

// Setpoint values
float screwSpeedSetpoint = 0;
float temperature1Setpoint = 0;
float temperature2Setpoint = 0;

// Current extruder variable and setpoint
float currentValue = 0;
float currentSetpoint = 0;

float previousValue = 0;
float previousSetpoint = 0;


//Read the pressed button from the LCD keypad
int read_LCD_buttons() {
  /*******************************************************
  This function has been written from the code by Mark Bramwell, July 2010
  Found in: http://www.dfrobot.com/wiki/index.php?title=Arduino_LCD_KeyPad_Shield_%28SKU:_DFR0009%29
  ********************************************************/

  int adc_key_in;
  adc_key_in = analogRead(0); //read value of the keypad analog output
  
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 821)  return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT; 
  if (adc_key_in < 176)  return btnUP;
  if (adc_key_in < 328)  return btnDOWN;
  if (adc_key_in < 518)  return btnLEFT;
  if (adc_key_in < 821)  return btnSELECT;

  return btnNONE;
}

// Emergency bit, set to 1 if something doesn't work
char emergency = 1;

void setRGBLED(){
  if (emergency == 1){
    digitalWrite(redRGBLEDPin, HIGH);
    digitalWrite(blueRGBLEDPin, LOW);
    digitalWrite(greenRGBLEDPin, LOW);
  }
  else {
    digitalWrite(redRGBLEDPin, LOW);
    digitalWrite(blueRGBLEDPin, LOW);
    digitalWrite(greenRGBLEDPin, HIGH);
  }
}

void setEmergencyLED(){
  if(emergency == 1){
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}

Encoder MotorEncoder(2, 3); //Brown cable in pin 3
                            //White cable in pin 2
                            
unsigned long last_micros = 0;

float getScrewSpeed(){
  
  float motor_speed, motor_position;
  
  motor_position = MotorEncoder.read();
  
  motor_speed = (motor_position/1200.0)/(micros()-last_micros);
  
  //convert from rev/us to rev/min
  motor_speed = motor_speed*600000;
  
  //store the last_micros value
  last_micros = micros();
  MotorEncoder.write(0); 
  
  return motor_speed;
}

float pot_read = 0;
float motor_duty_cycle = 0;


void setup(){
  lcd.begin(16, 2);              // start the library
  
  pinMode(11, OUTPUT); //IN2 pin, controls the red terminal of the motor (V+, PWM Speed control
  pinMode(12, OUTPUT); //IN1 pin, controls the black terminal of the motor (GND)
  pinMode(0, INPUT); //SF flag
  
  pinMode(13, OUTPUT); //emergency LED pin
}

void loop(){
  
  screwSpeed = getScrewSpeed();
  
  pot_read = analogRead(1);
  motor_duty_cycle = pot_read/1023.0; 

  lcd.setCursor(0,0);
  lcd.print("Motor Speed     ");
  lcd.setCursor(0,1);
  lcd.print(screwSpeed);
  lcd.setCursor(9,1);
  lcd.print(motor_duty_cycle);
 
  if (digitalRead(0) == LOW){ //check SF flag for overtemperature or shorts (active if LOW)
    emergency = 1;
  } else {
    emergency = 0;
  }
  
  
  
  
  digitalWrite(12, LOW);
  analogWrite(11, motor_duty_cycle*255.0);
  
  setEmergencyLED();
  
  
}
