// ESP32 only sketch (uses > 40kbytes RAM)

// Loads a PNG image from the internet with a specified URL,
// also loads a file from SPIFFS.

// Use IDE to upload files to SPIFFS!

//#define USE_ADAFRUIT_GFX // Comment out to use TFT_eSPI

#define USE_LINE_BUFFER  // Enable for faster rendering

#define WIFI_SSID "Your_SSID"
#define WIFI_PASS "Your_password"


#if defined(USE_ADAFRUIT_GFX)
  #define TFT_CS  5
  #define TFT_DC  26
  #define TFT_RST 27
  #include <Adafruit_ILI9341.h>
  Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
#else
  #include <TFT_eSPI.h>              // Hardware-specific library
  TFT_eSPI tft = TFT_eSPI();         // Invoke custom library
#endif

// Include SPIFFS
#define FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h" // Required for ESP32 only

#include <HTTPClient.h>

#include "support_functions.h"


void setup()
{
  Serial.begin(115200);
  tft.begin();

  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n WiFi connected.\n");
}


void loop()
{
  tft.fillScreen(0);
  uint32_t t = millis();

  setPngPosition(0, 0);
  //load_png("https://raw.githubusercontent.com/kikuchan/pngle/master/tests/pngsuite/PngSuite.png"); // Colour bar test image
  load_png("https://i.imgur.com/gOkm2as.png"); // M81

  t = millis() - t;
  Serial.print(t); Serial.println(" ms to load URL");

  //setPngPosition(20, 20);
  //load_file(SPIFFS, "/test.png"); // Test png with transparent mask
  
  delay(2000);
  t = millis();

  setPngPosition(0, 0);
  load_file(SPIFFS, "/panda2.png");
  //load_file(SPIFFS, "/PngSuite.png");
  //load_file(SPIFFS, "/M81.png");


  t = millis() - t;
  Serial.print(t); Serial.println(" ms to load SPIFFS");
  delay(2000);
}
