//LIGHTED CONTROLED BY PIR
void PIR2_control() {
  if (digitalRead(PIR2_pin) == LOW && digitalRead(relay1) == HIGH) {
    relay1_state = HIGH;
    digitalWrite(relay1, HIGH);
    Blynk.virtualWrite(V61, HIGH);
    Blynk.syncVirtual(V61);
    delay(50);

  }
  if (digitalRead(PIR2_pin) == LOW && digitalRead(relay2) == HIGH) {
    relay2_state = HIGH;
    digitalWrite(relay2, HIGH);
    Blynk.virtualWrite(V62, HIGH);
    Blynk.syncVirtual(V62);
    delay(50);

  }

  if (digitalRead(PIR2_pin) == LOW && digitalRead(relay3) == HIGH ) {  //&& pir2AlarmState == HIGH
    relay3_state = HIGH;
    digitalWrite(relay3, HIGH);
    Blynk.virtualWrite(V63, HIGH);
    Blynk.syncVirtual(V63);
    delay(50);

  }

  if (digitalRead(PIR2_pin) == LOW && digitalRead(relay4) == HIGH) {
    relay4_state = HIGH;
    digitalWrite(relay4, HIGH);
    Blynk.virtualWrite(V64, HIGH);
    Blynk.syncVirtual(V64);
    delay(50);

  }

  if (digitalRead(PIR2_pin) == LOW && digitalRead(deskPin) == HIGH) {
    deskState = LOW;
    digitalWrite(deskPin, LOW);
    Blynk.virtualWrite(V30, LOW);
    Blynk.syncVirtual(V30);
  }
}




//Buttons IRL
void buttons_setup() {
  pinMode(buttenPinEncoder, INPUT_PULLUP);
  pinMode(buttenPinBlackbutton, INPUT_PULLUP);
}

bool encoder_buttonState = false;
bool buttenPin_blackbutton = false;

void buttons_refrech() {
  encoder_buttonState = digitalRead(buttenPinEncoder);
  buttenPin_blackbutton = digitalRead(buttenPinBlackbutton);

  if (encoder_buttonState == HIGH) {
    oled_graphics("encoderButton");
  }
  else if (buttenPin_blackbutton == HIGH) {
    oled_graphics("blackButton");
  }

}


// KEYPAD
char Keypad_return() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    return customKey;
  }
}
bool Keypad_ask(char ask) {
  char customKey = customKeypad.getKey();
  if (customKey == ask) {
    return LOW;
  }
  else {
    return HIGH;
  }
}
#define deskPin 38
BLYNK_WRITE(V30) {
  deskState =  param.asInt();
  digitalWrite(deskPin, deskState);
}



//Main Button Loop
void control_update() {
  bool input1 = Keypad_ask('5');
  if (input1 == LOW) {
    deskState = !deskState;
    digitalWrite(deskPin, deskState);
    Blynk.virtualWrite(V30, deskState);
    Blynk.syncVirtual(V30);
  }
}




//ROTARYENCODER
int rotary_return() {
  static int lastPos = -1;
  encoder.tick();

  int newPos = encoder.getPosition() * ROTARYSTEPS;
  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } // if

  if (lastPos != newPos) {
    lastPos = newPos;
    return newPos;
  }
}
