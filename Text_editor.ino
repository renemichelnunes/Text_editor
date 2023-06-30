// Demo based on:
// UTFT_Demo by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
/*

 The delay between tests is set to 0. The tests run so fast you will need to
 change the WAIT value below to see what is being plotted!
 
 This sketch uses the GLCD and font 2 only.

 Make sure all the required fonts are loaded by editing the
 User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######            TO SELECT THE FONTS YOU USE, SEE ABOVE           ######
  #########################################################################
 */

// Delay between demo pages
#define WAIT 0 // Delay between tests, set to 0 to demo speed, 2000 to see what it does!

#define CENTRE 240

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height

class Text{
  // Char is 10x8 on size 2
  uint8_t font_size = 2;
  String text = "1234567890";
  uint8_t lines = 1;
  uint8_t char_per_lines = 10; 
  uint8_t x = 0;
  uint8_t y = 0;
};

void randChar(){
  uint16_t x = 0, y = 0, color = 0;
  uint8_t a = 0;
  // this causes a overflow and a infinite loop
  for(uint16_t i = 0; i < 65536; i++){
    x = random(480);
    y = random(320);
    a = random(128);
    color = random(65536);
    //tft.drawChar(' ', x, y, 2);
    tft.setTextColor(color);
    tft.drawChar(char(a), x, y, 2);
  }
}

void setup()
{
  randomSeed(analogRead(0));
  Serial.begin(38400);
// Setup the LCD
  tft.init();
  tft.setBacklightPin(D4);
  tft.setBacklight(10);
  tft.setRotation(1);
  tft.setTextColor(TFT_ORANGE);
  tft.fillScreen(TFT_BLACK);
  tft.drawString("ooooooooooooooooooooooooooooo oooooooooooooooooooooooooooooa", 0, 0, 2);
  tft.drawString("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO OOOOOOOOOOOOOOOOOOOOOA", 0, 12, 2);
  String a = "test";
  a += 'e';
  tft.drawString(a, 0, 24, 2);
  a.remove(a.length()-1);
  tft.drawString(a, 0, 36, 2);
  delay(2000);
  randChar();
}

void loop()
{
  
}
