
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
