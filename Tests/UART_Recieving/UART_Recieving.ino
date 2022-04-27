#include <SoftwareSerial.h>
#include <RingBuf.h>

SoftwareSerial portOne (7, 8); //(Rx, Tx)

float distance_read;
String line;
size_t place;
float distance_inches;

RingBuf<float, 100> myRingBuffer;

void setup()
{
  // Start the hardware serial port
  Serial.begin(115200);
  portOne.begin(115200);

}

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

void loop()
{
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
  Serial.println(distance_inches);
}
