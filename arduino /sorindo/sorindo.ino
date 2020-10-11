#include <FastLED.h>
#define LED_PIN 8
#define NUM_LEDS 16
uint8_t i = 0;
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS];
void setup(){
  
    FastLED.addLeds<WS2811,LED_PIN,GRB>(leds,NUM_LEDS);
}
void loop(){
  delay(100);
 leds1[0]  = CRGB(0,0,250);

 
  leds[0] =  leds1[0];

  FastLED.show();

}
