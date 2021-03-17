#include <U8glib.h>

#define oledGND 37
#define oledVCC 36





void oled_refresh(String selector);
void oled_graphics(String cmd);
void terminal_help();
void terminal_setup();
void update_table(String value);
