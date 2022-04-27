#include <SoftwareSerial.h>
#include <RingBuf.h>

SoftwareSerial portOne (7, 8); //(Rx, Tx)

void setupProximitySystem(){
  //setup code for pins, etc.
  portOne.begin(115200);
}

//obtains average of current (buffer size) distance readings 
float runningAverage(){
  float running_value = 0;
  for(int i = 0; i < myRingBuffer.size(); i++)
  {
    //Serial.println(myRingBuffer[i], 8);
    running_value = running_value + myRingBuffer[i];
  }
  float average = running_value/myRingBuffer.size();
  return average;
}

//add distance readings to buffer
void push_to_Buff(float value){
  if(myRingBuffer.isFull())
  {
    float deleted_val;
    myRingBuffer.pop(deleted_val);
  }
  //Serial.println(value, 8);
  if(value != 0)
  {
    myRingBuffer.push(value);
  }
  return;
}

float getProximity(){
  //reads signal from serial input I2C or UART and returns the double value.
  //double distance;
  //distance = test_potDistance();

  line = portOne.readStringUntil('\n');
  place = line.indexOf("Distance : ");
  if(place == 0){
    distance_read = (line.substring(11, 19)).toFloat();
  }
  //Serial.println(distance_read, 8);
  push_to_Buff(distance_read);
  float avg_distance = runningAverage();
  //Serial.println(avg_distance, 8);
  distance_inches = -2.98 + 30.9*(avg_distance) + 0.851*sq(avg_distance);
  //Serial.println(distance_inches);
  
  return distance_inches; 
}

/*
double test_potDistance(){
  //proximity simulation with potmeter
  double analogInput = analogRead(POTENTIOMETER_PIN);
  double distance = (analogInput*16)/1023;  //turn input value to range 0-16
  return distance;
}
*/
