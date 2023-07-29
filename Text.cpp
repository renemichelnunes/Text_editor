#include <sys/_stdint.h>
#include "Arduino.h"
#include "Text.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

Text::Text(TFT_eSPI *display, uint8_t nlines, uint8_t char_per_lines, uint8_t x, uint8_t y, uint8_t font_size){
  this->nlines = nlines;
  this->char_per_lines = char_per_lines;
  this->x = x;
  this->y = y;
  this->font_size = font_size;
  this->disp = display;

  this->drawRect();
}

Text::Text(){

}

void Text::drawRect(){
  this->disp->drawRect(this->x - 5, this->y - 5, this->char_per_lines * 6 + 10, abs((this->nlines - 2)) * 12 + 5, TFT_WHITE);
}

void Text::add(String text){
  this->text = text;
  this->refresh();
}

void Text::append(String text){
  this->text += text;
  this->refresh();
}

char Text::pop(){
  char c = this->text[this->text.length() - 1];
  this->text[this->text.length() - 1] = ' ';
  this->refresh();
  this->text.remove(this->text.length() - 1);
  return c;
}

void Text::refresh(){
  uint32_t index = 0;
  uint8_t line = this->y;
  String text = this->text;
  String s, s2;
  uint32_t enter = 0;

  while (index < this->text.length()) {
    s = text.substring(index, index + this->char_per_lines);
    enter = s.indexOf('\n');
    if(enter != -1){
      s = text.substring(index, index + enter);
      this->disp->drawString(s, this->x, line);
      //Serial.println(s);
      index += enter + 1;
      enter = 0;
    }
    else{
      this->disp->drawString(s, this->x, line);
      //Serial.println(s);
      index += this->char_per_lines;
    }
    line += 10;
  }
}

void Text::clear(){
  this->text = "";
  this->disp->fillRect(this->x - 4, this->y - 4, this->char_per_lines * 6 + 4, abs((this->nlines - 2)) * 12 + 2, TFT_BLACK);
}
