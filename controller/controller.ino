#include <Wire.h>


const byte SENSOR_ADDRESS = B1001000;

String input_frame;
boolean processed_frame = false;

char frame_byte;
int frame_counter = 0;

// The frame has the following structure.
char option;
char id;
char address;
char value;


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
    if (frame_byte == 'S' || frame_counter > 0) {
      frame_counter++;
      input_frame += frame_byte;
      if (frame_counter == 6) {
        processed_frame = true;
        frame_counter = 0;
      }
    }
  }
}

void parseString(String s) {
  if (s[5] == '\n') {
    option = s[1];
    id = s[2];
    address = s[3];
    value = s[4];
  }
}