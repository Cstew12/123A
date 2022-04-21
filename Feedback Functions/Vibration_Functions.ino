/*
 * CSE 123A Group 8: Social Distancers
 * Author: Terrence Ng
 * Description: Functions For the Vibrations on the soial distance detectin device
 * Date: 4/18/2022
 */

#define MOTOR 5 //Vibration motor pin
#define OFF 0 //No vibration at all
#define LEVEL_1 50 //20% vibration level
#define LEVEL_2 100 //40% vibration level
#define LEVEL_3 150 //60% vibration level
#define LEVEL_4 200 //80% vibration level
#define LEVEL_5 255 //100% (Max) vibration level

int current_level = 0; //current vibration level
int last_level = LEVEL_5; //last known non zero vibration level

//vibrates the vibration motors at the specified current level (global variable)
void triggerHaptic() {
  current_level = last_level; //set vibration to last level
  analogWrite(MOTOR, current_level); //vibrate MOTOR at specified data level
}

//initiallization code for vibrations
void initialize_vibration() {
  pinMode(MOTOR, OUTPUT); //setup vibration motor pins
}

//turn off vibration 
//save last vibration level
void Haptic_Output_killHaptic() {
   last_level = current_level; //save current vibration level
   current_level = OFF; //turn off 
   analogWrite(MOTOR, OFF); //dont send any power to the vibration motor
}

//change vibration amount to level
//should be one of the predefined vibration levels
void set_hapticIntensity(int hapticIntensity){
  //sets global variable to Haptic intensity
  gbl_hapticIntensity = hapticIntensity;
}
