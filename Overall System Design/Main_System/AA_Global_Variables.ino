//ALL GLOBAL VARIABLES FOR ALL SYSTEMS

///////////////////////////////////////////////////////////////

//Global Variables for Feedback Systems

bool gbl_ledPwr;          // on/off
int gbl_ledMode;          // 1:blink 2:continuous
bool gbl_soundPwr;        // on/off
int gbl_soundVol;         // volume: 1-10
int gbl_soundMode;        // 1:preset1, 2:preset2, etc.
bool gbl_hapticPwr;       // on/off
int gbl_hapticIntensity;  // intensity: 1-3
int gbl_hapticMode;       // 1: low, 2: med, 3: high
                          // low: Waits 5 seconds when triggered to turn on, stays on for 5 seconds, then turns off.
                          // med: Waits 3 seconds when triggered to turn on, alternate on and off for 5 seconds each until triggered off
                          // high: Immediately turns on when triggered and stays on until out triggered off


////////////////////////////////////////////////////////////////

//LED GBL VARS

#define LED_PIN 6

#define SINGLE_LED_PIN 12

//LED_Output GLOBAL VARIABLES

#define GREEN strip.Color(0, 255, 0) // Green color for LED ring
#define RED strip.Color(255, 0, 0) // Red color for LED ring

long interval = 250;      //Initilizes blink interval
long previousMillis = 0;  //Initilizes previous time stamp
int ledState = HIGH;      //Initilizes first LED State

///////////////////////////////////////////////////////////////

//HAPTIC GLOBAL VARIABLES

#define MOTOR 5 //Vibration motor pin
#define OFF 0 //No vibration at all
#define LEVEL_1 50 //20% vibration level
#define LEVEL_2 100 //40% vibration level
#define LEVEL_3 150 //60% vibration level
#define LEVEL_4 200 //80% vibration level
#define LEVEL_5 255 //100% (Max) vibration level


///////////////////////////////////////////////////////////////

//PROXIMITY GLOBAL VARIABLES

#define POTENTIOMETER_PIN A0
