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
extern unsigned long threshold_ide_shutdown;
extern unsigned long threshold_ide_activating;
extern unsigned long threshold_ide_pausing;
extern unsigned long threshold_flp_activating;
extern unsigned long threshold_flp_deactivating;

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
                    threshold_ide_shutdown = EEPROM.read(i) * ONE_MINUTE;
                    break;

                case 4:
                    if (EEPROM.read(i) > 0) threshold_ide_activating = EEPROM.read(i) * 10;
                    else threshold_ide_activating = DEFAULT_IDE_ACTIVE;
                    break;

                case 5:
                    if (EEPROM.read(i) > 0) threshold_ide_pausing = EEPROM.read(i) * 10;
                    else threshold_ide_pausing = DEFAULT_IDE_PAUSE;
                    break;

                case 6:
                    if (EEPROM.read(i) > 0) threshold_flp_activating = EEPROM.read(i) * 10;
                    else threshold_flp_activating = DEFAULT_FLP_ACTIVATING;
                    break;

                case 7:
                    if (EEPROM.read(i) > 0) threshold_flp_deactivating = EEPROM.read(i) * 10;
                    else threshold_flp_deactivating = DEFAULT_FLP_DEACTIVATING;
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
                    threshold_ide_shutdown = DEFAULT_IDE_SHUTDOWN;
                    break;

                case 4:
                    threshold_ide_activating = DEFAULT_IDE_ACTIVE;
                    break;

                case 5:
                    threshold_ide_pausing = DEFAULT_IDE_PAUSE;
                    break;

                case 6:
                    threshold_flp_activating = DEFAULT_FLP_ACTIVATING;
                    break;

                case 7:
                    threshold_flp_deactivating = DEFAULT_FLP_DEACTIVATING;
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
                if (threshold_ide_shutdown == 0) EEPROM.update(i, 0);
                else EEPROM.update(i, threshold_ide_shutdown / ONE_MINUTE);
                break;

            case 4:
                if (threshold_ide_activating == 0) EEPROM.update(i, DEFAULT_IDE_ACTIVE / 10);
                else EEPROM.update(i, threshold_ide_activating / 10);
                break;

            case 5:
                if (threshold_ide_pausing == 0) EEPROM.update(i, DEFAULT_IDE_PAUSE / 10);
                else EEPROM.update(i, threshold_ide_pausing / 10);
                break;

            case 6:
                if (threshold_flp_activating == 0) EEPROM.update(i, DEFAULT_FLP_ACTIVATING / 10);
                else EEPROM.update(i, threshold_flp_activating / 10);
                break;

            case 7:
                if (threshold_flp_deactivating == 0) EEPROM.update(i, DEFAULT_FLP_DEACTIVATING / 10);
                else EEPROM.update(i, threshold_flp_deactivating / 10);
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