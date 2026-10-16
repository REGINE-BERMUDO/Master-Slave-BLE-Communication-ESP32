#include "setup.h"

void setup() {
  Serial.begin(115200);

  // Call 
  ledpinSetup();

  // Call BLE Setup & Print Status
  Serial.println(bleSetup());
}

void loop() {
  // put your main code here, to run repeatedly:

}
