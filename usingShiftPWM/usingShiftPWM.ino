/************************************************************************************************************************************
 * ShiftPWM blocking RGB fades example, (c) Elco Jacobs, updated August 2012.
 *
 * ShiftPWM blocking RGB fades example. This example uses simple delay loops to create fades.
 * If you want to change the fading mode based on inputs (sensors, buttons, serial), use the non-blocking example as a starting point.
 * Please go to www.elcojacobs.com/shiftpwm for documentation, fuction reference and schematics.
 * If you want to use ShiftPWM with LED strips or high power LED's, visit the shop for boards.
 ************************************************************************************************************************************/
 
// ShiftPWM uses timer1 by default. To use a different timer, before '#include <ShiftPWM.h>', add
// #define SHIFTPWM_USE_TIMER2  // for Arduino Uno and earlier (Atmega328)
// #define SHIFTPWM_USE_TIMER3  // for Arduino Micro/Leonardo (Atmega32u4)

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
#define SHIFTPWM_NOSPI
const int ShiftPWM_dataPin = 11;
const int ShiftPWM_clockPin = 13;


// Setting ini menjadi True kalau pengen behavior pin menjadi menjadi terbalik
// atau LOW = lampu nyala
// sebaiknya di setting False aja
const bool ShiftPWM_invertOutputs = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

// ini cuma buat mensetting brightness step. Max 255 karena brghtness disimpan dalam bentuk byte.
// ingat! ini cuma buat setting step aja, jadi diturunkan pun brightness nya tetap segitu.
unsigned char maxBrightness = 255;
// Settin PWM frequency. makin tinggi makin smooth, tp makan resource CPU
unsigned char pwmFrequency = 75;
// jumlah Shift register yang digunakan
int numRegisters = 2;
// perhitungan LED
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
  // resultnya jadi orange, sepertinya ada hubungannya dengan pemakaian resistor yang cuma 1 (ground)
  // sehingga RED menjadi lebih dominan karena RED butuh hambatan lebih besar dibanding warna lain.
  // ShiftPWM.SetRGB (0, 255, 255, 255);

  // Intensitas RED dikurangi untuk menghasilkan warna PUTIH
  // ShiftPWM.SetRGB (0, 180, 255, 255);
  ShiftPWM.OneByOneFast();
  
}

// kedip2 slow to fast to steady
void kedipSlowToFast(int led, unsigned char r, unsigned char g, unsigned char b) {
  for(int i = 255; i > 0; i-=10) {
    ShiftPWM.SetRGB (led, r, g, b);
    delay(i);
    ShiftPWM.SetRGB (led, 0, 0, 0);
    delay(i);  
  }

  for(int i = 90; i > 0; i--) {
    ShiftPWM.SetRGB (led, r, g, b);
    delay(20);
    ShiftPWM.SetRGB (led, 0, 0, 0);
    delay(20);  
  }

  for(int i = 0; i < 255; i+=10) {
    ShiftPWM.SetRGB (led, r, g, b);
    delay(i);
    ShiftPWM.SetRGB (led, 0, 0, 0);
    delay(i);  
  }
}


void rgbLedRainbow(int numRGBLeds, int delayVal, int numCycles, int rainbowWidth){
  // Displays a rainbow spread over a few LED's (numRGBLeds), which shifts in hue. 
  // The rainbow can be wider then the real number of LED's.

  ShiftPWM.SetAll(0);
  for(int cycle=0;cycle<numCycles;cycle++){ // loop through the hue shift a number of times (numCycles)
    for(int colorshift=0;colorshift<360;colorshift++){ // Shift over full color range (like the hue slider in photoshop)
      for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
        int hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
        ShiftPWM.SetHSV(led, hue, 255, 255); // write the HSV values, with saturation and value at maximum
      }
      delay(delayVal); // this delay value determines the speed of hue shift
    } 
  }  
}
