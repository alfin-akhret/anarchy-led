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

};
