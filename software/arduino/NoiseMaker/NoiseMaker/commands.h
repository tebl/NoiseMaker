#include <Arduino.h>

void commands_init();

void print_help();
void print_version();
void print_welcome();
void update_volume(uint8_t value);

bool handle_command(String command, String name, void (*function)());
void select_command(String command);
void echo_command(String command);
void echo_unknown(String command);
