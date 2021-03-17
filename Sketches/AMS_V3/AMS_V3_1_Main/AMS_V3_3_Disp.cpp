//U8GLIB

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST);

void oled_refresh(String selector) {

  if (selector == "START") {
    oledState = LOW;
  }
  else if (selector == "STOP") {
    oledState = HIGH;
  }
  digitalWrite(oledGND, oledState);
  digitalWrite(oledVCC, oledState);
}





//Oled Menu
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
    Serial.println(page);
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
  Blynk.virtualWrite(V1, " - get.oledState");
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
  Blynk.virtualWrite(V1, " - start.oled");
  Blynk.virtualWrite(V1, " - stop.oled");
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





//Table
void update_table(String value) {
  static int rowIndex = 0;
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  table.addRow(rowIndex, value, currentTime);
  table.pickRow(rowIndex);
  rowIndex++;
}
