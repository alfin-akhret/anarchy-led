/**
  author: alfin.akhret@gmail.com
*/

class FadeInFadeOut {
  public:
    void crossFade(int color[3]);
    void go(int targetLed, int firstColor[3], int secondColor[3], int lapseTime, int steadyTime);

    int led, redVal, grnVal, bluVal, prevR, prevG, prevB, lapseTime, steadyTime;

  private:
    int calculateVal(int step, int val, int i);
    int calculateStep(int prevValue, int endValue);
};

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

 // CROSSFADE
void FadeInFadeOut::crossFade(int color[3]) {
  // Convert to 0-255
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




