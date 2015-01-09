#include <Wire.h>


const byte kSensorAddress = B1001000;

const int kFrameLength = 6;
String input_frame;
boolean processed_frame = false;


char frame_byte;
int frame_counter = 0;

// The frame has the following structure.
// [Start('S'), option, id, address, value, Stop('\n')]
const char kStartFrame = 'S';
const char kStop = 'E';

struct Frame {
  char option;
  char id;
  char address;
  char value;
};

Frame frame;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (processed_frame) {
    Serial.print(input_frame);
    parseString(input_frame);
    input_frame = "";
    processed_frame = false;
  }
}

void serialEvent() {

  while (Serial.available() > 0) {
    frame_byte = (char)Serial.read();
    if (frame_byte == kStartFrame || frame_counter > 0) {
      frame_counter++;
      input_frame += frame_byte;
      if (frame_counter == kFrameLength) {
        processed_frame = true;
        frame_counter = 0;
      }
    }
  }
}

void parseString(String s) {
  if (s[kFrameLength - 1] == kStop) {
    frame.option = s[1];
    frame.id = s[2];
    frame.address = s[3];
    frame.value = s[4];
  }
}