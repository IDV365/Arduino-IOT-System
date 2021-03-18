char auth[] = "NEO79_k3Zzy1PqnLkNUOMZiIXJmIo3kz";


//Libraries
#include <SPI.h>
#include <Ethernet2.h>
#include <BlynkSimpleEthernet2.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <RGBLed.h>
#include <U8glib.h>
#include <avr/wdt.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <BH1750.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <EEPROM.h>
#include <RotaryEncoder.h>
#include <Keypad.h>

//Pin defines
#define deskPin 38
#define DHTPIN 49
#define buttenPinEncoder 4
#define buttenPinBlackbutton 5



//Objects
WidgetTable table;
BLYNK_ATTACH_WIDGET(table, V2);

BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V1);

RGBLed led(12, 13, 11, RGBLed::COMMON_CATHODE);

BlynkTimer timer2;

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);

DHT_Unified dht(DHTPIN, DHT11);
BH1750 lightMeter;
BME280 BMP;

#define PIN_IN1 2
#define PIN_IN2 3
#define ROTARYSTEPS 2
#define ROTARYMIN 2
#define ROTARYMAX 6
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', 'E', 'F', 'G'}
};
byte rowPins[ROWS] = {29, 27, 25, 23};
byte colPins[COLS] = {22, 24, 26, 28};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



//Settings
#define SETTINGS_AMOUNT 5
#define EEPROM_MAX_SIZE 4
byte currentSettings[SETTINGS_AMOUNT];

int routineInterval = 1000;
byte flashBrightness = 150;
int flashTime = 350;
int DOOR_triggerpoint = 350;
bool deskState = LOW;




BlynkTimer timer_fast;
void routine_fast() {
  control_update();
  security_run();
}
BlynkTimer timer_medium;
void routine_medium() {
  buttons_refrech();
 //f digitalWrite(deskRelayPin, deskState);
}

BlynkTimer timer_slow;
void routine_slow() {

}

void myTimerEvent() {
  Blynk.virtualWrite(V10, DHT_return('T'));
  Blynk.virtualWrite(V11, DHT_return('H'));
  Blynk.virtualWrite(V12, BH1750_return());
  Blynk.virtualWrite(V20, hall_return());
  buttons_refrech();

}







void setup() {
  pinMode(deskPin, OUTPUT);
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

  control_update();

}
