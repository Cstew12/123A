#include <SPI.h>
#include <SD.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pitches.h"
#include "Volume.h"

#define MAX_LEN 50
#define ANALOG A0
#define QUIET 255
#define SOUND_PIN 5

Volume vol(SOUND_PIN);

File myFile;

const int notes[] = {NOTE_A1, NOTE_B1, NOTE_C1, NOTE_D1, NOTE_E1, NOTE_F1, NOTE_G1};
const int sharps[] = {NOTE_AS1, NOTE_CS1, NOTE_DS1, NOTE_FS1, NOTE_GS1};

int volume = 32;
int val = 0;

int Speed = 0;
int melody[MAX_LEN];
int durations[MAX_LEN];
int length = 0;
int index = 0;

int convertArrToInt(int arr[], int len) {
  int num = 0;
  for (int i = 0; i < len; i++) {
    num += (arr[i] * pow(10, len - i - 1));
  }
  return num;
}

int asciiToInt(int in) {
  int num = -1;
  if (in >= 48 && in <= 57) {
    num = in - 48;
  }
  return num;
}

int convertNote(int arr[], int len) {
  int note;
  int note_pos = arr[0];
  int octave = arr[len - 1];
  if (len > 2) {  // we pull from sharps
    if (note_pos > 66) {
      note = sharps[note_pos - 66];
    } else if (note_pos > 69) {
      note = sharps[note_pos - 69];
    } else {
      note = sharps[note_pos - 65];
    }
  } else {
    note = notes[note_pos - 65];
  }
  float mult = pow(2, octave - 1);
  int mul = (int) mult + 1;   // for whatever reason, converting from float to int decreases the value by one.
  note *= mul;
  return note;
}


void loop_song(int melody[], int durations[], int speed, int length) {
  if (index >= length) {
    index = 0;
  }
  int noteDuration = speed * durations[index];
//  if (noteDuration > 500) {
//    index++;
//    return;
//  }

  vol.tone(melody[index], volume);
  vol.delay(noteDuration);
//  vol.noTone();
  vol.tone(1, 0);
  
//  tone(SOUND_PIN, melody[index], noteDuration * 0.95);
//  delay(noteDuration);
//  noTone(SOUND_PIN);
  index++;
}

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(SOUND_PIN, OUTPUT);
  vol.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  // open the file for reading:
  myFile = SD.open("lick.txt");
  if (myFile) {
    Serial.println("Sample.txt:");

    char inputChar;
    int i = 0;        // index of smaller arrays (note_arr, dur_arr, speed_arr)
    int j;            // index of larger arrays (durations, melody)
    int speed_arr[3];
    int note_arr[4];
    int duration_arr[4];
    int note;
    int duration;

    // Loop to get speed of melody
    while (inputChar != '\n') {
      inputChar = myFile.read();
      if (inputChar >= 48 && inputChar <= 57) { // ASCII 48 = 0 decimal, ASCII 57 = 9 decimal
        speed_arr[i] = inputChar - 48;
        i++;
      } 
    }

    // Converts array to number
    Speed = convertArrToInt(speed_arr, i);
    
    i = 0;
    j = 0;
    while (1) {
      inputChar = myFile.read();
      if (inputChar >= '0' && inputChar <= '9') { // if it's a decimal
        note_arr[i] = inputChar - 48;  // ascii 0 is 48 in decimal
        i++;
      } else if ((inputChar >= 'A' && inputChar <= 'G') || inputChar == 'S') {  // if char
        note_arr[i] = inputChar;
        i++;
      } else if (inputChar == ',' || inputChar == '\n') {  // if we are at the end of a note
        note = convertNote(note_arr, i);
        i = 0;
        melody[j] = note;
        length++;
        j++;
      } 

      if (inputChar == '\n') {
        break;
      }
    }


    // Adds durations into an array
    i = 0;
    j = 0;
    while (myFile.available()) {
      inputChar = myFile.read();
      if (inputChar >= '0' && inputChar <= '9') {
        duration_arr[i] = inputChar - 48;
        i++;
      } else if (inputChar == ',' || inputChar == '\n') {
        duration = convertArrToInt(duration_arr, i);
        i = 0;
        durations[j] = duration;
        j++;
      } 
    }

    Serial.println(Speed);
    for (int k = 0; k < length; k++) {
      Serial.print(melody[k]);
      Serial.print(": ");
      Serial.println(durations[k]);
    }

    loop_song(melody, durations, Speed, length);
    
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Sample.txt");
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}


void loop() {
  // none
}
