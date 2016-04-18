class LedScenario {
  public:
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

    void smooth2Color1Led(int led, int *startColor, int *endColor, int internalDelay, int iteration=2) {

      for(int loopIteration = iteration; loopIteration > 0; loopIteration--) {
        int internalLoop = 360; // internal loop count
        int colorChangeStep;
      
        int tmp = *startColor;
      
        if(*startColor > *endColor) {
          // slideDown
          colorChangeStep = internalLoop - *endColor;
          
          for(int j = 0; j < colorChangeStep; j++) {
            if(*startColor <= *endColor) {
              break;  
            }
            ShiftPWM.SetHSV(led, *startColor-=1, 255, 255);  
            delay(internalDelay);
          }
        } else {
          // climbUp
          colorChangeStep = internalLoop - *startColor;
          for(int j = 0; j < colorChangeStep; j++) {
            if(*startColor >= *endColor) {
              break;  
            }
            ShiftPWM.SetHSV(led, *startColor+=1, 255, 255);  
            delay(internalDelay);
          }
        }
        // swap color
        *startColor = *endColor;
        *endColor = tmp;
      }
      
    }

};
