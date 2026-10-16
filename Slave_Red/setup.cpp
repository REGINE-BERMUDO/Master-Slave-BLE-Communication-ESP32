#include "setup.h"

// ---------- Command handler ----------
void CommandCallbacks::onWrite(BLECharacteristic *characteristic) {
  auto command = characteristic->getValue();

  Serial.print("Received command: ");
  Serial.println(command.c_str());

  // Turn LED 1 ON
  if (command == "ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Red LED ON");
  }
  // Turn LED 1 OFF
  else if (command == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Red LED OFF");
  }
}

// ---------- Connection handler ----------
void ServerCallbacks::onConnect(BLEServer *server) {
  Serial.println("Slave Red connected to Master!");
}

void ServerCallbacks::onDisconnect(BLEServer *server) {
  Serial.println("Slave Red disconnected!");

  // Restart advertising so the Master can reconnect
  BLEDevice::startAdvertising();

  Serial.println("Slave Red advertising restarted!");
}