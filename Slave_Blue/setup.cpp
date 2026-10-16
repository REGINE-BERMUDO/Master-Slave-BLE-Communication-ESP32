#include "setup.h"

// Connection Handler
class BLE_Server_Callback : public BLEServerCallbacks {
public:
  // Master connects
  void onConnect(BLEServer *pServer, BLEConnInfo& connInfo)
  override {
    Serial.println("ESP32 Slave (Blue) successfully connected to ESP32 Master!");
  }

  // When Master or Slave disconnects
  void onDisconnect(BLEServer *pServer, BLEConnInfo& connInfo)
  override {
    Serial.println("ESP32 Slave (Blue) disconnected!");

    // Re-advertise after disconnection
    BLEDevice::startAdvertising();

    Serial.println("ESP32 Slave (Blue) advertising restarted!");
  }
};

BLE_Server_Callback ble_srv_cb;

void ledpinSetup(void) {
  // Configure LED pin 20
  pinMode(CLED_PIN, OUTPUT);

  // Set Initial LED pin state to low
  digitalWrite(CLED_PIN, LOW);
}

String bleSetup(void) {
  // Initialize BLE with advertising name
  BLEDevice::init("ESP32 Slave (Blue)");

  // Create BLE Server for this device
  BLEServer *ptrServer = BLEDevice::createServer();

  // Create BLE LED Service & Led write characteristic
  BLEService *ptrService_LED = ptrServer->createService(SERVICE_LED_UUID);
  BLECharacteristic *ptrCharacteristic_ledwrite = ptrService_LED->createCharacteristic(CHARACTERISTIC_LEDWRITE_UUID, BLECharacteristic::PROPERTY_WRITE);

  // Set Server Callback functions
  ptrServer->setCallbacks();

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