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
Register GasSensor::status() {
  return status_;
}

Register GasSensor::lock() {
  return lock_;
}

Register GasSensor::reserved() {
  return reserved_;
}

Register GasSensor::tiacn() {
  return tiacn_;
}

Register GasSensor::refcn() {
  return refcn_;
}

Register GasSensor::modecn() {
  return modecn_;
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
void GasSensor::set_status(Register state) {
  status_ = state;
}

void GasSensor::set_status(byte address, byte value) {
  status_.set_address(address);
  status_.set_value(value);
}

// Lock.
void GasSensor::set_lock(Register lock) {
  lock_ = lock;
}

void GasSensor::set_lock(byte address, byte value) {
  lock_.set_address(address);
  lock_.set_value(value);
}

// Reserved
void GasSensor::set_reserved(Register reserved) {
  reserved_ = reserved;
}

void GasSensor::set_reserved(byte address, byte value) {
  reserved_.set_address(address);
  reserved_.set_value(value);
}

// Tiacn.
void GasSensor::GasSensor::set_tiacn(Register tiacn) {
  tiacn_ = tiacn;
}

void GasSensor::set_tiacn(byte address, byte value) {
  tiacn_.set_address(address);
  tiacn_.set_value(value);
}

// Refcn
void GasSensor::set_refcn(Register refcn) {
  refcn_ = refcn;
}

void GasSensor::set_refcn(byte address, byte value) {
  refcn_.set_address(address);
  refcn_.set_value(value);
}

// Modecn.
void GasSensor::set_modecn(Register modecn) {
  modecn_ = modecn;
}

void GasSensor::set_modecn(byte address, byte value) {
  modecn_.set_address(address);
  modecn_.set_value(value);
}

// I2C write method.
void GasSensor::writeRegister(byte address, byte value) {
  Wire.beginTransmission(kSensorAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void GasSensor::writeRegister(Register reg) {
  Wire.beginTransmission(kSensorAddress);
  Wire.write(reg.address());
  Wire.write(reg.value());
  Wire.endTransmission();
}