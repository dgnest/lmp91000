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

// Constructor.
GasSensor::GasSensor() {
  set_id(0);
  set_pin_menb(0);
}

GasSensor::GasSensor(int id, int pin_menb) {
  set_id(id);
  set_pin_menb(pin_menb);
}

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
void GasSensor::writeRegister(byte address, byte value) {
  // Change pin_menb to LOW to enable.
  digitalWrite(pin_menb(), LOW);

  // Status Register. Ready to accept I2C commands.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x01));
  Wire.endTransmission();

  // Lock Register. Unlock write mode.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x01));
  Wire.write(byte(0x00));
  Wire.endTransmission();

  // Write Register.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();

  // Change pin_menb to HIGH to disable.
  digitalWrite(pin_menb(), HIGH);
}

// I2C read method.
byte GasSensor::readRegister(byte address) {
  // Change pin_menb to LOW to enable.
  digitalWrite(pin_menb(), LOW);

  // Status Register. Ready to accept I2C commands.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x01));
  Wire.endTransmission();

  // Lock Register. Read only mode.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x01));
  Wire.write(byte(0x01));
  Wire.endTransmission();

  // Get value of the register with address given.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(address);
  Wire.endTransmission();
  // Request only one byte.
  Wire.requestFrom((int) kSensorAddress, 1);
  byte reading = 0x00;
  // If one byte is received.
  if (1 <= Wire.available())
    reading = Wire.read();

  // Change pin_menb to HIGH to disable.
  digitalWrite(pin_menb(), HIGH);

  return reading;
}