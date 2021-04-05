// Created by Bodmer 5/11/19

#include <math.h>

//#include "pngle.h"

#define LINE_BUF_SIZE 240  // pixel = 524, 16 = 406, 32 = 386, 64 = 375, 128 = 368, 240 = 367, no draw = 324 (51ms v 200ms)
uint16_t lbuf[LINE_BUF_SIZE];
int16_t sx = 0;
int16_t sy = 0;
uint32_t pc = 0;

int16_t png_dx = 0, png_dy = 0;

// Define corner position
void setPngPosition(int16_t x, int16_t y)
{
  png_dx = x;
  png_dy = y;
}

// Draw pixel - called by pngle
void pngle_on_draw(uint32_t x, uint32_t y, uint8_t rgba[4])
{
  if (rgba[3] > 127) { // Transparency threshold (no blending yet...)
    uint32_t color = ((rgba[0] >> 3) << 11) | ((rgba[1] >> 2) << 5) | (rgba[2] >> 3);

  #ifdef USE_LINE_BUFFER
    color = color << 8 | color >> 8;
    if ( (x == sx + pc) && (y == sy) && (pc < LINE_BUF_SIZE) ) lbuf[pc++] = color;
    else {
      // Push pixels to sprite
      spr.pushImage(png_dx + sx, png_dy + sy, pc, 1, lbuf);
      sx = x; sy = y; pc = 0;
      lbuf[pc++] = color;
    }
  #else
    spr.drawPixel(png_dx + (int32_t)x, png_dy + (int32_t)y, color);
  #endif
  }
}

// Render from FLASH array
void load_file(const uint8_t* arrayData, uint32_t arraySize)
{
  sx = png_dx;
  sy = png_dy;
  pc = 0;

  pngle_t *pngle = pngle_new();
  pngle_set_draw_callback(pngle, pngle_on_draw);

  // Feed data to pngle
  uint8_t buf[1024];

  uint32_t remain = 0;
  uint32_t arrayIndex = 0;
  uint32_t avail  = arraySize;
  uint32_t take = 0;
  
  //tft.startWrite(); // Crashes Adafruit_GFX, no advantage for TFT_eSPI with line buffer
  while ( avail > 0 ) {
    take = sizeof(buf) - remain;
    if (take > avail) take = avail;
    memcpy_P(buf + remain, (const uint8_t *)(arrayData + arrayIndex), take);
    arrayIndex += take;
    remain += take;
    avail -= take;
    int fed = pngle_feed(pngle, buf, remain);
    if (fed < 0) {
      //Serial.printf("ERROR: %s\n", pngle_error(pngle));
      break;
    }
    remain = remain - fed;
    if (remain > 0) memmove(buf, buf + fed, remain);
  }
#ifdef USE_LINE_BUFFER

  // Push any remaining pixels - because we had no warning that image has ended...
  if (pc) {spr.pushImage(png_dx + sx, png_dy + sy, pc, 1, lbuf); pc = 0;}

#endif
  //tft.endWrite();

  pngle_destroy(pngle);
}
