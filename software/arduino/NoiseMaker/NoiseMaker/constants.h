#pragma once

/* Magic numbers */
#define BAUD_RATE_115200 115200
#define BAUD_RATE_38400 38400
#define BAUD_RATE_19200 19200
#define BAUD_RATE_9600 9600
#define BAUD_RATE_4800 4800
#define BAUD_RATE BAUD_RATE_115200

#define TERMINAL_COLS 80

#define MODE_IDE 0
#define MODE_FLOPPY 1

#define STATE_INIT 0
#define STATE_FLP_IDLE 1
#define STATE_FLP_SPINNING 2
#define STATE_FLP_ACTIVE 3

#define STATE_IDE_IDLE 10
#define STATE_IDE_ACTIVE 11
#define STATE_IDE_PAUSED 12

#define SOUND_IDE_STARTUP 1
#define SOUND_IDE_ACTIVE 2
#define SOUND_IDE_SHUTDOWN 3
#define SOUND_FLP_STARTUP 1
#define SOUND_FLP_SPIN 2
#define SOUND_FLP_SNATCH 3
#define SOUND_FLP_CLICK 4

#define ONE_MINUTE 60000L
#define TEN_MINUTES 600000L
#define FIFTEEN_MINUTES 900000L

#define OFFSET_FLOPPY 1
#define OFFSET_IDE 10

/* Pin definitions */
#define DFPlayer_TX 11
#define DFPlayer_RX 10
#define DFPlayer_BUSY 12
#define PIN_TEST A0
#define PIN_VOL_UP A1
#define PIN_VOL_DOWN A2
#define PIN_MODE_SEL A5
#define PIN_ARD_P2 2
#define PIN_ARD_P3 3

#define PIN_IDE_ACTIVE PIN_ARD_P2
#define PIN_FLP_DRIVE_SEL PIN_ARD_P2
#define PIN_FLP_STEP PIN_ARD_P3
#define PIN_FLP_DISK_CHANGE 5
#define PIN_FLP_MOTOR_EN 6
#define PIN_LED LED_BUILTIN

/* Volume values */
#define VOLUME_1 10
#define VOLUME_2 15
#define VOLUME_3 20
#define VOLUME_4 22
#define VOLUME_5 24
#define VOLUME_6 26
#define VOLUME_7 28
#define VOLUME_8 31

/* Strings for reuse */
#define APP_TITLE "NoiseMaker"
#define APP_VERSION "0.1"
const char STR_DONE[] PROGMEM  = "done!";
const char STR_ERROR_ARGUMENT[] PROGMEM = "argument format";
