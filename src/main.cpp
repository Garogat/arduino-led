#include <FastLED.h>            // FastLED
#include "config.h"

// macros for debugging
#ifdef DEBUG
  #define         DEBUG_PRINT(x)    Serial.print(x)
  #define         DEBUG_PRINTLN(x)  Serial.println(x)
#else
  #define         DEBUG_PRINT(x)
  #define         DEBUG_PRINTLN(x)
#endif

enum CMD {
  CMD_NOT_DEFINED,
};
volatile uint8_t cmd = CMD_NOT_DEFINED;

CRGB leds[MATRIX_NUM_LEDS];

///////////////////////////////////////////////////////////////////////////
//   Setup() and loop()
///////////////////////////////////////////////////////////////////////////
void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  DEBUG_PRINTLN(F(""));
  DEBUG_PRINTLN(F(""));
  DEBUG_PRINTLN(F("Info: booted"));

  // init the I/O
  FastLED.addLeds<WS2812B, PIN_MATRIX, GRB>(leds, MATRIX_NUM_LEDS);
  fill_solid(leds, MATRIX_NUM_LEDS, CRGB::Black);
  FastLED.show();
}


void loop() {
  if (Serial.available() > 0) {
    if (length == 15) {
      int id;
      int r, g, b;
      sscanf(payload, "%d:%d:%d:%d", &id, &r, &g, &b);
      leds[id].r = r;
      leds[id].g = g;
      leds[id].b = b;
      FastLED.show();
    }
  }
}
