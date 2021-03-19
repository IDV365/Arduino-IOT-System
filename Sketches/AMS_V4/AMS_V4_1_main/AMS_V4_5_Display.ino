//U8glib
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





//Terminal Read
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
