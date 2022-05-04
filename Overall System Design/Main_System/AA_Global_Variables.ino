//ALL GLOBAL VARIABLES FOR ALL SYSTEMS

///////////////////////////////////////////////////////////////

//POWER NEEDS TO BE 3.3V ON NANO BLE 33

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


//BLE GBL VARS
#define BATTERY_PIN A0
int32_t silentMode = 0;
//int32_t volume = 10;


////////////////////////////////////////////////////////////////


//LED GBL VARS

#define LED_PIN D10 //(pin 13 (D10) on nano, 6 on UNO)

#define SINGLE_LED_PIN 22

//LED_Output GLOBAL VARIABLES

#define GREEN strip.Color(0, 255, 0) // Green color for LED ring
#define RED strip.Color(255, 0, 0) // Red color for LED ring

long interval = 250;      //Initilizes blink interval
long previousMillis = 0;  //Initilizes previous time stamp
int ledState = HIGH;      //Initilizes first LED State


///////////////////////////////////////////////////////////////


//HAPTIC GLOBAL VARIABLES

#define MOTOR D3 //Vibration motor pin (6 (D3) on nano, 5 on UNO)

#define OFF 0 //No vibration at all

///////////////////////////////////////////////////////////////


//SOUND GLOBAL VARIABLES

#define SOUND_PIN D8 //Sound pin (11 (D8) on nano, 4 on UNO)
int volume = 255;

///////////////////////////////////////////////////////////////


//PROXIMITY GLOBAL VARIABLES

//Software serial pins for RX and TX for getting distance is inside Proximity_System

float distance_read;
String line;
size_t place;
float distance_inches;

RingBuf<float, 10> myRingBuffer;

#define POTENTIOMETER_PIN A0
