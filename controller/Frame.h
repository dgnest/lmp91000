/*
  Frame.h - Library to handle a frame with the following structure:
  [Start('S'), option, id, address, value, Stop('E')]
*/

#ifndef Frame_h
#define Frame_h

#include "Arduino.h"
#include <StandardCplusplus.h>
#include <vector>

using namespace std;

class Frame {
 public:
  vector<byte> frame();
  byte option();
  byte id();
  byte address();
  byte value();
  void set_frame(vector<byte> frame);
  void set_option(byte option);
  void set_id(byte id);
  void set_address(byte address);
  void set_value(byte value);

  void parseFrame();

  static const int kFrameLength = 6;
  static const byte kStartFrame = 'S';
  static const byte kStop = 'E';


 private:
  vector<byte> frame_;

  byte option_;
  byte id_;
  byte address_;
  byte value_;
};

#endif Frame_h