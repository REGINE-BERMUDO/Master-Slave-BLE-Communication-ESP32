#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// Shared BLE UUIDs
#define SERVICE_UUID        "ec8817e4-164d-4c5e-8f2f-9b238a1b4e23"
#define CHARACTERISTIC_UUID "e70df770-9853-4704-bd6d-d18b3f8dfdb3"

// LED connected to GPIO 18
#define LED_PIN 18

// Handle commands received from the Master
class CommandCallbacks : public BLECharacteristicCallbacks {
public:
  void onWrite(BLECharacteristic *characteristic) override;
};

// Handle BLE connection and disconnection
class ServerCallbacks : public BLEServerCallbacks {
public:
  void onConnect(BLEServer *server) override;
  void onDisconnect(BLEServer *server) override;
};

#endif