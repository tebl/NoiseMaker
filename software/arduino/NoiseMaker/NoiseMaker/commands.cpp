#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#include "constants.h"
#include "ansi.h"
#include "help.h"
#include "storage.h"

extern bool ansi_enabled;
extern uint8_t setting_volume;
extern DFRobotDFPlayerMini dfplayer;

void commands_init() {
}

void do_save_settings() {
  store_settings();
}

void do_scratch_settings() {
  clear_settings();
  ansi_error_ln(F("Cleared settings - please RESET device!"));
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

void print_volume() {
  ansi_notice();
  Serial.print(F("Volume set to "));
  Serial.println(setting_volume);
  ansi_default();
}

void update_volume(uint8_t value) {
  bool changed = false;
  if (setting_volume != value) {
    changed = true;
  }
  setting_volume = value;
  dfplayer.volume(value);
  if (changed) print_volume();

}

void volume_max() {
  update_volume(30);
}

void volume_high() {
  update_volume(25);
}

void volume_medium() {
  update_volume(20);
}

void volume_low() {
  update_volume(10);
}

/* Called when a recognized command has been recognized, but before the
* function is actually called.
*/
void echo_command(String command) {
  ansi_colour(COLOUR_CYAN);
  Serial.println("> "+ command);
  ansi_default();
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
  else if (handle_command(command, F("ansi test"), ansi_test));
  else if (handle_command(command, F("clear"), do_clear));
  else if (handle_command(command, F("help"), print_help));
  else if (handle_command(command, F("reload"), do_reload_settings));
  else if (handle_command(command, F("scratch"), do_scratch_settings));
  else if (handle_command(command, F("save"), do_save_settings));
  else if (handle_command(command, F("version"), print_version));
  else if (handle_command(command, F("volume"), print_volume));
  else if (handle_command(command, F("volume max"), volume_max));
  else if (handle_command(command, F("volume high"), volume_high));
  else if (handle_command(command, F("volume medium"), volume_medium));
  else if (handle_command(command, F("volume low"), volume_low));
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