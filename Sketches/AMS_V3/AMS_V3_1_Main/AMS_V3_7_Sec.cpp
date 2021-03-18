#include "AMS_V3_7_Sec.h"

void security_run() {
  static bool PIR1_state = LOW;
  static bool DOOR_state = LOW;
  static bool prevPIR1_state = LOW;
  static bool prevDOOR_state = LOW;
  static int DOOR_value = 0;
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

int hall_return() {
  return analogRead(hallPin);
}
