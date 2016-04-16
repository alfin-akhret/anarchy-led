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
  
  // tampilkan
  
  fadeIn(1, 2, 10);
  fadeOut(2,3, 1);

  /**
  for (byte b = 30; b < 255; b++)
  {
    
    setBrightness(b);
    delay(50);
  }**/

  /**
  // redup perlahan
  for (byte b = 255; b > 30; b--)
  {
    setBrightness(b);
    delay(10);
  }
  **/
  
  
}
 
void fadeIn(int x, int y, int fadeStep)
{
   for(int j = 0; j < 255; j+=fadeStep) {
      for(int i = 0; i<255; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, x);
        digitalWrite(latchPin, HIGH);
  
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, y); // 00000001
        digitalWrite(latchPin, HIGH);  
      }
      setBrightness(j);
   }
      
}

void fadeOut(int x, int y, int fadeStep)
{
   for(int j = 255; j > 0; j-=fadeStep) {
      for(int i = 0; i<255; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, x);
        digitalWrite(latchPin, HIGH);
  
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, y); // 00000001
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
