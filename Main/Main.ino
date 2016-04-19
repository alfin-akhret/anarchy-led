/**
 * Anarchy Led
 * Desc: Led installation for Alvan Hafiz's Artwork
 * Using Elco Jacob's awesome ShiftPWM library
 * @autho: alfin.akhret@gmail.com
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
#include "hsv2rgb.h"
// Include main Led scenario lib
#include "FadeInFadeOut.h"

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


// magenta ke toska
int toska[3] = {0,255,255};
int magenta[3] = {125, 0, 255};
int ungu[3] = {75, 0, 255};
int orange[3] = {160, 180, 0};
int merah[3] = {180, 0, 0};
int hijau[3] = {0, 255, 0};
int biru[3] = {0, 0, 255};

int off[3] = {0, 0, 0};

void loop()
{    
  Serial.println("Testing serial output\n");
  Serial.println("Testing stino\n");

  // Toska ke magenta
  FadeInFadeOut fifo;
  for(int i = 0; i < 1; i++){
    fifo.go(0, off, magenta, 10, 0);
    fifo.go(0, magenta, toska, 5, 2000);
    fifo.go(0, toska, magenta, 5, 2000);
  }
  fifo.go(0, magenta, off, 5, 0);

  // Ungu ke Orange
  for(int i = 0; i < 1; i++){
    fifo.go(1, off, ungu, 10, 0);
    fifo.go(1, ungu, orange, 5, 2000);
    fifo.go(1, orange, ungu, 5, 2000);
  }
  fifo.go(1, ungu, off, 5, 0);

  // toska ke merah
  for(int i = 0; i < 1; i++){
    fifo.go(2, off, toska, 10, 0);
    fifo.go(2, toska, merah, 5, 2000);
    fifo.go(2, merah, toska, 5, 2000);
  }
  fifo.go(2, toska, off, 5, 0);

  // magenta ke biru
  for(int i = 0; i < 1; i++){
    fifo.go(3, off, magenta, 10, 0);
    fifo.go(3, magenta, biru, 5, 2000);
    fifo.go(3, biru, magenta, 5, 2000);
  }
  fifo.go(3, magenta, off, 5, 0);
  
  // hijau ke magenta
  for(int i = 0; i < 1; i++){
    fifo.go(4, off, hijau, 10, 0);
    fifo.go(4, hijau, magenta, 5, 2000);
    fifo.go(4, magenta, hijau, 5, 2000);
  }
  fifo.go(4, hijau, off, 5, 0);
  
}


