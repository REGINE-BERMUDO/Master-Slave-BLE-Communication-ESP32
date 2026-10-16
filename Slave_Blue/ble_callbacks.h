#ifndef BLE_CALLBACKS_H
#define BLE_CALLBACKS_H

// Pin Macro
#define CREDLED_PIN 23

#include <BLEDevice.h>

class BLE_ServerConnection_Callback : public BLEServerCallbacks { // Connection Handler
public:
  void onConnect(BLEServer *pServer) override; // Master connects
  void onDisconnect(BLEServer *pServer) override; // When Master or Slave disconnects
};

class BLE_LEDWrite_Callback : public BLECharacteristicCallbacks { // LED Write Command Handler
public:
  void onWrite(BLECharacteristic *pCharacteristic) override; // When Master sends LED Command
};

#endif