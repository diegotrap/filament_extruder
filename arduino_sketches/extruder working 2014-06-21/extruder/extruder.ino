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
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
char emergency = 0;

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


void setup(){
  lcd.begin(16, 2);              // start the library
}

void loop(){

  lcd.setCursor(0,0);
  
//  switch (lcd_screen){
//    case screenScrewSpeed : {
//      lcd.print("Screw Speed     ");
//      currentValue = screwSpeed;
//      currentSetpoint = screwSpeedSetpoint;
//      break;
//    }
//    case screenTemperature1 : {
//      lcd.print("Z1 Temperature  ");
//      currentValue = temperature1;
//      currentSetpoint = temperature1Setpoint;
//      break;
//    }
//    case screenTemperature2 : {
//      lcd.print("Z2 Temperature  ");
//      currentValue = temperature2;
//      currentSetpoint = temperature2Setpoint;
//      break;
//    }
//  }
  

  
  
  lcd_key = read_LCD_buttons();  // read the buttons
  
  // if it has been a change in state
  if (lcd_key != previous_lcd_key) {
    
    lcd.setCursor(0,0);
    
    switch (lcd_screen){
      case screenScrewSpeed : {
        lcd.print("Screw Speed     ");
        currentValue = screwSpeed;
        currentSetpoint = screwSpeedSetpoint;
        break;
      }
      case screenTemperature1 : {
        lcd.print("Z1 Temperature  ");
        currentValue = temperature1;
        currentSetpoint = temperature1Setpoint;
        break;
      }
      case screenTemperature2 : {
        lcd.print("Z2 Temperature  ");
        currentValue = temperature2;
        currentSetpoint = temperature2Setpoint;
        break;
      }
    }

    switch (lcd_key) {               // depending on which button was pushed, we perform an action
      case btnRIGHT: {
        //save the previous values to update the variables
        switch (lcd_screen) {
          case (screenScrewSpeed):{
            screwSpeedSetpoint = currentSetpoint;
            break;
          }
          case (screenTemperature1):{
            temperature1Setpoint = currentSetpoint;
            break;
          }
          case (screenTemperature2):{
            temperature2Setpoint = currentSetpoint;
            break;
          }
        }
        lcd_screen++;
        break;
      }
      case btnLEFT: {
        //save the previous values to update the variables
        switch (lcd_screen) {
          case (screenScrewSpeed):{
            screwSpeedSetpoint = currentSetpoint;
            break;
          }
          case (screenTemperature1):{
            temperature1Setpoint = currentSetpoint;
            break;
          }
          case (screenTemperature2):{
            temperature2Setpoint = currentSetpoint;
            break;
          }
        }
        lcd_screen--;
        break;
      }
      case btnUP: {
        currentSetpoint++;
        //save the previous values to update the variables
        switch (lcd_screen) {
          case (screenScrewSpeed):{
            screwSpeedSetpoint = currentSetpoint;
            break;
          }
          case (screenTemperature1):{
            temperature1Setpoint = currentSetpoint;
            break;
          }
          case (screenTemperature2):{
            temperature2Setpoint = currentSetpoint;
            break;
          }
        }
        break;
      }
      case btnDOWN: {
        currentSetpoint--;
                //save the previous values to update the variables
        switch (lcd_screen) {
          case (screenScrewSpeed):{
            screwSpeedSetpoint = currentSetpoint;
            break;
          }
          case (screenTemperature1):{
            temperature1Setpoint = currentSetpoint;
            break;
          }
          case (screenTemperature2):{
            temperature2Setpoint = currentSetpoint;
            break;
          }
        }
        break;
      }
    }
     
    // Print the values
    lcd.setCursor(0,1);
    lcd.print(currentValue);
    
    lcd.setCursor(9,1);
    lcd.print(currentSetpoint); 
    
    previous_lcd_key = lcd_key;
    

  }
 
  setRGBLED();
  
}
