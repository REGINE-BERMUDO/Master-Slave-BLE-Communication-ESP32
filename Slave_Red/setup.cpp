#include "setup.h"

// ---------- Command handler ----------
void CommandCallbacks::onWrite(BLECharacteristic *characteristic) {
  auto command = characteristic->getValue();

  Serial.print("Received command: ");
  Serial.println(command.c_str());

  // Turn LED 1 ON
  if (command == "ON") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED 1 ON");
  }
  // Turn LED 1 OFF
  else if (command == "OFF") {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED 1 OFF");
  }
}