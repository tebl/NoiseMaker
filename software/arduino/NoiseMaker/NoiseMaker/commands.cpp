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

bool parser_error(String command, String error) {
  ansi_error();
  Serial.print("? " + command);
  Serial.print(" (");
  Serial.print(error);
  Serial.println(")");
  ansi_default();

  return false;
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

void print_version() {
  Serial.print(F(APP_TITLE));
  Serial.print(' ');
  Serial.println(F(APP_VERSION));
}

void print_welcome() {
  ansi_clear();
  ansi_highlight();
  print_version();
  ansi_default();
}

int8_t volume_from_value(int8_t value) {
  if (VOLUME_2 == value) return 2;
  if (VOLUME_3 == value) return 3;
  if (VOLUME_4 == value) return 4;
  if (VOLUME_5 == value) return 5;
  if (VOLUME_6 == value) return 6;
  if (VOLUME_7 == value) return 7;
  if (VOLUME_8 == value) return 8;
  return 1;
}

int8_t volume_to_value(int8_t level) {
  switch (level) {
    case 2: return VOLUME_2;
    case 3: return VOLUME_3;
    case 4: return VOLUME_4;
    case 5: return VOLUME_5;
    case 6: return VOLUME_6;
    case 7: return VOLUME_7;
    case 8: return VOLUME_8;
    default:
      return VOLUME_1;
  }
}

void print_volume() {
  ansi_notice();
  Serial.print(F("Volume set to "));
  Serial.println(volume_from_value(setting_volume));
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
  update_volume(
    volume_to_value(
      volume_from_value(setting_volume) + 1
    )
  );
  store_settings();
}

void volume_down() {  
  update_volume(
    volume_to_value(
      volume_from_value(setting_volume) - 1
    )
  );
  store_settings();
}

bool handle_volume(String c) {
  if (c.length() != 8) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  uint8_t new_value = c[7] - '0';
  if (new_value < 1 || new_value > 8) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  update_volume(volume_to_value(new_value));
  return true;
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

unsigned long get_threshold_value(char digit1, char digit2) {
  return ((digit1 - '0') * 16 + (digit2 - '0'));
}

bool handle_flp_activating(String c) {
  if (c.length() != 17) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  threshold_flp_activating = get_threshold_value(c[15], c[16]) * 10;
  print_threshold();
  return true;
}

bool handle_flp_deactivating(String c) {
  if (c.length() != 19) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  threshold_flp_deactivating = get_threshold_value(c[17], c[18]) * 10;
  print_threshold();
  return true;
}

bool handle_ide_activating(String c) {
  if (c.length() != 17) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  threshold_ide_activating = get_threshold_value(c[15], c[16]) * 10;
  print_threshold();
  return true;
}


bool handle_ide_pausing(String c) {
  if (c.length() != 14) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  threshold_ide_pausing = get_threshold_value(c[12], c[13]) * 10;
  print_threshold();
  return true;
}


bool handle_ide_shutdown(String c) {
  if (c.length() != 15) return parser_error(c, (__FlashStringHelper*) STR_ERROR_ARGUMENT);
  echo_command(c);
  threshold_ide_shutdown = get_threshold_value(c[13], c[14]) * ONE_MINUTE;
  print_threshold();
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
    case 1:   Serial.print(F("Amiga Floppy disk")); break;
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
#if defined(__AVR_ATmega328P__)
       if (handle_command(command, F("ansi"), ansi_status));
  else if (handle_command(command, F("ansi on"), ansi_on));
  else if (handle_command(command, F("ansi off"), ansi_off));
  else if (handle_command(command, F("ansi test"), ansi_test));
  else if (handle_command(command, F("clear"), do_clear));
  else if (handle_command(command, F("help"), print_help));
  else if (handle_command(command, F("dump"), dump_settings));
  else if (handle_command(command, F("profile"), print_profile));
#else
       if (handle_command(command, F("profile"), print_profile));
#endif
  else if (command.startsWith(F("profile "))) handle_profile(command);
  else if (handle_command(command, F("reload"), do_reload_settings));
  else if (handle_command(command, F("scratch"), do_scratch_settings));
  else if (handle_command(command, F("save"), do_save_settings));
  else if (handle_command(command, F("threshold"), print_threshold));
// #if defined(__AVR_ATmega328P__)
  else if (command.startsWith(F("ide-activating "))) handle_ide_activating(command);
  else if (command.startsWith(F("ide-pausing "))) handle_ide_pausing(command);
  else if (command.startsWith(F("ide-shutdown "))) handle_ide_shutdown(command);
  else if (command.startsWith(F("flp-activating "))) handle_flp_activating(command);
  else if (command.startsWith(F("flp-deactivating "))) handle_flp_deactivating(command);
// #endif
  else if (handle_command(command, F("version"), print_version));
#if defined(__AVR_ATmega328P__)
  else if (handle_command(command, F("volume"), print_volume));
  else if (handle_command(command, F("volume+"), volume_up));
  else if (handle_command(command, F("volume-"), volume_down));
  else if (command.startsWith(F("volume "))) handle_volume(command);
#endif
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