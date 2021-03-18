//GLOBAL SETTINGS
#define SETTINGS_AMOUNT 5
#define EEPROM_MAX_SIZE 4
byte currentSettings[SETTINGS_AMOUNT];

int routineInterval = 1000;
byte flashBrightness = 150;
int flashTime = 350;
int DOOR_triggerpoint = 350;
bool deskState = LOW;


//BLYNK
#include <SPI.h>
#include <Ethernet2.h>
#include <BlynkSimpleEthernet2.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#define BLYNK_PRINT Serial

char auth[] = "NEO79_k3Zzy1PqnLkNUOMZiIXJmIo3kz";

WidgetTable table;
BLYNK_ATTACH_WIDGET(table, V2);

BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V1);


//RGB
#include <RGBLed.h>
RGBLed led(12, 13, 11, RGBLed::COMMON_CATHODE);
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


BLYNK_CONNECTED() {
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
  Blynk.syncVirtual(V30);
}

int hall_return() {
#define hallPin A8
  return analogRead(hallPin);
}

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

#define buttenPinEncoder 4
#define buttenPinBlackbutton 5

//BUTTONS
void buttons_setup() {
  pinMode(buttenPinEncoder, INPUT_PULLUP);
  pinMode(buttenPinBlackbutton, INPUT_PULLUP);
}
bool encoder_buttonState = false;
bool buttenPin_blackbutton = false;

void buttons_refrech() {
  encoder_buttonState = digitalRead(buttenPinEncoder);
  buttenPin_blackbutton = digitalRead(buttenPinBlackbutton);

  if (encoder_buttonState == HIGH) {
    oled_graphics("encoderButton");
  }
  else if (buttenPin_blackbutton == HIGH) {
    oled_graphics("blackButton");
  }

}




//ROTARYENCODER
#include <RotaryEncoder.h>
#define PIN_IN1 2
#define PIN_IN2 3
#define ROTARYSTEPS 2
#define ROTARYMIN 2
#define ROTARYMAX 6
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int rotary_return() {
  static int lastPos = -1;
  encoder.tick();

  int newPos = encoder.getPosition() * ROTARYSTEPS;
  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } // if

  if (lastPos != newPos) {
    lastPos = newPos;
    return newPos;
  }
}

// KEYPAD
#include <Keypad.h>
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
char Keypad_return() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    return customKey;
  }
}
bool Keypad_ask(char ask) {
  char customKey = customKeypad.getKey();
  if (customKey == ask) {
    return LOW;
  }
  else {
    return HIGH;
  }
}
#define deskPin 38
BLYNK_WRITE(V30) {
  deskState =  param.asInt();
  digitalWrite(deskPin, deskState);
}


void control_update() {
  bool input1 = Keypad_ask('5');
  if (input1 == LOW) {
    deskState = !deskState;
    digitalWrite(deskPin, deskState);
    Blynk.virtualWrite(V30, deskState);
    Blynk.syncVirtual(V30);
  }
}



//U8GLIB

#include <U8glib.h>
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);


String Weekday[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thunderday", "Friday", "Saterday"};

void oled_graphics(String cmd) {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + "/" + month() + "/" + "21";
  String Time = String( currentTime + "  " + Weekday[weekday() - 1] + "  " +  currentDate);
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_orgv01);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawLine(0, 55, 128, 55);
    u8g.setPrintPos(3, 62);
    u8g.print(Time);

    int page = rotary_return();
    if (page == 2) {
      u8g.drawStr(5, 10, "Temp: ");
      u8g.setPrintPos(35, 10);
      u8g.print(DHT_return('T'));
      u8g.drawStr(70, 10, "C");

      u8g.drawStr(5, 20, "Hum: ");
      u8g.setPrintPos(35, 20);
      u8g.print(DHT_return('H'));
      u8g.drawStr(70, 20, "%");

      u8g.drawStr(5, 30, "Lux: ");
      u8g.setPrintPos(35, 30);
      u8g.print(BH1750_return());
    }
    else if (page == 4) {
      u8g.drawStr(5, 10, "Desk power  on/off");
      if (cmd == "blackButton") {
        deskState = !deskState;
      }
    }
    else if (page == 6) {
      u8g.drawStr(5, 10, "(6) Nothing here yet  xD");
    }

  } while ( u8g.nextPage() );
}

