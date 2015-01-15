/*
  lmp91000.h - Library to handle the lmp91000 sensor's registers.
*/

#ifndef lmp91000_h
#define lmp91000_h

#include <Wire.h>

#include "Arduino.h"

class Register {
 public:
  byte address();
  byte value();
  void set_address(byte address);
  void set_value(byte value);

 private:
  byte address_;
  byte value_;
};

class GasSensor {
 public:
  // Constructor.
  GasSensor();
  GasSensor(int id, int pin_menb);

  // Gets the sensor id.
  int id();
  // Gets the MENB status an its pin.
  boolean menb();
  int pin_menb();
  // Gets the registers.
  Register current_register();

  // Sets the sensor id.
  void set_id(int id);
  // Sets the MENB status an its pin.
  void set_menb(boolean input);
  void set_pin_menb(int pin);
  // Sets registers.
  void set_current_register(Register reg);
  void set_current_register(byte address, byte value);

  // I2C write method.
  void writeRegister(byte address, byte value);
  byte readRegister(byte address);

  static const byte kSensorAddress = B1001000;

 private:
  // Sensor id.
  int id_;
  // MENB.
  boolean menb_;
  int pin_menb_;
  // Register state.
  Register current_register_;
};

#endif lmp91000_h