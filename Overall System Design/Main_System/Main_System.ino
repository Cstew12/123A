void setup() {
  // put your setup code here, to run once:
  setupFeedbackSystem();
  initilizeFeedbackSystem();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double distance = getProximity();
  //int test = getBatteryLife();
  //double distance = 6;
  Serial.println(distance);
  if(distance <= 6){
    //trigger feedback system
    triggerFeedbackSystem(true);
  }
  if(distance > 6){
    //untrigger feedback system
    triggerFeedbackSystem(false);
  }
}
