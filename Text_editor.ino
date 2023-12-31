/*
 This sketch uses the GLCD and font 2 only.

 Make sure all the required fonts are loaded by editing the
 User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######            TO SELECT THE FONTS YOU USE, SEE ABOVE           ######
  #########################################################################
 */
 
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "Text.h"
 
TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height
Text t;

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
    tft.setTextColor(TFT_BLACK, color);
    tft.drawChar(' ', x, y);
  }
}

TFT_eSprite needle = TFT_eSprite(&tft);
TFT_eSprite back = TFT_eSprite(&tft);

void setup()
{
  randomSeed(analogRead(0));
// Setup the LCD
  tft.init();
  tft.setBacklightPin(D4);
  tft.setBacklight(10);
  tft.setRotation(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);

  t = Text(&tft, 20, 70, 10, 30, 0); // Text box
  //t.append("A class is like a template that lets you reuse code without having to type it over and over. \nFor example, say you needed to make 20 documents that all had the same font, header, and margins. \nIt would be too time consuming to change the formatting of all 20 documents individually. \nInstead you could make a template document with the right font, header, and margins, then add the text and save it as a separate file.");

  //randChar();
  tft.setPivot(200, 200);
  needle.createSprite(15, 5);
  back.createSprite(20, 20);
  Serial.begin(9600);
}

void teste(){
  for(int i = 0; i < 20; i++)
    t.append(String(i) + '\n');
}

void serialKeyboard(){
  String s = "";
  if(Serial.available()){
    char c = Serial.read();
    //Serial.println(int(c));
    if(int(c) == 127)
      t.pop();
    else if(int(c) == 13)
      s = '\n';
    else if(int(c) == 96){
      t.clear();
      teste();
    }
    else
      s = String(c);
    t.append(s);
  }
}

uint16_t angle = 0;
void loop()
{
  
  serialKeyboard();
  back.fillSprite(TFT_BLACK);
  needle.fillSprite(TFT_ORANGE);
  needle.pushRotated(&back, angle);
  back.pushSprite(400, 0);
  angle++;
  if(angle == 360)
    angle = 0;
  delay(5);
}
