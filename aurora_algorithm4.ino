#include <FastLED.h>

#define NUM_LEDS  88
#define LED_PIN   22

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( greenblue_gp ) { 
  0,   0,  255, 245,
  150,  0,  80,  255,
  200, 12, 250, 10,
  255, 0,  255, 245
};

CRGBPalette16 greenblue = greenblue_gp;
int x = random8();
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  //Fill the colorIndex array with random numbers
  
  uint8_t wave1;
  for (int i = 0; i < NUM_LEDS; i++) {
    wave1 = (sin8((x+10*i)%256)+sin8(2*((x+10*i)%256)))/2;
    colorIndex[i] = wave1;
    Serial.println(wave1);
  }
}

void loop() {

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
  uint8_t sinBeat = beatsin8(2, 160, 240, 0, 0);
  
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
