#include <Wire.h>

#include "Frame.h"
#include "lmp91000.h"

String input_frame;
boolean processed_frame = false;

char frame_byte;
int frame_counter = 0;

// The frame has the following structure.
// [Start('S'), option, id, address, value, Stop('\n')]
Frame frame;
GasSensor sensor;

GasSensor sensor0(0, 10);
GasSensor sensor1(1, 11);
GasSensor sensor2(2, 12);
GasSensor sensor3(3, 13);


void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // Enters if the whole frame arrives.
  if (processed_frame) {
    frame.set_frame(input_frame);
    Serial.print(frame.frame());

    frame.parseFrame();

    // Maps sensor.
    switch (frame.id()) {
      case 0:
        sensor = sensor1;
        break;
      case 1:
        sensor = sensor1;
        break;
      case 2:
        sensor = sensor2;
        break;
      case 3:
        sensor = sensor3;
        break;
    }

    switch (frame.option()) {
      case 'w':
        sensor.writeRegister(frame.address(), frame.value());
        Serial.print('w');
        break;
      case 'r':
        Serial.print(sensor.readRegister(frame.address()), HEX);
        Serial.print('r');
        break;
      case 'a':
        Serial.print('a');
        break;
    }

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