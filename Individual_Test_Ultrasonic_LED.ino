int echo = 6;
int trig = 7;

int red_led_pin = 3;
int green_led_pin = 5;
int blue_led_pin = 4;

void setup() {

  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void RGB_color(int red, int green, int blue) {
  analogWrite(red_led_pin, red);
  analogWrite(green_led_pin, green);
  analogWrite(blue_led_pin, blue);
}

void led_distance(long distance) {
  if (distance >= 72) {
    RGB_color(255, 0, 255);
  } else if (distance < 72) {
    RGB_color(0, 255, 255);
  }
}

void loop() {
  long duration, inches, cm;

  // write code
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // get duration
  duration = pulseIn(echo, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  led_distance(inches);
  
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



// sources
// ultrasonic code: https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm#:~:text=Advertisements,or%201%E2%80%9D%20to%2013%20feet.
// Anthonys LED test
