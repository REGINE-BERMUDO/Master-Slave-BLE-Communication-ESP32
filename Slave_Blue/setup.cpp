#include "setup.h"

void ledpinSetup(void) {
  // Configure LED Pin 20
  pinMode(CLED_PIN, OUTPUT);

  digitalWrite(CLED_PIN, LOW);
}