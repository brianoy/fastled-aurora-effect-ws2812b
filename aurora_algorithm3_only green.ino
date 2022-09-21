#include <FastLED.h>

#define LED_PIN     22
#define COLOR_ORDER RGB
#define CHIPSET     WS2812B
#define NUM_LEDS    89

#define BRIGHTNESS  150
#define FRAMES_PER_SECOND 200
#define FRAME_SPEED 5
static uint8_t oldheat[NUM_LEDS];
static uint8_t newheat[NUM_LEDS];
CRGB leds[NUM_LEDS];

void setup() {
  delay(1000); // sanity delay
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither(0);
}

void loop()
{
  Fire2012(); // run simulation frame
  frame_blending();
}
#define COOLING  200
#define SPARKING 20


void Fire2012()
{
  /*for( int k= NUM_LEDS - 1; k >= 0; k--) {
    oldheat[k] = newheat[k];
  }*/
  // Step 1.  Cool down every cell a little
  /*for( int m= 0; m >NUM_LEDS; m++) {
    newheat[m] = oldheat[m];
  }*/

  if( random8() < COOLING ) {
    for( int i = 0; i < NUM_LEDS; i++) {
      oldheat[i] = qsub8( oldheat[i],  1);
    }
  }


    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    /*for( int k= NUM_LEDS - 1; k >= 0; k--) {
      heat[k] = (heat[k] + heat[k - 1] + heat[k + 1] + heat[k - 2] + heat[k + 2] ) / 5 +1;
      int m = NUM_LEDS - k;
      heat[m] = (heat[m] + heat[m - 1] + heat[m + 1] + heat[m - 2] + heat[m + 2] ) / 5 +1;
    }*/
    for( int k= NUM_LEDS - 1; k >= 0; k--) {
      newheat[k] = (oldheat[k] + oldheat[k - 1] + oldheat[k + 1] + oldheat[k - 2] + oldheat[k - 1] + oldheat[k - 3]) / 6 ;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(NUM_LEDS/2);
      if(oldheat[y]<=55){
        int x = random8(5,20);
        newheat[y] = qadd8( oldheat[y], x );
        for(int p = 1 ; p <= 7 ; p++){
          newheat[y+p]= qadd8( oldheat[y], x-3*p );
          newheat[y-p]= qadd8( oldheat[y], x-3*p );
        }
      }
    }

    // Step 4.  Map from heat cells to LED colors
    /*for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      leds[j] = color;
    }*/
}


void frame_blending(){
  for( int j = 0; j < 256; j = j + FRAME_SPEED) {
    for( int i = 0; i < NUM_LEDS; i++) {
      CRGB color = HeatColor((newheat[i]*j + oldheat[i]*(256-j) )/256);
      leds[i] = color;
    }
    //FastLED.show(); // display this frame
    FastLED.delay(1000/FRAMES_PER_SECOND);
  }
  for( int k= NUM_LEDS - 1; k >= 0; k--) {
    oldheat[k] = newheat[k];
  }
}
