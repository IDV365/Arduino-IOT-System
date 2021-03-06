char auth[] = "U9t1B_3Q_hNEaciGMftBF8M78mlI7lFW";

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
#include <DallasTemperature.h>
#include "SparkFunBME280.h"
#include <EEPROM.h>
#include <RotaryEncoder.h>
#include <Keypad.h>
#include <DallasTemperature.h>


//Pin defines
#define DHTPIN 49
#define buttenPinEncoder 4
#define buttenPinBlackbutton 5
#define DallasPin 6
#define hallPin A8
#define PIR1_pin 45
#define PIR2_pin 44
#define beep_pin 46
#define deskPin 34
#define relay1 30
#define relay2 31
#define relay3 32
#define relay4 33



//Objects
OneWire oneWire(DallasPin);
DallasTemperature Dallas(&oneWire);


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

//states
bool deskState = LOW;
bool pirAlarmState = HIGH;
bool pir2AlarmState = HIGH;
bool beepState = HIGH;
bool relay1_state = HIGH;
bool relay2_state = HIGH;
bool relay3_state = HIGH;
bool relay4_state = HIGH;
bool allRelay_state = LOW;
bool pir2AutoOff_state = LOW;
bool pir2AutoOn_state = LOW;
bool relay1Auto_state = LOW;
bool relay2Auto_state = LOW;
bool relay3Auto_state = LOW;
bool relay4Auto_state = LOW;
bool wallAuto_state = LOW;


//Events and routines
BlynkTimer timer_fast;
void routine_fast() {
  key_control();
}
BlynkTimer timer_medium;
void routine_medium() {
  buttons_refrech();
  security_run();
  PIR2_control_V2();
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






//Setup
void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(beep_pin, OUTPUT);
  pinMode(deskPin, OUTPUT);
  digitalWrite(deskPin, LOW);
  buttons_setup();
  Serial.begin(9600);
  Blynk.begin(auth);
  wdt_enable(WDTO_8S);
  Wire.begin();
  BMP.beginI2C();
  dht.begin();
  lightMeter.begin();
  Dallas.begin();



  encoder.setPosition(1 / ROTARYSTEPS);

  sync_getEEPROM_setSETTINGS();
  terminal_setup();

  timer2.setInterval(3000L, checkBlynk);
  timer.setInterval(1000L, myTimerEvent);
  timer_fast.setInterval(1L, routine_fast);
  timer_medium.setInterval(200L, routine_medium);
  timer_slow.setInterval(4000L, routine_slow);
}

//Loop
void loop() {
  Blynk.run();
  timer.run();
  timer2.run();
  timer_fast.run();
  timer_medium.run();
  timer_slow.run();
  wdt_reset();
  rotary_return();

}