//DHT
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 49
DHT_Unified dht(DHTPIN, DHT11);
float DHT_return(char selector) {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if ( selector == 'T') {
    if (isnan(event.temperature)) {
    }
    else {
      return event.temperature;
    }
  }
  else if ( selector == 'H') {
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
    }
    else {
      return event.relative_humidity;
    }
  }
}



//BH1750
#include <BH1750.h>
BH1750 lightMeter;
float BH1750_return() {
  float lux = lightMeter.readLightLevel();
  return lux;
}

//BMP
#include <Wire.h>
#include "SparkFunBME280.h"
BME280 BMP;
float BMP_return(char selector) {
  if (selector == 'T') {
    return BMP.readTempC();
  } else if (selector == 'F') {
    return BMP.readTempF();
  } else if (selector == 'H') {
    return BMP.readFloatHumidity();
  } else if (selector == 'P') {
    return BMP.readFloatPressure();
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
  routineInterval = currentSettings[2] * EEPROM_MAX_SIZE;
  flashBrightness = currentSettings[3];
  flashTime = currentSettings[4] * EEPROM_MAX_SIZE;
  DOOR_triggerpoint = currentSettings[5] * 2;
}

void sync_getSETTINGS_setEEPROM() {
  currentSettings[2] = routineInterval / EEPROM_MAX_SIZE;
  currentSettings[3] = flashBrightness;
  currentSettings[4] = flashTime / EEPROM_MAX_SIZE;
  currentSettings[5] = DOOR_triggerpoint / 2;
  updateEEPROM();
}


//TERMINAL
void terminal_help() {
  Blynk.virtualWrite(V1, "You called the help function", "Here is a list of compatible commands for the terminal:", "\n", "\n");

  Blynk.virtualWrite(V1, "To get info:");
  Blynk.virtualWrite(V1, "-------------");
  Blynk.virtualWrite(V1, " - get.connectionState");
  Blynk.virtualWrite(V1, " - get.routineInterval");
  Blynk.virtualWrite(V1, " - get.flashBrightness");
  Blynk.virtualWrite(V1, " - get.flashTime");
  Blynk.virtualWrite(V1, "\n", "\n");

  Blynk.virtualWrite(V1, "To change settings:");
  Blynk.virtualWrite(V1, "-------------");
  Blynk.virtualWrite(V1, " - set.sensor   (NOT AVAILABLE YET)");
  Blynk.virtualWrite(V1, " - set.routineSpeed   (NOT AVAILABLE YET)");
  Blynk.virtualWrite(V1, " - set.flashBrightness");
  Blynk.virtualWrite(V1, " - set.flashTime");
  Blynk.virtualWrite(V1, "\n", "\n");

  Blynk.virtualWrite(V1, "To start or stop tasks:");
  Blynk.virtualWrite(V1, "-------------");
  Blynk.virtualWrite(V1, "\n", "\n");

  Blynk.virtualWrite(V1, "\n");

}

void terminal_setup() {
  terminal.clear();
  Blynk.virtualWrite(V1, "\n"
                     "   ___  __          __\n"
                     "  / _ )/ /_ _____  / /__\n"
                     " / _  / / // / _ \\/  '_/\n"
                     "/____/_/\\_, /_//_/_/\\_\\\n"
                     "       /___/ v." BLYNK_VERSION " on\n            " BLYNK_INFO_DEVICE "\n");
  size_t ram = BlynkFreeRam();
  Blynk.virtualWrite(V1, "\n Free RAM: ", ram);
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + "/" + month() + "/" + year();
  Blynk.virtualWrite(V1, "\n ", currentTime, " ", currentDate);
}

BLYNK_WRITE(V1) {
  String terminalInput = param.asStr();

  bool seperator = false;
  int seperator_pos = -1;
  int ctr = 0;
  for (int i = 0; terminalInput.length() > i; i++) {
    if (terminalInput[ctr] == ' ') {
      seperator_pos = ctr;
      seperator = true;
    }
    else {
      ctr++;
    }
  }
  String command;
  String valueString;
  int value;
  if (seperator_pos == -1) {
    command = terminalInput;
  } else {
    command = terminalInput.substring(0, seperator_pos);
    valueString = terminalInput.substring(seperator_pos + 1, terminalInput.length());
    value = valueString.toInt();
  }
  Serial.println(terminalInput);
  Serial.println(command);

  if (String("help") == command) {
    terminal_help();
  }
  else if (String("set.routineSpeed") == command) {
  }
  else if (String("set.flashBrightness") == command) {
    //flashBrightness ==
  }
  else if (String("set.flashTime") == command) {
  }
  else if (String("get.connectionState") == command) {
    Blynk.virtualWrite(V1, Blynk.connected(), "\n");
  }
  else {
    terminal.println("Not a valid command");
    terminal.println('\n');
  }
  terminal.flush();
  sync_getSETTINGS_setEEPROM();

}






#define PIR1_pin 45
#define DOOR_pin A8
bool PIR1_state = LOW;
bool DOOR_state = LOW;
bool prevPIR1_state = LOW;
bool prevDOOR_state = LOW;
int DOOR_value = 0;
WidgetLED DOOR_led(21);
WidgetLED PIR1_led(24);
void security_run() {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  PIR1_state = digitalRead(PIR1_pin);
  DOOR_value = analogRead(DOOR_pin);
  if (DOOR_value < DOOR_triggerpoint) {
    DOOR_state = HIGH;
    DOOR_led.on();
  } else {
    DOOR_state = LOW;
    DOOR_led.off();
  }
  if (PIR1_state == HIGH) {
    PIR1_led.on();
  } else {
    PIR1_led.off();
  }
  if (PIR1_state == HIGH && prevPIR1_state == LOW) {
    Blynk.notify("PIR1 detected intruder in the hallway");
    RGB_flash("Red", 255, 750);
    Blynk.virtualWrite(V23, currentTime);
    update_table("PIR1 triggerd at :");


  }
  if (DOOR_state == LOW && prevDOOR_state == HIGH || DOOR_state == HIGH && prevDOOR_state == LOW) {
    Blynk.notify("Door opend or closed");
  }
  prevPIR1_state = PIR1_state;
  prevDOOR_state = DOOR_state;
}
//Table
int rowIndex = 0;
void update_table(String value) {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  table.addRow(rowIndex, value, currentTime);
  table.pickRow(rowIndex);
  rowIndex++;
}
BLYNK_WRITE(V52) {
  if (param.asInt()) {
    table.clear();
    rowIndex = 0;
  }
}

void security_updateBlynk() {

}

BlynkTimer timer_fast;
void routine_fast() {
  control_update();
  security_run();
}
#define deskRelayPin 38
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
  digitalWrite(deskRelayPin, deskState);

}



void setup() {
  pinMode(deskRelayPin, OUTPUT);
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



/* IDEAS

    een sensor selector
  v  een h in terminal -> Lijst met functies, en instellingen die je kan veranderen
  v > Instellingen in EEPROM
  v  in setup instellingen inlezen uit eeprom
  v  na dat er een instelling veranderd is eeporom updaten

    alarm voor als bepaalde waarde boven een bepaald maxiumum gaan
    bv. als het te warm wordt, een melding dat de verwarming af moet gezet worden

  v    tijd op oled

    oled op relay!

    interval van routine vervangen met een Timer


*/
