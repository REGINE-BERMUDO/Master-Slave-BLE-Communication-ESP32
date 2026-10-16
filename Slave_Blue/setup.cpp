#include "setup.h"

void ledpinSetup(void) {
  // Configure LED pin 20
  pinMode(CLED_PIN, OUTPUT);

  // Set Initial LED pin state to low
  digitalWrite(CLED_PIN, LOW);
}

void bleSetup(void) {
  // Initialize BLE with advertising name
  BLEDevice::init("ESP32 Slave (Blue)");

  // Create BLE Server for this device
  BLEServer *ptrServer = BLEDevice::createServer();

  // Create BLE LED Service & Led write characteristic
  BLEService *ptrService_LED = ptrServer->createService(SERVICE_LED_UUID);
  BLECharacteristic *ptrCharacteristic_ledwrite = ptrService_LED->createCharacteristic(CHARACTERISTIC_LEDWRITE_UUID, BLECharacteristic::PROPERTY_WRITE);
}