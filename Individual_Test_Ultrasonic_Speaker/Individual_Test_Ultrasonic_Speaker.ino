#include "pitches.h"

int echo = 6;
int trig = 7;

int melody[] = {NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, END};
int note_durations[] = {4, 4, 8, 12, 8, 8, 8, 4, 4, 4};

int speed = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  long duration, inches, cm;

  // write
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // get duration
  duration = pulseIn(echo, HIGH);

  // convert
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Respond
  distance(inches);

  // print
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (inches <= 6) {
    delay(1);
  } else {
    delay(1000); 
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void distance(int inches) {
  if (inches <= 6) {
    loop_song();
  }
}

void loop_song() {
  for (int i = 0; melody[i] != -1; i++) {
    int noteDuration = speed * note_durations[i];
    tone(3, melody[i], noteDuration * .95);
    delay(noteDuration);
    noTone(3);
  }
}

// Sources
// https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm#:~:text=Advertisements,or%201%E2%80%9D%20to%2013%20feet.
// https://maker.pro/arduino/projects/arduino-speaker
