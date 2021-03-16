/*
Made by IDV, all rightes reserved!

-> GitHub : https://github.com/IDV365/Arduino-IOT-System

This code is written for fun, and pretty specific to what I'am doing!
Everyone can use it anywhere they want, if u like it I would love to know!


*/


//GLOBAL SETTINGS
#define SETTINGS_AMOUNT 5
#define EEPROM_MAX_SIZE 4
byte currentSettings[SETTINGS_AMOUNT];

bool oledState = LOW;
int routineInterval = 1000;
byte flashBrightness = 150;
int flashTime = 350;
int DOOR_triggerpoint = 350;
bool deskState = LOW;
   






void setup() {
  pinMode(deskRelayPin, OUTPUT);
  pinMode(oledGND, OUTPUT);
  pinMode(oledVCC, OUTPUT);
  buttons_setup();
  Serial.begin(9600);
  Blynk.begin(auth);
  wdt_enable(WDTO_8S);
  Wire.begin();
  BMP.beginI2C();
  dht.begin();
  lightMeter.begin();

  encoder.setPosition(1 / ROTARYSTEPS);

  sync_getEEPROM_setSETTINGS();
  terminal_setup();

  timer2.setInterval(3000L, checkBlynk);
  timer.setInterval(1000L, myTimerEvent);
  timer_fast.setInterval(1L, routine_fast);
  timer_medium.setInterval(100L, routine_medium);
  timer_slow.setInterval(4000L, routine_slow);
}

void loop() {
  Blynk.run();
  timer.run();
  timer2.run();
  timer_fast.run();
  timer_medium.run();
  timer_slow.run();
  wdt_reset();
  rotary_return();
  //oled_graphics("none");

}
