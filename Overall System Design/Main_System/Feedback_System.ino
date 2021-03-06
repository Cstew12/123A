
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//LED strip declaration
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupFeedbackSystem(){
  //setup code for pins, etc.
  initialize_LED();
  initilize_Haptic();
}

void initilizeDefaultFeedbackSystem(){
  //initilize feedback system to default settings (everything on, full intensity)
  gbl_ledPwr = true;        //Default: LED On
  gbl_ledMode = 2;          //Default: LED Continuous
  gbl_soundPwr = true;      //Default: Sound On
  gbl_soundVol = 7;         //Default: Sound Vol 7 out of 10
  gbl_soundMode = 1;        //Default: Sound preset 1
  gbl_hapticPwr = true;     //Default: Haptic On
  gbl_hapticIntensity =1;  //Default: Haptic Full Intensity
  gbl_hapticMode = 3;       //Default: Haptic High Alert (3)
}

void triggerFeedbackSystem(bool trigger){
  //triggers all feedback systems based on their on/off preferences
  if(trigger){
    if(gbl_ledPwr){
      //if led power setting is on 
      triggerLed();
    }
    if(gbl_soundPwr){
      //if sound power setting is on
      triggerSound();
    }
    if(gbl_hapticPwr){
      //if haptic power setting is on
      triggerHaptic();
    }
  }
  else if(!trigger){
    //if feedback devices are untriggered
    killFeedback();
  }
}

void killFeedback(){
  //turns off all feedback devices
  LED_Output_continuous(GREEN);
  //LED_Output_killLED();
  //Sound_Output_killSound;
  Haptic_Output_kill();
}

void triggerLed(){
  //turns on led to specified mode
  if(gbl_ledMode == 1){
    //blink LED
    LED_Output_blink();
  }
  else if(gbl_ledMode == 2){
    //continuous LED
    LED_Output_continuous(RED);
  }
  else{
    //led mode invalid: throw error
  }
}

void triggerSound(){
  //turns on speaker to specified volume with preset sound
  
}

void triggerHaptic(){
  //turns on haptic device to specified intensity and mode
  triggerHaptic_HIGH();
}

//All below functions set global feedback settings

void set_ledPower(bool ledPwr){
  //sets global variable to LED On or Off
  gbl_ledPwr = ledPwr;
}

void set_ledMode(int ledMode){
  //sets global variable to indicate LED mode
  gbl_ledMode = ledMode;
}

void set_soundPower(bool soundPwr){
  //sets global variable to Speaker On or Off
  gbl_soundPwr = soundPwr;
}

void set_soundVolume(int soundVol){
  //sets global variable to incdicate Speaker volume
  gbl_soundVol = soundVol;
}

void set_soundMode(int soundMode){
  //sets global variable to indicate Speaker mode
  gbl_soundMode = soundMode;
}

void set_hapticPower(bool hapticPwr){
  //sets global variable to Haptic On or Off
  gbl_hapticPwr = hapticPwr;
}

void set_hapticIntensity(int hapticIntensity){
  //sets global variable to Haptic intensity
  gbl_hapticIntensity = hapticIntensity;
}

void set_hapticMode(int hapticMode){
  //sets global variable to Haptic mode
  gbl_hapticMode = hapticMode;
}
