#include "pitches.h"
#include "Volume.h"

#define SOUND_PIN 5

Volume vol(SOUND_PIN);

int melody_1[] = {NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4, END};
int note_durations_1[] = {4, 4, 8, 12, 8, 8, 8, 4, 4, 4};

int melody_2[] = {NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_G4, NOTE_A4, END};
int note_durations_2[] = {4, 4, 4, 4, 8, 4, 12};

int melody_3[] = {NOTE_C8, NOTE_CS2};
int note_durations_3[] = {4, 4};

int speed = 20;
int index = 0;
int length = 2;
int volume = 128;

void loop_song() {

  if (index >= length) {
    index = 0;
  }
  int noteDuration = speed * note_durations_3[index];
  if (noteDuration > 100) {
    index++;
    return;
  }
  tone(SOUND_PIN, melody_3[index], noteDuration * .95);
  delay(noteDuration);
  noTone(SOUND_PIN);
  index++;
}

void beep() {
//  tone(SOUND_PIN, NOTE_B5, 100);
//  delay(100);
//  noTone(SOUND_PIN);

  vol.tone(440, volume);
  delay(100);
  vol.tone(1, 0);

//  analogWrite(SOUND_PIN, volume);
//  delay(100);
//  analogWrite(SOUND_PIN, 255);

}

void setup() {
  pinMode(SOUND_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  beep();
  delay(5000);
}

// Sources
// https://maker.pro/arduino/projects/arduino-speaker
