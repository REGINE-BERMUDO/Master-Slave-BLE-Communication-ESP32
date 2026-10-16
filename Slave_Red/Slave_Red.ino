#include "setup.h"

void setup() {
  Serial.begin(115200);
  delay(1000); 
   // Configure Red LED 
  pinMode(LED_PIN, OUTPUT);

  // Keep LED OFF at startup
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // BLE commands are handled automatically by callbacks
}
