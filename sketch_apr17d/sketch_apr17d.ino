int latchPin = 8;
int clockPin = 13;
int dataPin = 11;
int outputEnablePin = 3;
 
//byte leds = 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  setBrightness(0);
  Serial.begin(9600); 
}
 
void loop() 
{
  // setting init value
  
  fadeIn(1, 2, 10);
  fadeOut(2, 3, 1);
  
  
}
 
void fadeIn(int r, int g, int fadeStep)
{
   for(int j = 0; j < 255; j+=fadeStep) {
      for(int i = 0; i<255; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, r);
        digitalWrite(latchPin, HIGH);
  
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, g); // 00000001
        digitalWrite(latchPin, HIGH);  
      }
      setBrightness(j);
   }
      
}

void fadeOut(int r, int g, int fadeStep)
{
   for(int j = 255; j > 0; j-=fadeStep) {
      for(int i = 0; i<255; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, r);
        digitalWrite(latchPin, HIGH);
  
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, g); // 00000001
        digitalWrite(latchPin, HIGH);  
      }
      setBrightness(j);
   }
      
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
