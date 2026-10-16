#include "setup.h"





// Connection Handler
class BLE_ServerConnection_Callback : public BLEServerCallbacks {
public:
  // Master connects
  void onConnect(BLEServer *pServer)
  override {
    Serial.println("ESP32 Slave (Blue) successfully connected to ESP32 Master!");
  }

  // When Master or Slave disconnects
  void onDisconnect(BLEServer *pServer)
  override {
    Serial.println("ESP32 Slave (Blue) disconnected!");

    // Re-advertise after disconnection
    BLEDevice::startAdvertising();

    Serial.println("ESP32 Slave (Blue) advertising restarted!");
  }
};

class BLE_LEDWrite_Callback : public BLECharacteristicCallbacks {
public:
  // When Master sends LED Command
  void onWrite(BLECharacteristic *pCharacteristic)
  override {
    // Gather Master LED Command
    stding::string ledcommand = pCharacteristic->getValue();

    Serial.println("Received LED Command:" + String(command.c_str()));

    // Set LED Pin to HIGH if command is ON
    if(ledcommand == "ON") {
      digitalWrite(CREDLED_PIN, LOW);
      Serial.println("RED LED PIN ON");
    }

    // Set LED Pin to LOW if command is OFF
    if(ledcommand == "OFF") {
      digitalWrite(CREDLED_PIN, LOW);
      Serial.println("RED LED PIN OFF");
    }
  }
};

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
  BLEDevice::init("ESP32 Slave (Blue)");

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