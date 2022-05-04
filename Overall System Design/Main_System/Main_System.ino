#include <RingBuf.h>

void setup() {
  // put your setup code here, to run once:
  setupFeedbackSystem();
  initilizeDefaultFeedbackSystem();
  setupProximitySystem();
  setupBLESystem();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = getProximity();

  //send info to phone if connected to bluetooth
  getInfo(distance);
  
  //double distance = 72; //72 inches = 6 feet
  Serial.println(distance);
  if(distance <= 72){
    //trigger feedback system
    triggerFeedbackSystem(true);
  }
  if(distance > 72){
    //untrigger feedback system
    triggerFeedbackSystem(false);
  }
}
