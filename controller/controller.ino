#include "Frame.h"

const byte kSensorAddress = B1001000;

String input_frame;
boolean processed_frame = false;

char frame_byte;
int frame_counter = 0;

// The frame has the following structure.
// [Start('S'), option, id, address, value, Stop('\n')]
Frame frame;


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (processed_frame) {
    frame.set_frame(input_frame);
    Serial.print(frame.frame());

    frame.ParseFrame();
    // Serial.print(frame.value());
    // Serial.print(frame.address());
    // Serial.print(frame.id());
    // Serial.print(frame.option());

    input_frame = "";
    processed_frame = false;
  }
}

void serialEvent() {
  while (Serial.available() > 0) {
    frame_byte = (char)Serial.read();
    if (frame_byte == Frame::kStartFrame || frame_counter > 0) {
      frame_counter++;
      input_frame += frame_byte;
      if (frame_counter == Frame::kFrameLength) {
        processed_frame = true;
        frame_counter = 0;
      }
    }
  }
}