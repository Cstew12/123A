#include "pitches.h"

int echo = 6;
int trig = 7;

int melody[] = {NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4};
int note_durations[] = {4, 4, 8, 12, 8, 8, 8, 4, 4, 4};

int speed = 5;
void loop_song() {
  for (int i = 0; melody[i] != -1; i++) {
    int noteDuration = speed * note_durations[i];
    tone(3, melody[i], noteDuration * .95);
    delay(noteDuration);
    noTone(3);
  }
}

void setup() {
  Serial.begin(9600);
  loop_song();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

// Sources
// https://maker.pro/arduino/projects/arduino-speaker
