int latchPin = 8;
int clockPin = 13;
int dataPin = 11;
int outputEnablePin = 3;
 
byte leds = 0;
 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  setBrightness(0);
  Serial.enable(9600); 
}
 
void loop() 
{
  /**
  setBrightness(255);
  leds = 0;
  updateShiftRegister();
  delay(500);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(500);
  }
  for (byte b = 255; b > 0; b--)
  {
    setBrightness(b);
    delay(10);
  }
  **/

  // lead nyala perlahan
  bitSet(leds, 0);
  updateShiftRegister();
  
  for (byte b = 30; b < 255; b++)
  {
    setBrightness(b);
    delay(50);
  }
  
  // redup perlahan
  for (byte b = 255; b > 30; b--)
  {
    setBrightness(b);
    delay(10);
  }

  // green
  bitClear(leds, 0);
  bitSet(leds, 1);
  updateShiftRegister();
  
  for (byte b = 30; b < 255; b++)
  {
    setBrightness(b);
    delay(50);
  }
  
  // redup perlahan
  for (byte b = 255; b > 30; b--)
  {
    setBrightness(b);
    delay(10);
  }

  
}
 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
 
void setBrightness(byte brightness) // 0 to 255
{
  analogWrite(outputEnablePin, 255-brightness);
}

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}
