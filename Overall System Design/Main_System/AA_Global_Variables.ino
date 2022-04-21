//ALL GLOBAL VARIABLES FOR ALL SYSTEMS

///////////////////////////////////////////////////////////////

//Global Variables for Feedback Systems

bool gbl_ledPwr;          // on/off
int gbl_ledMode;          // 1:blink 2:continuous
bool gbl_soundPwr;        // on/off
int gbl_soundVol;         // volume: 1-10
int gbl_soundMode;        // 1:preset1, 2:preset2, etc.
bool gbl_hapticPwr;       // on/off
int gbl_hapticIntensity;  // intensity: 1-5
int gbl_hapticMode;       // 1: low, 2: med, 3: high
                          // low: Waits 5 seconds when triggered to turn on, stays on for 5 seconds, then turns off.
                          // med: Waits 3 seconds when triggered to turn on, alternate on and off for 5 seconds each until triggered off
                          // high: Immediately turns on when triggered and stays on until out triggered off


////////////////////////////////////////////////////////////////
//LED GBL VARS



//LED_Output GLOBAL VARIABLES

long interval = 250;      //Initilizes blink interval
long previousMillis = 0;  //Initilizes previous time stamp
int ledState = HIGH;      //Initilizes first LED State

///////////////////////////////////////////////////////////////

//PROXIMITY GLOBAL VARIABLES

#define POTENTIOMETER_PIN A0
