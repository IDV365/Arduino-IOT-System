#include "AMS_V3_4_Input.h"

//BUTTONS
void buttons_setup() {
  pinMode(buttenPinEncoder, INPUT_PULLUP);
  pinMode(buttenPinBlackbutton, INPUT_PULLUP);
}


void buttons_refrech() {
  static bool encoder_buttonState = false;
  static bool buttenPin_blackbutton = false;
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
  static const byte ROWS = 4;
  static const byte COLS = 4;
  static byte rowPins[ROWS] = {29, 27, 25, 23};
  static byte colPins[COLS] = {22, 24, 26, 28};
  static char hexaKeys[ROWS][COLS] = {

    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'},
    {'9', 'A', 'B', 'C'},
    {'D', 'E', 'F', 'G'}
  };
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
