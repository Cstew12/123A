/*
 * CSE 123A Group 8: Social Distancers
 * Author: Anthony White
 * Test: Individual Test: LED
 */

int red_led_pin = 3;
int green_led_pin = 5;
int blue_led_pin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);
  Serial.begin(9600);
}

bool led_distance_output(int distance) {
  if(distance > 6)
  {
    RGB_color(255, 0, 255);  //Green
  }
  if(distance <= 6 && distance >= 0) 
  {
    RGB_color(0, 255, 255);  //Red
  }
  if(distance <= 0)
  {
    RGB_color(255, 255, 0);  //Blue for Error
  }
}

void RGB_color(int red_led_value, int green_led_value, int blue_led_value)
{
  analogWrite(red_led_pin, red_led_value);
  analogWrite(green_led_pin, green_led_value);
  analogWrite(blue_led_pin, blue_led_value);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  int distance;
  for(distance = 20; distance--; distance >= -5)
  {
    Serial.print(distance);
    Serial.print("\n");
    led_distance_output(distance);
    delay(1000);
  }
}
