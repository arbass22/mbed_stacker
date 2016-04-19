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
 *  Modified by Andrew Bass 4/19/2016 for use with 8x16 matrix
 */


#include "mbed.h"
#include "Adafruit_GFX.h"

#define LED_ON 1
#define LED_OFF 0

#define LED_RED 1
#define LED_YELLOW 2
#define LED_GREEN 3



#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0x0E

// this is the raw HT16K33 controller
class Adafruit_LEDBackpack {
 public:
  Adafruit_LEDBackpack(I2C *i2c);
  void begin(uint8_t _addr);
  void setBrightness(uint8_t b);
  void blinkRate(uint8_t b);
  void writeDisplay(void);
  void clear(void);

  uint16_t displaybuffer[8];

  void init(uint8_t a);

  protected:
    I2C *_i2c;

 private:
  uint8_t i2c_addr;
};

class Adafruit_8x8matrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
 public:
  Adafruit_8x8matrix(I2C *i2c);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
};

class Adafruit_8x16matrix : public Adafruit_LEDBackpack, public Adafruit_GFX {
 public:
  Adafruit_8x16matrix(I2C *i2c);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

 private:
};
