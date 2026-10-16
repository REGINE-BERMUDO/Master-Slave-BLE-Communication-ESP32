# Group Technical Guide

This guide describes the firmware currently present on the group's `main` branch. It records source-level configuration and the integration work needed to run the two Master options with the Blue and Red Slaves.

## Repository layout

| Path | Contents |
| :--- | :--- |
| `master/master.ino` | Original single-file FreeRTOS Master. |
| `master_modular/` | Modular Master sketch and its nine companion source/header files. |
| `Slave_Blue/` | Blue Slave sketch, setup module, and BLE callbacks. |
| `Slave_Red/` | Red Slave sketch, setup module, and BLE callbacks. |
| `demo/` | Serial Monitor and physical three-board recordings. |
| `docs/assets/` | README cover, icons, and badges. |

The repository's `main` branch contains these files together. `Paraguya` is an older snapshot: its Master and modular files are present, but its Slave folders contain only starter `.ino` files. The `Restauro` and `Bermudo` links in the [branch directory](../README.md#branches) show the respective member contributions.

## BLE configuration

The Master and both Slave implementations use the same BLE service and writable characteristic. Commands are the text values `ON` and `OFF`.

| Setting | Current source value |
| :--- | :--- |
| Service UUID | `ec8817e4-164d-4c5e-8f2f-9b238a1b4e23` |
| Characteristic UUID | `e70df770-9853-4704-bd6d-d18b3f8dfdb3` |
| Master discovery targets | `LAB7_SLAVE_1` and `LAB7_SLAVE_2` |
| Blue Slave advertised name on `main` | `ESP32 SLAVE Blue` |
| Red Slave advertised name on `main` | `ESP32 SLAVE Red` |

**The discovery targets do not match the two advertised names.** Set the Master's two target-name constants in `master/master.ino` and `master_modular/Config.h` to the names used by the Slaves, or change each Slave's `BLEDevice::init(...)` name to the corresponding Master target. Keep the two names unique. The same names must be used by both Master implementations.

Both Masters also include MAC-address fallbacks copied from Yestin's individual boards. If a Slave appears in the scan without a name, replace the fallback address with that group's board address from the Serial Monitor scan output.

The member branches contain different spellings: Blue on `Restauro` advertises `ESP32 Slave (Blue)`, while Red on `Bermudo` advertises `ESPS32 SLAVE Red`. Use the consolidated `main` files as the source of truth when editing.

## Pins and hardware

| Board role | Current source configuration | Wiring to confirm |
| :--- | :--- | :--- |
| Master | Pushbutton input GPIO 23 with `INPUT_PULLUP` | Button between GPIO 23 and GND. |
| Blue Slave | LED output GPIO 23 | Confirm the Blue board LED is wired to GPIO 23. |
| Red Slave | LED output GPIO 18 | Confirm the Red board LED is wired to GPIO 18. |

The pin settings come from the source. Check the actual group wiring before powering the boards; disconnect power before changing connections. Use an appropriate current-limiting resistor for each external LED.

## Build and upload

1. Use Arduino IDE with Espressif's ESP32 board package. The group's individual reference setup used Arduino IDE 2.3.10 and ESP32 core 3.3.11; confirm the installed versions before recording a group build result.
2. Open each `.ino` from its matching folder and select the board target and COM port for that physical board.
3. Keep every `.h` and `.cpp` file beside its `.ino`. The modular Master folder and filename must both be `master_modular` / `master_modular.ino`.
4. Build and upload the Blue and Red Slaves, then the selected Master. Open Serial Monitor at 115200 baud.
5. Confirm the two advertised names match the Master discovery targets before evaluating connections.

BLE and FreeRTOS are included in the ESP32 board package used by the reference setup; no separate BLE library is required.

## Functional checks

Run these checks separately for the original and modular Master:

1. Confirm discovery and connection to both Slaves.
2. Press and release the button; confirm both Slave LEDs follow the requested state.
3. Disconnect one Slave and check that the other continues receiving commands.
4. Restore power to the disconnected Slave and check that the Master reconnects and sends the latest requested state.
5. Repeat reconnection while holding the button and record the observed state.

The root README links to recorded results from Yestin's individually tested setup and to the group demonstration recordings. Keep those evidence sources labeled by setup when adding test results.

## Source review findings

- The original Master in `main` is byte-identical to Yestin's individually tested Master.
- The modular Master in `main` is byte-identical to the modular version on `Paraguya`.
- `main` contains both Slave folders and their setup/callback modules.
- The Master/Slave advertising-name mismatch must be corrected before the current source configuration can connect by name.
- The Blue and Red LED pins differ. Confirm GPIO 23 and GPIO 18 against the physical group wiring.

