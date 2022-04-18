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

void setup() {
  pinMode(MOTOR, OUTPUT); //setup vibration motor pins
}

/*
void loop() {
  analogWrite(MOTOR, data); //vibrate MOTOR at specified data level
*/

//vibrates the vibration motors at the specified level when not at a safe distance (< 6ft)
//could remove level argument and just run the motor at the current level global variable
void runVibrate(bool safe, int level) {
  if(safe) { //more than 6 feet away
    analogWrite(MOTOR, 0); //vibrate MOTOR at specified data level
  } else { //less than 6 feet away
    analogWrite(MOTOR, level); //vibrate MOTOR at specified data level
  }
}

//turn off vibration 
void vibrationOFF() {
   last_level = current_level; //save current vibration level
   current_level = OFF; //turn off 
}

//turn on vibratrion (level is same as last known vibration, LEVEL_5 otherwise)
void vibrationON() {
  if(last_level == 0) { //if previously no vibration before it was off
    current_level = LEVEL_5; //set vibraiton to max
  } else {
    current_level = last_level; //set vibration to last level
  }
}

//change vibration amount to level
//should be one of the predefined vibration levels
void setVibLevel(int level) {
  current_level = level;
}
