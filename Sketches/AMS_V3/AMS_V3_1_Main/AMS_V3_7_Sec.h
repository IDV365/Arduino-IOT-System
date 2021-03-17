#include <RGBLed.h>
RGBLed led(12, 13, 11, RGBLed::COMMON_CATHODE);
#define PIR1_pin 45
#define DOOR_pin A8
WidgetLED DOOR_led(21);
WidgetLED PIR1_led(24);

#define hallPin A8


void security_run();
int hall_return();
