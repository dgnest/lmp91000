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

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  if (processed_frame) {
    frame.set_frame(input_frame);
    Serial.print(frame.frame());

    frame.parseFrame();
    sensor.set_id(frame.id());
    sensor.set_pin_menb(13);

    switch (frame.option()) {
      case 'w':
        sensor.set_current_register(frame.address(), frame.value());
        sensor.writeRegister();
        Serial.print('w');
        break;
      case 'r':
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