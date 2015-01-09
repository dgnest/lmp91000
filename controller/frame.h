/*
  Frame.h - Library to handle the following structure:
  [Start('S'), option, id, address, value, Stop('\n')]
*/

#ifndef frame_h
#define frame_h

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

  void ParseFrame();

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


String Frame::frame() {
  return frame_;
}

char Frame::option() {
  return option_;
}

char Frame::id() {
  return id_;
}

char Frame::address() {
  return address_;
}

char Frame::value() {
  return value_;
}

void Frame::set_frame(String frame) {
  frame_ = frame;
}

void Frame::set_option(char option) {
  option_ = option;
}

void Frame::set_id(char id) {
  id_ = id;
}

void Frame::set_address(char address) {
  address_ = address;
}

void Frame::set_value(char value) {
  value_ = value;
}

void Frame::ParseFrame() {
  if (frame().charAt(frame().length() - 1) == kStop) {
    set_option(frame_[1]);
    set_id(frame_[2]);
    set_address(frame_[3]);
    set_value(frame_[4]);
  }
}

#endif frame_h