/*
  Frame.cpp - Library to handle a frame with the following structure:
  [Start('S'), option, id, address, value, Stop('E')]
*/

#include "Arduino.h"
#include "Frame.h"

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

void Frame::parseFrame() {
  if (frame().charAt(frame().length() - 1) == kStop) {
    set_option(frame_[1]);
    set_id(frame_[2]);
    set_address(frame_[3]);
    set_value(frame_[4]);
  }
}