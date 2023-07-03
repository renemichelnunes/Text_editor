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
  while (index < this->text.length()) {
    if(this->font_size > 0)
      this->disp->drawString(text.substring(index, index + this->char_per_lines), x, line, this->font_size);
    else
      this->disp->drawString(text.substring(index, index + this->char_per_lines), x, line);
    line += 10;
    index += this->char_per_lines;
  }
}