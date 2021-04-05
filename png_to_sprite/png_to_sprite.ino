// ESP32 & Raspberry Pi Pico sketch (uses > 40kbytes RAM)

// Created by Bodmer 5/11/19

//#define USE_LINE_BUFFER  // Very small gain for writing to sprite

#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

// Create a sprite instance
TFT_eSprite spr = TFT_eSprite(&tft);

#include "pngle.h"
#include "support_functions.h"

#include "array_M81_png.h"
#include "array_test_i_png.h"
#include "array_test_ni_png.h"
#include "array_test_png.h"
#include "array_PngSuite_png.h"
#include "array_panda_png.h"

uint16_t myColor(uint16_t x, uint16_t y)
{
  return TFT_RED;
}
void setup()
{
  Serial.begin(115200);
  tft.begin();
  //tft.initDMA();
  Serial.println("\n Ready to load image...\n");

  // Create a 100 x 100 sprite
  spr.createSprite(100,100);

  tft.setCallback(myColor);
}

void loop()
{
  tft.fillScreen(0);

  uint32_t t = millis();

  setPngPosition(0, -80); // Set position of top left corner of image relative to top left of sprite

  //load_file(M81_png, sizeof(M81_png));
  load_file(PngSuite_png, sizeof(PngSuite_png));
  //load_file(panda_png, sizeof(panda_png));
  //load_file(test_ni_png, sizeof(test_ni_png));
  //load_file(test_123_png, sizeof(test_123_png));
  //load_file(test_ni_png, sizeof(test_ni_png));   // From Photoshop 363 ms non-interlaced - interlaced >500ms!
  //load_file(test_png, sizeof(test_png));

  // Push sprite to screen
  spr.pushSprite(0,0);
  t = millis() - t;

  Serial.print(t); Serial.println(" ms to load array");
  delay(2000);

  //Serial.println(String(ESP.getFreeHeap()));
}
