// ESP32 only sketch (uses > 40kbytes RAM)

// Created by Bodmer 5/11/19

#define USE_LINE_BUFFER  // Enable for faster rendering

#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library
  
#include "support_functions.h"

#include "array_M81_png.h"
#include "array_test_i_png.h"
#include "array_test_ni_png.h"
#include "array_test_png.h"
#include "array_PngSuite_png.h"
#include "array_panda_png.h"

void setup()
{
  Serial.begin(115200);
  tft.begin();
  Serial.println("\n Ready to load image...\n");
}

void loop()
{
  tft.fillScreen(0);
  uint32_t t = millis();

  setPngPosition(0, 0);
  //load_file(M81_png, sizeof(M81_png));
  load_file(PngSuite_png, sizeof(PngSuite_png));
  //load_file(panda_png, sizeof(panda_png));
  //load_file(test_ni_png, sizeof(test_ni_png));
  t = millis();
  load_file(test_123_png, sizeof(test_123_png)); // From IrfanView 186 ms
  //load_file(test_ni_png, sizeof(test_ni_png)); // From Photoshop 363 ms non-interlaced - interlaced >500ms!
  //load_file(test_png, sizeof(test_png));       // Original 186 ms
  t = millis() - t;
  delay(2000);
  Serial.print(t); Serial.println(" ms to load array");
  //delay(2000);
  //Serial.print(sizeof(panda)); Serial.println(" byte array");
  Serial.println(String(ESP.getFreeHeap()));
}
