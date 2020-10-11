#include <FastLED.h>
#define LED_PIN 8
#define NUM_LEDS 16
uint8_t i = 0;
CRGB leds[NUM_LEDS];
void setup(){
  
    FastLED.addLeds<WS2811,LED_PIN,GRB>(leds,NUM_LEDS);
}
void loop(){
  delay(1000);
  leds[i] = CRGB(20,20,0);
  if (i > 0){
    leds[i-1] = CRGB(0);
  }
  FastLED.show();
  i = i > 17 ? 0 : i+1;
}
