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

  /* TODO: change pin_menb to LOW for enabled */
  digitalWrite(pin_menb(), HIGH);
  
  // Ready.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0x01));
  Wire.endTransmission();
  
  // Mode - unlock write mode.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x01));
  Wire.write(byte(0x00));
  Wire.endTransmission();

  // Data.
  Wire.beginTransmission(kSensorAddress);
  // Wire.write(current_register().address());
  Wire.write(byte(0x10));
  // Wire.write(current_register().value());
  Wire.write(byte(0xF0));
  Wire.endTransmission();

  digitalWrite(pin_menb(), LOW);
}


// I2C read method.
byte GasSensor::readRegister() {
  digitalWrite(pin_menb(), HIGH);

  // Mode - unlock write mode.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x01));
  Wire.write(byte(0x01));
  Wire.endTransmission();

  // Get value for 0x10 register.
  Wire.beginTransmission(kSensorAddress);
  Wire.write(byte(0x10));
  Wire.endTransmission();

  Wire.requestFrom((int) kSensorAddress, 1);
  byte reading = 0x00;

  // If one byte were received.
  if(1 <= Wire.available())
  {
    reading = Wire.read();
  }

  digitalWrite(pin_menb(), LOW);

  return reading;
}