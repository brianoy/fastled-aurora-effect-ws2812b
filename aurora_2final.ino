#include <FastLED.h>

#define NUM_LEDS  88
#define LED_PIN   22
CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(aurora_gp) {
   0,     0,   100,    0,  //black green
   89,    20,  232,  30,   //dark green
   135,   0,   234,  141,  //bright green
   175,   1,   126,  213,  //blue
   225,   190, 61,   255,  //purple
   255,   141, 1,    196   //dark purple
   };

CRGBPalette16 aurora_object = aurora_gp;

void setup() {
  delay(200);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(240);
  Serial.begin(115200);
}

void loop() {
  aurora_colorpicker();
}


void aurora_colorpicker(){//讓藍色及紅色比較少出現 以及出現時會限制波的長度較短
  uint8_t color_picker = random8();//先選擇是5個顏色的哪一個顏色
  uint8_t color;//在範圍內選擇適當的中央色 
  uint8_t wavesize;//選擇一次波的長度 
  if      (0<color_picker and color_picker<130)   {wavesize = random8(10,45); color = random8(14,75);}    //black green  - dark green
  else if (130<color_picker and color_picker<170) {wavesize = random8(10,45); color = random8(103,121);}  //dark green   - bright green
  else if (170<color_picker and color_picker<200) {wavesize = random8(5,30);  color = random8(145,165);}  //bright green - blue
  else if (200<color_picker and color_picker<225) {wavesize = random8(5,20);  color = random8(181,219);}  //blue         - purple
  else                                            {wavesize = random8(5,20);  color = random8(231,249);}  //purple       - dark purple
  aurora(wavesize, color);
}


void aurora(uint8_t wavesize ,uint8_t color) {//發生器
  for (int i = 0; i < wavesize; i++) {
    for (int j = NUM_LEDS-1; j >= 1 ; j--) {//先將所有的像素往後移一格
      leds[j] = (leds[j-1] + leds[j-2])/2;
    }
    leds[1] = leds[0];
    leds[0] = ColorFromPalette(aurora_object, color+0.3*i, 55+(200/wavesize*i));
    //Serial.println(leds[0]);
    FastLED.delay(25);
  }
  for (int k = 0; k < wavesize; k++) {
    for (int l = NUM_LEDS-1; l >= 1; l--) {//先將所有的像素往後移一格
      leds[l] = (leds[l-1] + leds[l-2])/2;
    }
    leds[1] = leds[0];
    leds[0] = ColorFromPalette(aurora_object, color-0.3*k, 255-(200/wavesize*k));
    FastLED.delay(25);
  }
}
