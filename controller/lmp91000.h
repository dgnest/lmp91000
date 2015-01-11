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
  // Gets the sensor id.
  int id();
  // Gets the MENB status an its pin.
  boolean menb();
  int pin_menb();
  // Gets the registers.
  Register status();
  Register lock();
  Register reserved();
  Register tiacn();
  Register refcn();
  Register modecn();
  // Sets the sensor id.
  void set_id(int id);
  // Sets the MENB status an its pin.
  void set_menb(boolean input);
  void set_pin_menb(int pin);

  // Sets registers.
  // Status
  void set_status(Register state);
  void set_status(byte address, byte value);
  // Lock.
  void set_lock(Register lock);
  void set_lock(byte address, byte value);
  // Reserved
  void set_reserved(Register reserved);
  void set_reserved(byte address, byte value);
  // Tiacn.
  void set_tiacn(Register tiacn);
  void set_tiacn(byte address, byte value);
  // Refcn
  void set_refcn(Register refcn);
  void set_refcn(byte address, byte value);
  // Modecn.
  void set_modecn(Register modecn);
  void set_modecn(byte address, byte value);

  // I2C write method.
  static void writeRegister(byte address, byte value);
  static void writeRegister(Register reg);

  static const byte kSensorAddress = B1001000;

 private:
  // Sensor id.
  int id_;
  // MENB.
  boolean menb_;
  int pin_menb_;
  // Registers.
  Register status_;
  Register lock_;
  Register reserved_;
  Register tiacn_;
  Register refcn_;
  Register modecn_;
};

#endif lmp91000_h