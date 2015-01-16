#include <Wire.h>
#include <StandardCplusplus.h>
#include <vector>

#include "Frame.h"
#include "lmp91000.h"

using namespace std;


vector<byte> input_frame;
boolean processed_frame = false;

byte frame_byte;
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

    frame.parseFrame();

    Serial.print(frame.option());
    Serial.print("-");
    Serial.print(frame.id(), HEX);
    Serial.print("-");
    Serial.print(frame.address(), HEX);
    Serial.print("-");
    Serial.print(frame.value(), HEX);
    Serial.print(":");
    Serial.print(":");

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
        Serial.println('w');
        break;
      case 'r':
        Serial.print(sensor.readRegister(frame.address()), HEX);
        Serial.print("-");
        Serial.println('r');
        break;
      case 'a':
        Serial.println('a');
        break;
    }

    processed_frame = false;
  }
}

void serialEvent() {
  while (Serial.available() > 0) {
    frame_byte = (byte)Serial.read();
    if (frame_byte == Frame::kStartFrame || frame_counter > 0) {
      frame_counter++;
      input_frame.push_back(frame_byte);
      if (frame_counter == Frame::kFrameLength) {
        processed_frame = true;
        frame_counter = 0;
      }
    }
  }
}