/*
  lmp91000.cpp - Library to handle the lmp91000 sensor's registers.
*/

#include <Wire.h>

#include "Arduino.h"
#include "lmp91000.h"

// Register class.

byte Register::address() {
  return address_;
}

byte Register::value() {
  return value_;
}

void Register::set_address(byte address) {
  address_ = address;
}

void Register::set_value(byte value) {
  value = value_;
}


// GasSensor Class.

// Gets the sensor id.
int GasSensor::id() {
  return id_;
}

// Gets the MENB status an its pin.
boolean GasSensor::menb() {
  return menb_;
}

int GasSensor::pin_menb() {
  return pin_menb_;
}

// Gets the registers.
Register GasSensor::current_register() {
  return current_register_;
}


// Sets the sensor id.
void GasSensor::set_id(int id) {
  id_ = id;
}

// Sets the MENB status an its pin.
void GasSensor::set_menb(boolean input) {
  menb_ = input;
}

void GasSensor::set_pin_menb(int pin) {
  pin_menb_ = pin;
}

// Sets status register.
void GasSensor::set_current_register(Register reg) {
  current_register_ = reg;
}

void GasSensor::set_current_register(byte address, byte value) {
  current_register_.set_address(address);
  current_register_.set_value(value);
}

// I2C write method.
void GasSensor::writeRegister() {
  digitalWrite(pin_menb(), HIGH);
  Wire.beginTransmission(kSensorAddress);
  Wire.write(current_register().address());
  Wire.write(current_register().address());
  Wire.endTransmission();
  digitalWrite(pin_menb(), LOW);
}