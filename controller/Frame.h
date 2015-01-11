/*
  Frame.h - Library to handle a frame with the following structure:
  [Start('S'), option, id, address, value, Stop('E')]
*/

#ifndef Frame_h
#define Frame_h

#include "Arduino.h"

class Frame {
 public:
  String frame();
  char option();
  char id();
  char address();
  char value();
  void set_frame(String frame);
  void set_option(char option);
  void set_id(char id);
  void set_address(char address);
  void set_value(char value);

  void parseFrame();

  static const int kFrameLength = 6;
  static const char kStartFrame = 'S';
  static const char kStop = 'E';


 private:
  String frame_;

  char option_;
  char id_;
  char address_;
  char value_;
};

#endif Frame_h