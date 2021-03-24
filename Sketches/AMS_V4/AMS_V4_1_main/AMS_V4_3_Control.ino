//LIGHTED CONTROLED BY PIR
void PIR2_control_V2() {
  if (pir2AutoOff_state == HIGH && digitalRead(PIR2_pin) == LOW) {
    
    if (relay1Auto_state == true && digitalRead(relay1) == LOW){
      relay1_state = HIGH;
      digitalWrite(relay1, HIGH);
      Blynk.virtualWrite(V61, HIGH);
      Blynk.syncVirtual(V61);
      delay(50);
    }
    
    if (relay2Auto_state == true && digitalRead(relay2) == LOW) {
      relay2_state = HIGH;
      digitalWrite(relay2, HIGH);
      Blynk.virtualWrite(V62, HIGH);
      Blynk.syncVirtual(V62);
      delay(50);
    }

    if (relay3Auto_state == true && digitalRead(relay3) == LOW) {
      relay3_state = HIGH;
      digitalWrite(relay3, HIGH);
      Blynk.virtualWrite(V63, HIGH);
      Blynk.syncVirtual(V63);
      delay(50);
    }

    if (relay4Auto_state == true && digitalRead(relay4) == LOW) {
      relay4_state = HIGH;
      digitalWrite(relay4, HIGH);
      Blynk.virtualWrite(V64, HIGH);
      Blynk.syncVirtual(V64);
      delay(50);
    }

    if (wallAuto_state == true && digitalRead(deskPin) == LOW) {
      deskState = LOW;
      digitalWrite(deskPin, LOW);
      Blynk.virtualWrite(V30, LOW);
      Blynk.syncVirtual(V30);
    }
  }

  
  if (pir2AutoOn_state == HIGH && digitalRead(PIR2_pin) == HIGH) {
    
    if (relay1Auto_state == true && digitalRead(relay1) == HIGH) {
      relay1_state = LOW;
      digitalWrite(relay1, LOW);
      Blynk.virtualWrite(V61, LOW);
      Blynk.syncVirtual(V61);
      delay(50);
    }
    if (relay2Auto_state == true && digitalRead(relay2) == HIGH) {
      relay2_state = LOW;
      digitalWrite(relay2, LOW);
      Blynk.virtualWrite(V62, LOW);
      Blynk.syncVirtual(V62);
      delay(50);
    }

    if (relay3Auto_state == true && digitalRead(relay3) == HIGH) {
      relay3_state = LOW;
      digitalWrite(relay3, LOW);
      Blynk.virtualWrite(V63, LOW);
      Blynk.syncVirtual(V63);
      delay(50);
    }

    if (relay4Auto_state == true && digitalRead(relay4) == HIGH) {
      relay4_state = LOW;
      digitalWrite(relay4, LOW);
      Blynk.virtualWrite(V64, LOW);
      Blynk.syncVirtual(V64);
      delay(50);
    }

    if (wallAuto_state == true && digitalRead(deskPin) == LOW) {
      deskState = HIGH;
      digitalWrite(deskPin, HIGH);
      Blynk.virtualWrite(V30, HIGH);
      Blynk.syncVirtual(V30);
    }
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
    return HIGH;
  }
  else {
    return HIGH;
  }
}


//Main Button Loop
void key_control() {
  char key_input = Keypad_return();

  if (key_input == '5') {
    relay1_state = !relay1_state;
    digitalWrite(relay1, relay1_state);
    Blynk.virtualWrite(V61, relay1_state);
    Blynk.syncVirtual(V61);
  }
  else if (key_input == '6') {

    relay2_state = !relay2_state;
    digitalWrite(relay2, relay2_state);
    Blynk.virtualWrite(V62, relay2_state);
    Blynk.syncVirtual(V62);
  }
  else if (key_input == '7') {
    relay3_state = !relay3_state;
    digitalWrite(relay3, relay3_state);
    Blynk.virtualWrite(V63, relay3_state);
    Blynk.syncVirtual(V63);
  }
  else if (key_input == '8') {
    relay4_state = !relay4_state;
    digitalWrite(relay4, relay4_state);
    Blynk.virtualWrite(V64, relay4_state);
    Blynk.syncVirtual(V64);
  }
  else if (key_input == '9') {
    deskState = !deskState;
    digitalWrite(deskPin, deskState);
    Blynk.virtualWrite(V30, deskState);
    Blynk.syncVirtual(V30);
  }
  else if (key_input == '1') {          //everything off
    relay1_state = HIGH;
    relay2_state = HIGH;
    relay3_state = HIGH;
    relay4_state = HIGH;
    deskState = LOW;

    Blynk.virtualWrite(V61, HIGH);
    Blynk.virtualWrite(V62, HIGH);
    Blynk.virtualWrite(V63, HIGH);
    Blynk.virtualWrite(V64, HIGH);
    Blynk.virtualWrite(V30, LOW);

    Blynk.syncVirtual(V61);
    Blynk.syncVirtual(V62);
    Blynk.syncVirtual(V63);
    Blynk.syncVirtual(V64);
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
