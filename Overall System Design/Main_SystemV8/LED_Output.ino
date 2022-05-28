/*
 * CSE 123A Group 8: Social Distancers
 * Author: Terrence Ng
 * Description: Functions For the LED ring on the soial distance detectin device
 * Date: 4/14/2022
 */
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


/* Only PWR +5V, GND, and Data Inut pins are used (no resistors used)
 * PWR to 5V pin
 * GND to GND
 * Data Input to PIN # specified in "#define PIN _"
 */

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


void initialize_LED() {
  //Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, LED_PIN, NEO_GRB + NEO_KHZ800);
  pinMode(SINGLE_LED_PIN, OUTPUT);
  strip.begin();
  strip.setBrightness(50); //(0 to 255) (0 = dim) (255 = brightest)
  strip.show(); //initialize all pixels to "on"
}


void LED_Output_blink(){
  //blinks LED based on previous state and current time
  //Delay() cant be used becuase multitasking needs to happen
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval){
    previousMillis = currentMillis;
    if(ledState == LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    digitalWrite(SINGLE_LED_PIN, ledState);
  }
  
}


void LED_Output_continuous(uint32_t c){
  //Continuously sets LED Output to On
  //Serial.println("continuous\n");
  digitalWrite(SINGLE_LED_PIN, HIGH);
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    //uint16_t i=0;
    //Serial.println(strip.numPixels());
    strip.setPixelColor(i, c);
    strip.show();
  }
}

void LED_Output_killLED(){
  //kills the LED Output
  digitalWrite(SINGLE_LED_PIN, LOW);
    strip.clear();
    strip.show();
}
