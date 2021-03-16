//WATCHDOG TIMER
#include <avr/wdt.h>
BlynkTimer timer2;
int disconnects;
void(* resetFunc) (void) = 0;
void checkBlynk() {
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    disconnects++;
    resetFunc();
  }
}



// EEPROM
#include <EEPROM.h>
void updateEEPROM() {
  for (int i = 0; i < SETTINGS_AMOUNT; i++) {
    EEPROM.update(i, currentSettings[i]);
  }
}
void getSettings_fromEEPROM() {
  for (int i = 0; i < SETTINGS_AMOUNT; i++) {
    currentSettings[i] = EEPROM.read(i);
  }
}

void sync_getEEPROM_setSETTINGS() {
  getSettings_fromEEPROM();
  oledState = currentSettings[1];
  routineInterval = currentSettings[2] * EEPROM_MAX_SIZE;
  flashBrightness = currentSettings[3];
  flashTime = currentSettings[4] * EEPROM_MAX_SIZE;
  DOOR_triggerpoint = currentSettings[5] * 2;
}

void sync_getSETTINGS_setEEPROM() {
  currentSettings[1] = oledState;
  currentSettings[2] = routineInterval / EEPROM_MAX_SIZE;
  currentSettings[3] = flashBrightness;
  currentSettings[4] = flashTime / EEPROM_MAX_SIZE;
  currentSettings[5] = DOOR_triggerpoint / 2;
  updateEEPROM();
}
