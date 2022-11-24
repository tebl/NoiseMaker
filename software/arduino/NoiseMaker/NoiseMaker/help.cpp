#include <Arduino.h>
#include "ansi.h"
#include "constants.h"

/*
* Calculates the length of a string that has been stored in Flash memory
* instead of RAM, normally defined using the Arduino F() macro.
*/
unsigned int flash_length(const __FlashStringHelper *string) {
  const char *ptr = (const char *) string;
  int size = 0;
  while (pgm_read_byte_near(ptr++)) {
    size++;
  }
  return size;
}

/*
* Arduino lacks a way to pad strings, so then I guess we're doing it the 
* ridiculously hard way instead of leaving things somewhat sensible. Feature
* creep is a real thing, but doing this for fun, so let's just live with it!
*/
void help_command(const __FlashStringHelper *command = nullptr, 
                  const __FlashStringHelper *description = nullptr,
                  const __FlashStringHelper *parameter = nullptr,
                  const __FlashStringHelper *switch_ref = nullptr) {
  int size = 0;
  int position = 0;
  if (command != nullptr) {
    size = flash_length(command);
    ansi_notice(command);
  }

  if (parameter != nullptr) {
    size += flash_length(parameter) + 1;
    Serial.print(' ');
    ansi_colour(parameter, COLOUR_WHITE);
  }
  for (int i = size; i < 20; i++) Serial.print(' ');
  position = 20;

  if (description != nullptr) {
    ansi_colour(description, COLOUR_WHITE);
    position += flash_length(description);
  }

  if (switch_ref != nullptr) {
    size = TERMINAL_COLS - flash_length(switch_ref);
    for (int i = position; i < size; i++) Serial.print(' ');
    ansi_colour(switch_ref, COLOUR_MAGENTA);
  }

  Serial.println();
}

/*
* Run the command associated with the serial command given, compared against
* all known commands (depending on the currently selected command set).
*/
void print_help() {
  ansi_colour_ln(F("Commands supported:"), COLOUR_MAGENTA);
  help_command(F("ansi on"),            F("Enable ANSI terminal code usage"));
  help_command(F("ansi off"),           F("Disable ANSI terminal code usage"));
  help_command(F("ansi test"),          F("Test ANSI terminal codes on terminal"));
  help_command(F("clear"),              F("Clear screen"));
  help_command(F("dump"),               F("Show raw contents of EEPROM"));  
  help_command(F("profile"),            F("Display audio profile"));
  help_command(F("profile <number>"),   F("Set audio profile (0-8)"));
  help_command(F("reload"),             F("Reload settings from EEPROM"));  
  help_command(F("save"),               F("Save current settings to EEPROM"));
  help_command(F("scratch"),            F("Clear settings in EEPROM (reset afterwards)"));
  help_command(F("version"),            F("Prints firmware version"));
  help_command(F("volume"),             F("Prints current volume"));
  help_command(F("volume <setting>"),   F("Set volume (1-8)"));
}
