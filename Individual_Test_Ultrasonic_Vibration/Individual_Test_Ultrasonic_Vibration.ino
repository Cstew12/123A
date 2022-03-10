int echo = 6;
int trig = 7;

int mvm = 10; // microvibration motor is connected with pin number 5 witch is the pwm pin
int vresistor = A1; // potentiometer data pin is A1
int data = 255; // resistance initially starts at 0

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(mvm, OUTPUT); //vibration motor
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;

  // Write
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);

  // Get duration in inches and centimeters
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  // Vibrate
  if (inches <= 6) {
    data = 255;
  } else {
    data = 0;
  }
  analogWrite(mvm, data); //send data from potentiometer to power pin of vibration motor
  
  // print
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(1000);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// Sources
// https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm#:~:text=Advertisements,or%201%E2%80%9D%20to%2013%20feet.
// Pretty much the same exact code
