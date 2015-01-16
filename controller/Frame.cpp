/*
  Frame.cpp - Library to handle a frame with the following structure:
  [Start('S'), option, id, address, value, Stop('E')]
*/

#include "Arduino.h"
#include "Frame.h"
#include <StandardCplusplus.h>
#include <vector>

using namespace std;

vector<byte> Frame::frame() {
  return frame_;
}

byte Frame::option() {
  return option_;
}

byte Frame::id() {
  return id_;
}

byte Frame::address() {
  return address_;
}

byte Frame::value() {
  return value_;
}

void Frame::set_frame(vector<byte> frame) {
  frame_ = frame;
}

void Frame::set_option(byte option) {
  option_ = option;
}

void Frame::set_id(byte id) {
  id_ = id;
}

void Frame::set_address(byte address) {
  address_ = address;
}

void Frame::set_value(byte value) {
  value_ = value;
}

void Frame::parseFrame() {
  if (frame().at(frame().size() - 1) == kStop) {
    set_option(frame_[1]);
    set_id(frame_[2]);
    set_address(frame_[3]);
    set_value(frame_[4]);
  }
}