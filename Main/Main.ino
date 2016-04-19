/**
 * Anarchy Led
 * Desc: Led installation for Alvan Hafiz's Artwork
 * Using Elco Jacob's awesome ShiftPWM library
 * @author: alfin.akhret@gmail.com
 ------------------------------------------------------------------------ 
 */
 
 /** MAIN CONFIGURATION 
 /* Jangan diganti2, lihat docs ShiftPWM kalau mau ganti2
 --------------------------------------------------------------------------
 */
#define SHIFTPWM_NOSPI
const int ShiftPWM_latchPin=8;                    // Pin for HC595 Storage register (latch)
const int ShiftPWM_dataPin = 11;                  // Pin for HC595 Serial (DS)
const int ShiftPWM_clockPin = 13;                 // Pin for HC595 Shift register (clock)
const bool ShiftPWM_invertOutputs = false; 
const bool ShiftPWM_balanceLoad = true;

/** Include ShiftPWM **/
// Include disini jangan dipindah2kan
// Notes: https://www.arduino.cc/en/Guide/Libraries
#include <ShiftPWM.h>                        

/** SCENARIO FILES 
/* Include semua scenario files yang akan digunakan disini
/* -------------------------------------------------------------------------- 
*/
#include "scenario/FadeSeries.h"

/** Settingan Umum ShiftPWM **
/ ---------------------------------------------------------------------------*/
unsigned char maxBrightness = 255;                // set brightness step

// set PWM frequency. 
// Higher = smoother but more CPU usage. 
// Lower = flicker, but less CPU usage
unsigned char pwmFrequency = 75;

// Number of shift register 
int numRegisters = 2;

// Led number based on register number
int numRGBleds = numRegisters*8/3;

/* Arduino Setup 
/* ----------------------------------------------- */ 
void setup(){
  Serial.begin(9600);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
}

/* Main Program
/* ----------------------------------------------*/
void loop()
{    
  FadeSeries();
}




