
//Blynk

BLYNK_CONNECTED() {
  Blynk.syncAll();
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
}

BLYNK_WRITE(V30) {
  deskState =  param.asInt();
  digitalWrite(deskPin, deskState);
}
BLYNK_WRITE(V25) {
  pirAlarmState = param.asInt();
}
BLYNK_WRITE(V28) {
  pir2AutoOn_state = param.asInt();
}
BLYNK_WRITE(V29) {
  pir2AutoOff_state = param.asInt();
}
BLYNK_WRITE(V32) {
  beepState = param.asInt();
}
BLYNK_WRITE(V61) {
  relay1_state = param.asInt();
  digitalWrite(relay1, relay1_state);
}
BLYNK_WRITE(V62) {
  relay2_state = param.asInt();
  digitalWrite(relay2, relay2_state);
}
BLYNK_WRITE(V63) {
  relay3_state = param.asInt();
  digitalWrite(relay3, relay3_state);
}
BLYNK_WRITE(V64) {
  relay4_state = param.asInt();
  digitalWrite(relay4, relay4_state);
}
BLYNK_WRITE(V37) {
  relay1Auto_state = param.asInt();
}
BLYNK_WRITE(V36) {
  relay2Auto_state = param.asInt();
}
BLYNK_WRITE(V39) {
  relay3Auto_state = param.asInt();
}
BLYNK_WRITE(V38) {
  relay4Auto_state = param.asInt();
}
BLYNK_WRITE(V35) {
  wallAuto_state = param.asInt();
}

BLYNK_WRITE(V6) {
  allRelay_state = HIGH;
  relay1_state = HIGH;
  relay2_state = HIGH;
  relay3_state = HIGH;
  relay4_state = HIGH;
  deskState = HIGH;

  Blynk.virtualWrite(V61, HIGH);
  delay(50);
  Blynk.virtualWrite(V62, HIGH);
  delay(50);
  Blynk.virtualWrite(V63, HIGH);
  delay(50);
  Blynk.virtualWrite(V64, HIGH);
  delay(50);
  Blynk.virtualWrite(V30, HIGH);

  Blynk.syncVirtual(V61);
  Blynk.syncVirtual(V62);
  Blynk.syncVirtual(V63);
  Blynk.syncVirtual(V64);
  Blynk.syncVirtual(V30);

}
