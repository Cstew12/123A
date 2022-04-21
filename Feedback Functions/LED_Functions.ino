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

#define PIN 6 //Data Input

#define GREEN strip.Color(0, 255, 0) // Green color for LED ring
#define RED strip.Color(255, 0, 0) // Red color for LED ring

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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

/*
void setup() { 
  strip.begin(); 
  strip.setBrightness(50); //(0 to 255) (0 = dim) (255 = brightest)
  strip.show(); // Initialize all pixels to 'on'
}
*/

//initialization for LED ring
void initialize_LED() {
  strip.begin();
  strip.setBrightness(50); //(0 to 255) (0 = dim) (255 = brightest)
  strip.show(); //initialize all pixels to "on"
}


//displays green when at a safe distance (>= 6ft)
//displays red if not at a safe distance (< 6ft)
//safe is a global variable boolean
void triggerLed() {
  if(safe) { //more than 6 feet 
    solidColor(GREEN, 2000); 
  } else { //less than 6 feet 
    solidColor(RED, 2000);
  }
}

//turns off all pixels on the LED Ring
void ledOFF() {
  strip.clear();
}

//turns on all pixels on the LED Ring
void ledON() {
  strip.show();
}

//displays a solid color c for time wait (ms)
void solidColor(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
  }
  delay(wait);
}

//displays every other light in a moving circle
//c = solid color displayed
//wait = speed of light movement (50 works well)
void flashCircle(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
