#include "setup.h"

BLE_ServerConnection_Callback ble_srvconn_cb;
BLE_LEDWrite_Callback ble_ledwrite_cb;

void ledpinSetup(void) {
  // Configure LED pin 20
  pinMode(CREDLED_PIN, OUTPUT);

  // Set Initial LED pin state to low
  digitalWrite(CREDLED_PIN, LOW);
}

String bleSetup(void) {
  // Initialize BLE with advertising name
  BLEDevice::init("ESP32 SLAVE Blue");

  // Create BLE Server for this device
  BLEServer *ptrServer = BLEDevice::createServer();

  // Create BLE LED Service & Led write characteristic
  BLEService *ptrService_LED = ptrServer->createService(SERVICE_LED_UUID);
  BLECharacteristic *ptrCharacteristic_ledwrite = ptrService_LED->createCharacteristic(CHARACTERISTIC_LEDWRITE_UUID, BLECharacteristic::PROPERTY_WRITE);

  // Set Server Callback function
  ptrServer->setCallbacks(&ble_srvconn_cb);

  // Set LED Write Characteristic Callback function
  ptrCharacteristic_ledwrite->setCallbacks(&ble_ledwrite_cb);

  // Start BLE LED Service
  ptrService_LED->start();

  // Create advertising instance
  BLEAdvertising *ptrAdvertise = BLEDevice::getAdvertising();

  // Advertise LED Service
  ptrAdvertise->addServiceUUID(SERVICE_LED_UUID);

  // Start advertising
  ptrAdvertise->start();

  return "ESP32 Slave (Blue) is ready! Advertising BLE";
}