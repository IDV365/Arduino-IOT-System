
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
  pir2AlarmState = param.asInt();
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
BLYNK_WRITE(V6) {
  allRelay_state != allRelay_state;
  relay1_state = allRelay_state;
  relay2_state = allRelay_state;
  relay3_state = allRelay_state;
  relay4_state = allRelay_state;
  deskState = allRelay_state;

  Blynk.virtualWrite(V61, relay1_state);
  delay(50);
  Blynk.virtualWrite(V62, relay2_state);
  delay(50);
  Blynk.virtualWrite(V63, relay3_state);
  delay(50);
  Blynk.virtualWrite(V64, relay4_state);
  delay(50);
  Blynk.virtualWrite(V30, deskState);

  Blynk.syncVirtual(V61);
  Blynk.syncVirtual(V62);
  Blynk.syncVirtual(V63);
  Blynk.syncVirtual(V64);
  Blynk.syncVirtual(V30);

}
