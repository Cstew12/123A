#define POTENTIOMETER_PIN A0

void setupProximitySystem(){
  //setup code for pins, etc.
}


double getProximity(){
  //reads signal from serial input I2C or UART and returns the double value.
  double distance;
  distance = test_potDistance();
  return distance; 
}

double test_potDistance(){
  //proximity simulation with potmeter
  double analogInput = analogRead(POTENTIOMETER_PIN);
  double distance = (analogInput*16)/1023;  //turn input value to range 0-16
  return distance;
}
