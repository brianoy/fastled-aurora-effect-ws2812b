#include <FastLED.h>

#define NUM_LEDS  88
#define LED_PIN   22

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(aurora_gp) {
   0,     0,   10,    0,  //black
   89,    20,  232,  30, //dark green
   135,   0,   234,  141,//bright green
   175,   1,   126,  213,//blue
   225,   181, 61,   255,//purple
   255,   141, 1,    196 //dark purple
   };

CRGBPalette16 greenblue = aurora_gp;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(250);

  //Fill the colorIndex array with random numbers
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}

void loop() {

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
  uint8_t sinBeat = beatsin8(5, 150, 240, 0, 0);
  
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(greenblue, colorIndex[i], sinBeat);
  }
  
  EVERY_N_MILLISECONDS(5){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.show();
}
