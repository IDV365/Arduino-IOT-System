
//Blynk

BLYNK_CONNECTED() {
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
  Blynk.syncVirtual(V30);
  Blynk.syncVirtual(V40);

}

BLYNK_WRITE(V25) {
  pirAlarmState = param.asInt();
}
BLYNK_WRITE(V28) {
  pir2AlarmState = param.asInt();
}
