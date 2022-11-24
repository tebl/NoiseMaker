#include <Arduino.h>
#include <EEPROM.h>
#include "constants.h"
#include "settings.h"
#include "ansi.h"
#include "commands.h"

#define STORAGE_LENGTH 32
#define STORAGE_BYTES (STORAGE_LENGTH - 1)
#define STORAGE_CHECKSUM STORAGE_BYTES

extern bool ansi_enabled;
extern uint8_t setting_volume;
extern uint8_t profile;
extern unsigned long threshold_shutdown;

int storage_checksum() {
    int x = 0;
    for(int i = 0; i < STORAGE_BYTES; i++) {
        x += EEPROM.read(i);
    }
    x = x % 256;
    x = ~x;
    x = x + 1;
    x = x & 0xFF;
    return x;
}

bool checksum_passes() {
    return EEPROM.read(STORAGE_CHECKSUM) == storage_checksum();
}

void clear_settings() {
    int value = (EEPROM.read(STORAGE_CHECKSUM) + 1) % 256;
    EEPROM.update(STORAGE_CHECKSUM, value);
}

void restore_settings() {
    Serial.println(F("Restore settings ... "));
    if (checksum_passes()) {
        for (int i = 0; i < STORAGE_BYTES; i++) {
            switch (i) {
                case 0:
                    ansi_enabled = EEPROM.read(i) == 1;
                    break;

                case 1:
                    update_volume(EEPROM.read(i));
                    break;

                case 2:
                    update_profile(EEPROM.read(i));
                    break;
                
                case 3:
                    threshold_shutdown = EEPROM.read(i) * ONE_MINUTE;
                    break;

                default:
                    break;
            }
        }
        ansi_highlight_ln((__FlashStringHelper*) STR_DONE);
    } else {
        ansi_notice_ln(F("... by loading defaults ... "));
        for (int i = 0; i < STORAGE_BYTES; i++) {
            switch (i) {
                case 0:
                    ansi_enabled = DEFAULT_ANSI;
                    break;

                case 1:
                    update_volume(DEFAULT_VOLUME);
                    break;

                case 2:
                    update_profile(DEFAULT_PROFILE);
                    break;
                
                case 3:
                    threshold_shutdown = DEFAULT_SHUTDOWN;
                    break;

                default:
                    break;
            }
        }
        ansi_highlight_ln((__FlashStringHelper*) STR_DONE);
    }
}

void store_settings() {
    Serial.print(F("Storing settings ... "));
    for (int i = 0; i < STORAGE_BYTES; i++) {
        switch (i) {
            case 0:
                EEPROM.update(i, ansi_enabled ? 1 : 0);
                break;
            
            case 1:
                EEPROM.update(i, setting_volume);
                break;

            case 2:
                EEPROM.update(i, profile);
                break;

            case 3:
                if (threshold_shutdown == 0) EEPROM.update(i, 0);
                else EEPROM.update(i, threshold_shutdown / ONE_MINUTE);
                break;
            
            default:
                EEPROM.update(i, 0);
                break;
        }
    }
    EEPROM.update(STORAGE_CHECKSUM, storage_checksum());
    ansi_highlight_ln((__FlashStringHelper*) STR_DONE);
}

void dump_settings() {
    Serial.print(F("Checksum... "));
    if (checksum_passes()) {
        ansi_highlight_ln(F("OK"));

        for (int i = 0; i < STORAGE_BYTES; i++) {
            if (i < 100) Serial.print(' ');
            if (i < 10) Serial.print(' ');
            Serial.print(i);
            Serial.print(": ");

            uint8_t value = EEPROM.read(i); 
            if (value < 100) Serial.print(' ');
            if (value < 10) Serial.print(' ');
            Serial.println(value);
        }
    }
    else ansi_error_ln(F("ERROR"));
}