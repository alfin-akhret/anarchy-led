/**
 * Anarchy Led
 * Desc: Led installation for Alvan Hafiz's Artwork
 * @autho: alfin.akhret@gmail.com
 * 
 */
// Pin for HC595 Storage register (latch)
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
#define SHIFTPWM_NOSPI
const int ShiftPWM_dataPin = 11;  // Pin for HC595 Serial (DS)
const int ShiftPWM_clockPin = 13; // Pin for HC595 Shift register (clock)


// True = Invert pin behavior. LOW = ON
// False = Normal pin behavior. LOW = OFF
const bool ShiftPWM_invertOutputs = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Include main Led scenario lib
#include "LedScenario.h"

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

// set brightness step
unsigned char maxBrightness = 255;

// set PWM frequency. Higher = smoother but more CPU usage. Lower = flicker, but less CPU usage
unsigned char pwmFrequency = 75;

// Number of shift register 
int numRegisters = 2;
// Led number based on register number
int numRGBleds = numRegisters*8/3;

void setup(){
  Serial.begin(9600);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);

}

void loop()
{    
  // Fade in and fade out all outputs one by one fast. Usefull for testing your hardware. Use OneByOneSlow when this is going to fast.
  // ShiftPWM.OneByOneFast();
  /**
  for(int hue = 231; hue>231; hue--){
    ShiftPWM.SetHSV(3, hue, 100, 100); 
    delay(50);
  }
  **/
  // Update random LED to random color. Funky!
  int fadeIn = 0;
  for(int j = 255; j > 100; j--) {
    if(fadeIn >= (280-231)) {
      break;  
    } else {
      ShiftPWM.SetHSV(1, 231+fadeIn,255,255);  
    }
    delay(200);
    fadeIn++;
  }
  int fadeOut = 280;
  for(int j = 0; j < 100; j++) {
    if(fadeOut <= 0) {
      break;  
    } else {
      ShiftPWM.SetHSV(1, fadeOut,255,255);  
    }
    delay(200);
    fadeOut--;
  }
  

}
