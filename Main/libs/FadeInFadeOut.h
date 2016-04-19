/**
  author: alfin.akhret@gmail.com
* Crossfading only one led using with help of ShiftPWM
* Cara penggunaan:
* Jika ingin menggunakan pada file .ino
  
  #include "libs/FadeInFadeOut.h"

  int green[3] = {0, 255, 0};
  int red[3] = {255, 0, 0};
  int led = 0;
  void loop() {
    FadeInFadeOut ff;
    ff.go(led, green, red, 100, 2000); 
}

NOTES: untuk detail cara pengguna lihat file /scenario/FadeSerie.h
*/

class FadeInFadeOut {
  public:
    void go(int targetLed, int firstColor[3], int secondColor[3], int lapseTime, int steadyTime);
    int led, redVal, grnVal, bluVal, prevR, prevG, prevB, lapseTime, steadyTime;

  private:
    void crossFade(int color[3]);
    int calculateVal(int step, int val, int i);
    int calculateStep(int prevValue, int endValue);
};

// go()
// @desc: 		Crossfading dari satu led dari warna pertama ke warna kedua 
// @params:		
// int targetLed 	nomor LED yang akan dimanipulasi	
// int[] firstColor 	warna RGB awal. berbentuk array. contoh: lihat file colorConfig.h	
// int[] secondColor 	warna RGB akhir. berbentuk array. contoh: lihat file colorConfig.h	
// int l 		lapseTime, waktu yang dibutuhkan untuk transisi dari warna awal ke warna akhir. default 10 ms
// int s		Steady time, waktu yang digunakan untuk "steady" atau diam. 
//          waktu ini berlaku untuk warna awal dan warna akhir. default 4000 ms 
void FadeInFadeOut::go(int targetLed, int firstColor[3], int secondColor[3], int l=10, int s=4000) {
  redVal = firstColor[0]; // r1
  grnVal = firstColor[1]; // r2
  bluVal = firstColor[2]; // r3
  prevR = redVal; // r1
  prevG = grnVal; // r2
  prevB = bluVal; // r3
  lapseTime = l;
  steadyTime = s;

  led = targetLed;

  crossFade(secondColor);
}

// PRIVATE CLASS MEMBERS
// jangan diganggu.
void FadeInFadeOut::crossFade(int color[3]) {

  int R = color[0];
  int G = color[1];
  int B = color[2];

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 255; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    ShiftPWM.SetRGB(led, redVal, grnVal, bluVal);

    delay(lapseTime); // Pause for 'wait' milliseconds before resuming the loop
  }

  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(steadyTime); // Pause for optional 'wait' milliseconds before resuming the loop
}

int FadeInFadeOut::calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

int FadeInFadeOut::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 255/step;              //   divide by 1020
  } 
  return step;
}




