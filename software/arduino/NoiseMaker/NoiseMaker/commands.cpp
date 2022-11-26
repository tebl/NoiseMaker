#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include "constants.h"
#include "ansi.h"
#include "help.h"
#include "storage.h"

extern uint8_t mode;
extern bool ansi_enabled;
extern uint8_t setting_volume;
extern uint8_t profile;
extern unsigned long threshold_ide_shutdown;
extern unsigned long threshold_ide_activating;
extern unsigned long threshold_ide_pausing;
extern unsigned long threshold_flp_activating;
extern unsigned long threshold_flp_deactivating;

extern DFRobotDFPlayerMini dfplayer;

/* Called when a recognized command has been recognized, but before the
* function is actually called.
*/
void echo_command(String command) {
  ansi_colour(COLOUR_CYAN);
  Serial.println("> "+ command);
  ansi_default();
}

void do_save_settings() {
  store_settings();
}

void do_scratch_settings() {
  clear_settings();
  ansi_notice_ln(F("Settings cleared!"));
  ansi_error_ln(F("RESET device."));
}

void do_reload_settings() {
  restore_settings();
}

void print_value(const __FlashStringHelper *string, unsigned long value) {
  Serial.print(' ');
  Serial.print(' ');
  Serial.print(string);
  Serial.print(F(" = \""));
  ansi_notice();
  Serial.print(value);
  ansi_default();
  Serial.println(F("\""));
}

void print_threshold() {
  Serial.println(F("IDE:"));
  print_value(F("activating  "), threshold_ide_activating);
  print_value(F("pausing     "), threshold_ide_pausing);
  print_value(F("shutdown    "), threshold_ide_shutdown);
  Serial.println(F("Floppy:"));
  print_value(F("activating  "), threshold_flp_activating);
  print_value(F("deactivating"), threshold_flp_deactivating);
}

void print_version() {
  Serial.print(F(APP_TITLE));
  Serial.print(' ');
  Serial.println(F(APP_VERSION));
}

void print_volume() {
  ansi_notice();
  Serial.print(F("Volume set to "));
  Serial.println(setting_volume);
  ansi_default();
}

void print_welcome() {
  ansi_clear();
  ansi_highlight();
  print_version();
  ansi_default();
}

void update_volume(int8_t value) {
  bool changed = false;
  if (value > 31) value = 31;
  if (value < 10) value = 10;
  if (setting_volume != value) {
    changed = true;
  }
  setting_volume = value;
  dfplayer.volume(value);
  if (changed) print_volume();
}

void volume_up() {
  update_volume(setting_volume + 4);
  store_settings();
}

void volume_down() {  
  update_volume(setting_volume - 4);
  store_settings();
}

bool parser_error(String command, String error) {
  ansi_error();
  Serial.print("? " + command);
  Serial.print(" (");
  Serial.print(error);
  Serial.println(")");
  ansi_default();

  return false;
}

bool handle_volume(String c) {
  if (c.length() != 8) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  uint8_t new_value = c[7] - '0';
  if (new_value < 1 || new_value > 8) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  switch (new_value) {
    case 2: update_volume(15); break; 
    case 3: update_volume(20); break; 
    case 4: update_volume(22); break; 
    case 5: update_volume(24); break; 
    case 6: update_volume(26); break; 
    case 7: update_volume(28); break; 
    case 8: update_volume(31); break;
    default:
      update_volume(10); break;
  }
  return true;
}

void print_profile() {
  ansi_notice();
  Serial.print(F("Profile set to "));
  Serial.print(profile);

#if defined(__AVR_ATmega328P__)
  Serial.print(' ');
  Serial.print('(');

  uint8_t dirnum = profile;
  if (mode == MODE_IDE) dirnum += OFFSET_IDE;
  else dirnum += OFFSET_FLOPPY;
  switch (dirnum) {
    case 1:   Serial.print(F("Floppy disk")); break;
    case 10:  Serial.print(F("IBM Deskstar 22GXP 7200")); break;
    case 11:  Serial.print(F("WD WD800BB 7200")); break;
    case 12:  Serial.print(F("Seagate Medalist ST34321A 5400")); break;
    case 13:  Serial.print(F("IBM UltraStar ES 5400")); break;
    case 14:  Serial.print(F("Maxtor Atlas 10K SCSI")); break;
    default:  Serial.print(F("Unknown profile")); break;
  }
  Serial.print(')');
#endif

  Serial.println();
  ansi_default();
}

void update_profile(int8_t value) {
  bool changed = false;
  if (setting_volume != value) {
    changed = true;
  }
  profile = value;
  if (changed) print_profile();
}

bool handle_profile(String c) {
  if (c.length() != 9) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  uint8_t new_value = c[8] - '0';
  if (new_value < 0 || new_value > 8) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  update_profile(new_value);
  return true;
}

/* Called when the entered command has not been recognized, we don't know
* what to do next so we'll just print it as an error instead.
*/
void echo_unknown(String command) {
  ansi_error();
  Serial.println("? " + command);
  ansi_default();
}

/* Clear the serial terminal screen, but note that this won't actually do
* anything unless ANSI terminal codes are supported by the client and
* have not been explicitly disabled. Does a second echo of the command
* as the first one will disappear upon execution.
*/
void do_clear() {
  ansi_clear();
  if (ansi_enabled) echo_command(F("clear"));
}

/*
* Handle serial commands, mainly just matches the name and if it does the
* supplied function is run. Recognized commands are echoed back to the user.
*/
bool handle_command(String command, String name, void (*function)(), bool suppress_echo = false) {
  if (command == name) {
    echo_command(command);
    (*function)();
    return true;
  }
  return false;
}

void select_command_main(String command) {
       if (handle_command(command, F("ansi"), ansi_status));
  else if (handle_command(command, F("ansi on"), ansi_on));
  else if (handle_command(command, F("ansi off"), ansi_off));
#if defined(__AVR_ATmega328P__)
  else if (handle_command(command, F("ansi test"), ansi_test));
  else if (handle_command(command, F("clear"), do_clear));
  else if (handle_command(command, F("help"), print_help));
#endif
  else if (handle_command(command, F("dump"), dump_settings));
  else if (handle_command(command, F("profile"), print_profile));
  else if (command.startsWith(F("profile "))) handle_profile(command);
  else if (handle_command(command, F("reload"), do_reload_settings));
  else if (handle_command(command, F("scratch"), do_scratch_settings));
  else if (handle_command(command, F("save"), do_save_settings));
// #if defined(__AVR_ATmega328P__)
  else if (handle_command(command, F("threshold"), print_threshold));
// #endif
  else if (handle_command(command, F("version"), print_version));
// #if defined(__AVR_ATmega328P__)
  else if (handle_command(command, F("volume"), print_volume));
  else if (command.startsWith(F("volume "))) handle_volume(command);
// #endif
  else {
    echo_unknown(command);
  }
}

/*
* Run the command associated with the serial command given, compared against
* all known commands (depending on the currently selected command set).
*/
void select_command(String command) {
  select_command_main(command);
}