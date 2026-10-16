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

// ---------- Setup ----------
void setupSlave() {
  // Configure Red LED
  pinMode(LED_PIN, OUTPUT);

  // Keep LED OFF at startup
  digitalWrite(LED_PIN, LOW);

  // Initialize BLE Slave Red
  BLEDevice::init("ESP32 SLAVE Red");

  // Create BLE Server
  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new ServerCallbacks());

  // Create BLE Service
  BLEService *service = server->createService(SERVICE_UUID);

  // Create writable Characteristic
  BLECharacteristic *characteristic =
      service->createCharacteristic(
          CHARACTERISTIC_UUID,
          BLECharacteristic::PROPERTY_WRITE
      );

  // Assign command handler
  characteristic->setCallbacks(new CommandCallbacks());

  // Start BLE Service
  service->start();

  // Configure and start advertising
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("Slave Red ready; advertising BLE");
}