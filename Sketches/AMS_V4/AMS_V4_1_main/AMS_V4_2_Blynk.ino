
//Blynk

BLYNK_CONNECTED() {
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
  Blynk.syncVirtual(V30);
  Blynk.syncVirtual(V40);
  Blynk.syncVirtual(V61);
  Blynk.syncVirtual(V62);
  Blynk.syncVirtual(V63);
  Blynk.syncVirtual(V64);


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
