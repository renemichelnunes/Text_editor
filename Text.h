#include <cstddef>
#ifndef Text_h
#define Text_h

#include "Arduino.h"
#include <TFT_eSPI.h>

class Text {
private:
  // Char is 10x8 on size 2
  uint8_t font_size = 2;
  uint8_t nlines = 1;
  uint8_t char_per_lines = 10;
  uint8_t x = 0;
  uint8_t y = 0;
  String text = "";
  TFT_eSPI* disp;

public:
  Text(TFT_eSPI *display, uint8_t nlines, uint8_t char_per_lines, uint8_t x, uint8_t y, uint8_t font_size);
  void add(String text);
  void append(String text);
  char pop();
  void refresh();
};

#endif