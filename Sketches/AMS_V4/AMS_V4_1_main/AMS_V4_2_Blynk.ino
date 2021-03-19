
//Blynk

BLYNK_CONNECTED() {
  rtc.begin();
  RGB_flash("Blue", flashBrightness, flashTime);
  Blynk.syncVirtual(V30);
  Blynk.syncVirtual(V40);

}
