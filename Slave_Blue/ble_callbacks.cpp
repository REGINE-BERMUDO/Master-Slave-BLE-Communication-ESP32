#include "ble_callbacks.h"

void BLE_ServerConnection_Callback::onConnect(BLEServer *pServer) {
  Serial.println("ESP32 Slave (Blue) successfully connected to ESP32 Master!");
}

void BLE_ServerConnection_Callback::onDisconnect(BLEServer *pServer) {
  Serial.println("ESP32 Slave (Blue) disconnected!");

  // Re-advertise after disconnection
  BLEDevice::startAdvertising();

  Serial.println("ESP32 Slave (Blue) advertising restarted!");
}

void BLE_LEDWrite_Callback::onWrite(BLECharacteristic *pCharacteristic) {
  // Gather Master LED Command
  String ledcommand = pCharacteristic->getValue();

  Serial.println("Received LED Command: " + ledcommand);

  // Set LED Pin to HIGH if command is ON
  if(ledcommand == "ON") {
    digitalWrite(CREDLED_PIN, HIGH);
    Serial.println("RED LED PIN ON");
  }

  // Set LED Pin to LOW if command is OFF
  if(ledcommand == "OFF") {
    digitalWrite(CREDLED_PIN, LOW);
    Serial.println("RED LED PIN OFF");
  }
}