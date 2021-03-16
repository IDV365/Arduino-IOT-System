//BLYNK
#include <SPI.h> 
#include <Ethernet2.h>
#include <BlynkSimpleEthernet2.h>
#include <TimeLib.h> 
#include <WidgetRTC.h>
#define BLYNK_PRINT Serial



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
