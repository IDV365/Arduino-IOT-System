//Sec sensors

bool PIR1_state = LOW;
bool DOOR_state = LOW;
bool prevPIR1_state = LOW;
bool prevDOOR_state = LOW;
int DOOR_value = 0;
WidgetLED DOOR_led(V21);
WidgetLED PIR1_led(V24);

void security_run() {
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  PIR1_state = digitalRead(PIR1_pin);
  
  if (hall_return() == HIGH) {
    DOOR_led.on();
  } 
  else if (hall_return() == LOW) {
    DOOR_led.off();
  }
  
  if (PIR1_state == HIGH) {
    PIR1_led.on();
  } else {
    PIR1_led.off();
  }
  if (PIR1_state == HIGH && prevPIR1_state == LOW) {
    if (pirAlarmState == HIGH) {
      Blynk.notify("PIR1 detected intruder in the hallway");
    }
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
BLYNK_WRITE(V40) {
  pirAlarmState = param.asInt();
}

bool hall_return() {
  bool input =  analogRead(hallPin);
  if (input < 350) {
    return LOW;
  }
  else {
    return HIGH;
  }
}