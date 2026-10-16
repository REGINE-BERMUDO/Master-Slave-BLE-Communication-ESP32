#include "setup.h"

void setup() {
  Serial.begin(115200);
  delay(1000); 

  setupSlave();
}

void loop() {
  // BLE commands are handled automatically by callbacks
}
