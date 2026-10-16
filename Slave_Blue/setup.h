#ifndef SETUP_H
#define SETUP_H

// Pin Macro
#define CLED_PIN 20

// LED Service & Characteristics UUID
#define SERVICE_LED_UUID "ec8817e4-164d-4c5e-8f2f-9b238a1b4e23"
#define CHARACTERISTIC_LEDWRITE_UUID "e70df770-9853-4704-bd6d-d18b3f8dfdb3"

#include <Arduino.h>
#include <BLEDevice.h>

// Sets up Controllable LED Pin
void ledpinSetup(void);

// BLE Initialize & Start Advertise
void bleSetup(void);

#endif