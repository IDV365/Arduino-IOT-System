#include <avr/wdt.h>
BlynkTimer timer2;

#include <EEPROM.h>

#include <RGBLed.h>
RGBLed led(12, 13, 11, RGBLed::COMMON_CATHODE);



void RGB_flash(String COLOUR, byte FLASH_BRIGHTNES, int ON_TIME);
void checkBlynk();
void(* resetFunc) (void);
void getSettings_fromEEPROM();
void sync_getEEPROM_setSETTINGS();
void sync_getSETTINGS_setEEPROM();
