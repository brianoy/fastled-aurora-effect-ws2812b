#include <FastLED.h>

#define NUM_LEDS  88
#define LED_PIN   22
CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(aurora_gp) {
   0,     0,   100,    0,  //black green
   89,    20,  232,  30, //dark green
   135,   0,   234,  141,//bright green
   175,   1,   126,  213,//blue
   225,   181, 61,   255,//purple
   255,   141, 1,    196 //dark purple
   };

CRGBPalette16 aurora = aurora_gp;

void setup() {
  delay(200);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(115200);
}



void loop() {
  
  /*for (int i = NUM_LEDS-1; i = 1; i--) {
    leds[i] = leds[i-1]
  }*/
  uint8_t wavesize = random8(10,45);//選擇一次波的長度
  uint8_t color = random8(0,255);//選擇該次波的顏色
  //Serial.println(wavesize);
  //Serial.println(color);
  for (int i = 0; i < wavesize; i++) {
    for (int j = NUM_LEDS-1; j >= -1 ; j--) {//先將所有的像素往後移一格
      leds[j] = leds[j-1];
    }
    leds[0] = ColorFromPalette(aurora, color+0.3*i, 55+(200/wavesize*i));
    //Serial.println(leds[0]);
    FastLED.delay(20);
  }
  for (int k = 0; k < wavesize; k++) {
    for (int l = NUM_LEDS-1; l >= -1; l--) {//先將所有的像素往後移一格
      leds[l] = leds[l-1];
    }
    leds[0] = ColorFromPalette(aurora, color-0.3*k, 255-(200/wavesize*k));
    FastLED.delay(20);
  }
}
