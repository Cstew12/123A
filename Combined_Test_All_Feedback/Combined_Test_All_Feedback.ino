/* 
 * CSE 123 Group 8: The Social Distancers
 * Author: Maxwell Voorhes
 * Test: Combined Test - All Feedbacks
 * Date: 3/9/2022
 */

/* Pins
 * 
 * LED Pins
 * Red: pin 3
 * Green: pin 5
 * Blue: pin 4
 * 
 * Ultrasonic pins
 * Echo: pin 6
 * Trig: pin 7
 * 
 * Speaker
 * Signal: pin 9
 * 
 * Vibration motor: pin 10
 */

#include "pitches.h"

const int echo = 6; // echo pin
const int trig = 7; // trig pin

const int red_led_pin = 3;    // Red pin
const int green_led_pin = 5;  // Green pin
const int blue_led_pin = 4;   // Blue pin

const int mvm = 10; // microvibration motor is connected with pin number 5 witch is the pwm pin
const int vresistor = A1; // potentiometer data pin is A1
int data = 0; // resistance initially starts at 0

bool speak = 0;

int melody[] = {NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, END};
int note_durations[] = {4, 4, 8, 12, 8, 8, 8, 4, 4, 4};

int speed = 30; // Speed of melody (higher num = longer)
void setup() {

  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);

  pinMode(mvm, OUTPUT);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(9600);
}

void RGB_color(int red, int green, int blue) {
  analogWrite(red_led_pin, red);
  analogWrite(green_led_pin, green);
  analogWrite(blue_led_pin, blue);
}

void led_test(long distance) {
  if (distance >= 6) {
    RGB_color(255, 0, 255);
  } else if (distance < 6) {
    RGB_color(0, 255, 255);
  }
}

void loop_song() {
  for (int i = 0; melody[i] != -1; i++) {
    int noteDuration = speed * note_durations[i];
    tone(9, melody[i], noteDuration * .95);
    delay(noteDuration);
    noTone(9);
  }
}

void speaker_test(long distance) {
  if (distance <= 6) {
    loop_song();
    speak = 1;
  } else {
    speak = 0;
  }
}

void vibration_test(long distance) {
  if (distance <= 6) {
    data = 255;
  } else {
    data = 0;
  }
  analogWrite(mvm, data);
}

int test = 0; // 0 = LED, 1 = Speaker, 2 = vibration
void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;

  // Write to ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);

  // Get duration in inches and centimeters
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Determines test to run
  if (test == 1) {
    speaker_test(inches);
    RGB_color(0,0,0);
  } else if (test == 2) {
    vibration_test(inches);
    RGB_color(0,0,0);
  } else {
    led_test(inches);
  }

  // print
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (speak == 1) {
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

// Sources
// https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm#:~:text=Advertisements,or%201%E2%80%9D%20to%2013%20feet.
// https://maker.pro/arduino/projects/arduino-speaker
// Anthonys LED Code
// Terrences Vibration Code
