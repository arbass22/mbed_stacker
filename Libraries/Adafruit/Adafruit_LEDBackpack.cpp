/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/
  ----> http://www.adafruit.com/products/

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

 /*
 *  Modified by Luiz Hespanha (http://www.d3.do) 8/16/2013 for use in LPC1768
 *
 *  Modified by Andrew Bass 4/19/16 for use with 8x16 matrix.
 */

#include "mbed.h"
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

void Adafruit_LEDBackpack::setBrightness(uint8_t b) {
  if (b > 15) b = 15;
  uint8_t c = 0xE0 | b;
  char foo[1];
  foo[0] = c;
  _i2c->write(i2c_addr, foo, 1);
}

void Adafruit_LEDBackpack::blinkRate(uint8_t b) {
  if (b > 3) b = 0; // turn off if not sure
  uint8_t c = HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1);
  char foo[1];
  foo[0] = c;
  _i2c->write(i2c_addr, foo, 1);
}

Adafruit_LEDBackpack::Adafruit_LEDBackpack(I2C *i2c): _i2c(i2c) {
}

void Adafruit_LEDBackpack::begin(uint8_t _addr = 0x70) {
  i2c_addr = _addr << 1;

  char foo[1];
  foo[0] = 0x21;

  _i2c->write(i2c_addr, foo, 1);  // turn on oscillator

  blinkRate(HT16K33_BLINK_OFF);

  setBrightness(15); // max brightness
}

void Adafruit_LEDBackpack::writeDisplay(void) {
  char foo[17];
  foo[0] = 0x00;
  int j = 0;
  for (uint8_t i=1; i<=16; i+=2) {
    int x = displaybuffer[j] & 0xFF;
    foo[i] = x;
    int x2 = displaybuffer[j] >> 8;
    foo[i+1] = x2;
    j++;
  }
  _i2c->write(i2c_addr, foo, 17);
}

void Adafruit_LEDBackpack::clear(void) {
  for (uint8_t i=0; i<8; i++) {
    displaybuffer[i] = 0;
  }
}

Adafruit_8x8matrix::Adafruit_8x8matrix(I2C *i2c) : Adafruit_LEDBackpack(i2c), Adafruit_GFX(8, 8) {
}




void Adafruit_8x8matrix::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((y < 0) || (y >= 8)) return;
  if ((x < 0) || (x >= 8)) return;

 // check rotation, move pixel around if necessary
  switch (getRotation()) {
  case 1:
    swap(x, y);
    x = 8 - x - 1;
    break;
  case 2:
    x = 8 - x - 1;
    y = 8 - y - 1;
    break;
  case 3:
    swap(x, y);
    y = 8 - y - 1;
    break;
  }

  // wrap around the x
  x += 7;
  x %= 8;


  if (color) {
    displaybuffer[y] |= 1 << x;
  } else {
    displaybuffer[y] &= ~(1 << x);
  }
}

Adafruit_8x16matrix::Adafruit_8x16matrix(I2C *i2c) : Adafruit_LEDBackpack(i2c), Adafruit_GFX(8, 16) {
}

void Adafruit_8x16matrix::drawPixel(int16_t x, int16_t y, uint16_t color) {

 // check rotation, move pixel around if necessary
  switch (getRotation()) {
  case 2:
    swap(x, y);
    x = 16 - x - 1;
    break;
  case 3:
    swap(x,y);
    x = 16 - x - 1;
    y = 8 - y - 1;
    break;
  case 0:
    swap(x, y);
    y = 8 - y - 1;
    break;
  }

  if ((y < 0) || (y >= 8)) return;
  if ((x < 0) || (x >= 16)) return;

  if (color) {
    displaybuffer[y] |= 1 << x;
  } else {
    displaybuffer[y] &= ~(1 << x);
  }
}
