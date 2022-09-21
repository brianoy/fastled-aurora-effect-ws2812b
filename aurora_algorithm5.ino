#include <FastLED.h>

#define NUM_LEDS  88
#define LED_PIN   22

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( greenblue_gp ) { 
  0,   20,  200, 80,
  30,  0,  255, 245,
  160, 12, 250, 10,
  255, 0,  80, 245
};

CRGBPalette16 greenblue = greenblue_gp;
int x = random8();
void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  Serial.println("starting..");
  Serial.println(x);
  //Fill the colorIndex array with random numbers
  
  uint8_t wave1;
  for (int i = 0; i < NUM_LEDS; i++) {
    wave1 = (sin8((x+4*i)%256));
    colorIndex[i] = wave1;
    Serial.println(wave1);
  }
}

void loop() {

  //Creat a sin wave with period of 2 seconds (30bpm) to change the brightness of the strip
 // uint8_t sinBeat = beatsin8(50, 160, 240, 0, 0);
  uint8_t sinBeat2 = beatsin8(2, 20, 100, 0, 0);
  uint8_t sinBeat3 = beatsin8(10, 0, 1, 0, 0);
  int x = random8();
  // Color each pixel from the palette using the index from colorIndex[]
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t sinBeat = beatsin8(2, 195, 240, 130*i, 0);
    leds[i] = ColorFromPalette(greenblue, colorIndex[i] + sinBeat2, sinBeat);
  }
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]=colorIndex[i]+1+sinBeat3;
    }
  FastLED.delay(5);
}
