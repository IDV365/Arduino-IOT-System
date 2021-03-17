#include <RotaryEncoder.h>
#include <keypad.h>

#define buttenPinEncoder 4
#define buttenPinBlackbutton 5

#define PIN_IN1 2
#define PIN_IN2 3
#define ROTARYSTEPS 2
#define ROTARYMIN 2
#define ROTARYMAX 6
RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void buttons_setup();
void buttons_refrech();
int rotary_return();
char Keypad_return();
bool Keypad_ask(char ask);
