#include "AMS_V3_6_Other.h"
//WATCHDOG TIMER

void(* resetFunc) (void) = 0;
void checkBlynk() {
  static int disconnects;
  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    disconnects++;
    resetFunc();
  }
}



// EEPROM
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


//RGB
void RGB_flash(String COLOUR, byte FLASH_BRIGHTNES, int ON_TIME) {
  if (COLOUR == "Red") {
    led.flash(FLASH_BRIGHTNES, 0, 0, ON_TIME);
  }
  else if (COLOUR == "Green") {
    led.flash(0, FLASH_BRIGHTNES, 0, ON_TIME);
  }
  else if (COLOUR == "Blue") {
    led.flash(0, 0, FLASH_BRIGHTNES, ON_TIME);
  }
  else if (COLOUR == "Purple") {
    led.flash(FLASH_BRIGHTNES, 0, FLASH_BRIGHTNES - 200, ON_TIME);
  }
  if (COLOUR == 'O') {
    led.off();
  }
}
