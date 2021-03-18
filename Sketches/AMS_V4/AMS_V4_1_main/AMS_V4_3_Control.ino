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


void control_update() {
  bool input1 = Keypad_ask('5');
  if (input1 == LOW) {
    deskState = !deskState;
    digitalWrite(deskPin, deskState);
    Blynk.virtualWrite(V30, deskState);
    Blynk.syncVirtual(V30);
  }
}
