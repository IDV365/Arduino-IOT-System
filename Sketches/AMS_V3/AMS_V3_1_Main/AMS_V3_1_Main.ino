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



#include <SPI.h> 
#include <Ethernet2.h>
#include <BlynkSimpleEthernet2.h>
#include <TimeLib.h> 
#include <WidgetRTC.h>
#define BLYNK_PRINT Serial


//ROUTINES
BlynkTimer timer_fast;
void routine_fast() {
  control_update();
  security_run();
}
#define deskRelayPin 38
BlynkTimer timer_medium;
void routine_medium() {
  buttons_refrech();
  digitalWrite(deskRelayPin, deskState);
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


void control_update() {
  if (Keypad_return() == '1') {
    oledState != oledState;
  }
}




//Blynk
WidgetTable table;
BLYNK_ATTACH_WIDGET(table, V2);

BlynkTimer timer;
WidgetRTC rtc;
WidgetTerminal terminal(V1);
BLYNK_CONNECTED() {
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
}

BLYNK_WRITE(V52) {
  if (param.asInt()) {
    table.clear();
    rowIndex = 0;
  }
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
  else if (String("get.oledState") == command) {
    Blynk.virtualWrite(V1, "Current oledState: ");
    if (oledState == HIGH) {
      Blynk.virtualWrite(V1, "true", "\n");
    }
    else {
      Blynk.virtualWrite(V1, "false", "\n");
    }
  }
  else if (String("start.oled") == command) {
    oled_refresh("start");
  }
  else if (String("start.oled") == command) {
    oled_refresh("stop");
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
