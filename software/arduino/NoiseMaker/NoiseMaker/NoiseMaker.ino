#include <Arduino.h>
#include <ezButton.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "constants.h"
#include "settings.h"
#include "debug.h"
#include "serial_console.h"
#include "commands.h"
#include "ansi.h"
#include "storage.h"

bool ansi_enabled = DEFAULT_ANSI;
uint8_t setting_volume = DEFAULT_VOLUME;
uint8_t mode = MODE_FLOPPY;
uint8_t state = STATE_INIT;
uint8_t profile = DEFAULT_PROFILE;
unsigned long threshold_ide_shutdown = DEFAULT_IDE_SHUTDOWN;
unsigned long threshold_ide_activating = DEFAULT_IDE_ACTIVE;
unsigned long threshold_ide_pausing = DEFAULT_IDE_PAUSE;
unsigned long threshold_flp_activating = DEFAULT_FLP_ACTIVATING;
unsigned long threshold_flp_deactivating = DEFAULT_FLP_DEACTIVATING;

SoftwareSerial dfplayer_serial(DFPlayer_RX, DFPlayer_TX);
DFRobotDFPlayerMini dfplayer;
ezButton vol_up(PIN_VOL_UP);
ezButton vol_down(PIN_VOL_DOWN);

volatile unsigned long last_activity = 0;
bool last_motor_on = false;
uint8_t last_error;
bool replay = false;

void play_flp_startup() {
  dfplayer.playFolder(OFFSET_FLOPPY + profile, SOUND_FLP_STARTUP);
}

void play_flp_spin() {
  dfplayer.playFolder(OFFSET_FLOPPY + profile, SOUND_FLP_SPIN);
}

void play_flp_snatch() {
  dfplayer.playFolder(OFFSET_FLOPPY + profile, SOUND_FLP_SNATCH);
}

void play_flp_click() {
  dfplayer.advertise(OFFSET_FLOPPY + profile);
}

void flp_interrupt_step() {
  // if (digitalRead(PIN_FLP_DRIVE_SEL) == LOW) {
    last_activity = millis();
  // }
}

void setup_floppy() {
  uint8_t mode = INPUT;
  #ifdef DEBUG_OFFLINE
    mode = INPUT_PULLUP;
  #endif
  pinMode(PIN_FLP_DRIVE_SEL, mode);
  pinMode(PIN_FLP_STEP, mode);
  pinMode(PIN_FLP_DISK_CHANGE, mode);
  pinMode(PIN_FLP_MOTOR_EN, mode);

  play_flp_startup();
  attachInterrupt(digitalPinToInterrupt(PIN_FLP_STEP), flp_interrupt_step, FALLING);
}

void play_ide_startup() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_STARTUP);
}

void play_ide_active() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_ACTIVE);
}

void play_ide_shutdown() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_SHUTDOWN);
}

void ide_interrupt() {
  last_activity = millis();
}

void setup_ide() {
  uint8_t mode = INPUT;
  #ifdef DEBUG_OFFLINE
    mode = INPUT_PULLUP;
  #endif
  pinMode(PIN_IDE_ACTIVE, mode);

  play_ide_startup();
  attachInterrupt(digitalPinToInterrupt(PIN_IDE_ACTIVE), ide_interrupt, FALLING);
}

void loop_floppy() {
  switch (state) {
    /* Waiting for startup sound to finish */
    case STATE_INIT:
      while (dfplayer.available()) {
        last_error = dfplayer.readType(); 
        if (last_error == DFPlayerPlayFinished) {
          delay(100);
          DEBUG_PRINTLN(F("set idle"));
          state = STATE_FLP_IDLE;
        } else unknown_error(last_error, dfplayer.read());
      }
      break;

    /* Waiting for activity */
    case STATE_FLP_IDLE:
      while (digitalRead(DFPlayer_BUSY) == LOW) DEBUG_SPINLOCK('-');
      if (digitalRead(PIN_FLP_MOTOR_EN) == LOW) {
        DEBUG_PRINTLN(F("motor on"));
        state = STATE_FLP_SPINNING;
        play_flp_spin();
      }
      break;
    
    /* Motor is spinning, wait for steps */
    case STATE_FLP_SPINNING:
      replay = false;
      if (digitalRead(PIN_FLP_MOTOR_EN) == HIGH) {
        DEBUG_PRINTLN(F("motor off"));
        state = STATE_FLP_IDLE;
        dfplayer.stop();
        while (digitalRead(DFPlayer_BUSY) == LOW) DEBUG_SPINLOCK('.');
      } else {
        while (dfplayer.available()) {
          last_error = dfplayer.readType(); 
          if (last_error == DFPlayerPlayFinished) {
            replay = true;
          } else unknown_error(last_error, dfplayer.read());
        }

        if (replay) {
            DEBUG_PRINTLN(F("replay spin"));
            play_flp_spin();
            delay(100);
            while (digitalRead(DFPlayer_BUSY) == HIGH) DEBUG_SPINLOCK('*');;
        } else {
          if (last_activity > 0 && ((millis() - last_activity) < threshold_flp_activating)) {
            DEBUG_PRINTLN(F("activating"));
            state = STATE_FLP_ACTIVE;
            play_flp_click();
            while (digitalRead(DFPlayer_BUSY) == HIGH) DEBUG_SPINLOCK('+');;
          }
        }
      }
      break;
    
    /* Motor is on, steps recently been taken */
    case STATE_FLP_ACTIVE:
      replay = false;
      if ((millis() - last_activity) > threshold_flp_deactivating) {
        DEBUG_PRINTLN(F("deactivating"));
        state = STATE_FLP_SPINNING;
        dfplayer.stopAdvertise();
        delay(200);
      } else {
        while (dfplayer.available()) {
          last_error = dfplayer.readType(); 
          if (last_error == DFPlayerPlayFinished) {
            replay = true;
          } else unknown_error(last_error, dfplayer.read());
        }

        if (replay) {
            DEBUG_PRINTLN(F("replay click"));
            play_flp_click();
            delay(200);
            while (digitalRead(DFPlayer_BUSY) == HIGH) DEBUG_SPINLOCK('/');;
        }
      }
      break;
  }
}

void setup() {
  dfplayer_serial.begin(BAUD_RATE_9600);
  process_serial_init();
  pinMode(PIN_TEST, INPUT_PULLUP);
  vol_up.setDebounceTime(50);
  vol_down.setDebounceTime(50);
  pinMode(PIN_MODE_SEL, INPUT_PULLUP);
  digitalWrite(PIN_LED, LOW);
  pinMode(PIN_LED, OUTPUT);
  pinMode(DFPlayer_BUSY, INPUT);

  ansi_default();
  Serial.print(F("Initializing "));
  ansi_highlight();
  print_version();
  ansi_default();

  Serial.print(F("Initializing DFPlayer ... "));
  if (!dfplayer.begin(dfplayer_serial, true, false)) {
    ansi_error();
    Serial.println(F("failed!"));
    Serial.println(F("Check SD-card!"));
    while(true) delay(0);
  };
  ansi_highlight_ln(F("done!"));

  Serial.print(F("Configured mode is... "));
  if (digitalRead(PIN_MODE_SEL) == LOW) {
    mode = MODE_FLOPPY;
    ansi_highlight_ln(F("floppy!"));
  } else {
    mode = MODE_IDE;
    ansi_highlight_ln(F("IDE!"));
  }

  restore_settings();

  if (mode == MODE_FLOPPY) setup_floppy();
  else setup_ide();
}

void loop_ide() {
  switch (state) {
    /* Waiting for startup sound to finish */
    case STATE_INIT:
      while (dfplayer.available()) {
        last_error = dfplayer.readType(); 
        if (last_error == DFPlayerPlayFinished) {
          delay(100);
          DEBUG_PRINTLN(F("set idle"));
          state = STATE_IDE_IDLE;
        } else unknown_error(last_error, dfplayer.read());
      }
      break;

    /* Waiting for activity */
    case STATE_IDE_IDLE:
      while (digitalRead(DFPlayer_BUSY) == LOW);
      if (last_activity > 0 && ((millis() - last_activity) < threshold_ide_activating)) {
        DEBUG_PRINTLN(F("activating"));
        state = STATE_IDE_ACTIVE;
        play_ide_active();
      }
      break;

    case STATE_IDE_ACTIVE:
      /* Check for activity timeout */
      replay = false;
      if ((millis() - last_activity) > threshold_ide_pausing) {
        DEBUG_PRINTLN(F("pausing"));
        state = STATE_IDE_PAUSED;
        dfplayer.pause();
        while (digitalRead(DFPlayer_BUSY) == LOW);
      } else {
        while (dfplayer.available()) {
          last_error = dfplayer.readType(); 
          if (last_error == DFPlayerPlayFinished) {
            delay(100);
            replay = true;
          } else unknown_error(last_error, dfplayer.read());
        }

        if (replay) {
            DEBUG_PRINTLN(F("replay"));
            play_ide_active();
            while (digitalRead(DFPlayer_BUSY) == HIGH);
        }
      }
      break;

    case STATE_IDE_PAUSED:
      if (last_activity > 0) {
        /* Check if we now see activity again */
        if ((millis() - last_activity) < threshold_ide_activating) {
          DEBUG_PRINTLN(F("resuming"));
          state = STATE_IDE_ACTIVE;
          dfplayer.start();
          while (digitalRead(DFPlayer_BUSY) == HIGH);
        }

        /* Check for shutdown. We can't actually know this due to only seeing
         * HDD-busy instead of the registers, so we just play the sound make
         * sure that we're ready to continue doing activity sounds right after
         * (instead of doing another startup).
         */
        if (threshold_ide_shutdown > 0 && (millis() - last_activity) > threshold_ide_shutdown) {
          DEBUG_PRINTLN(F("shutdown"));
          play_ide_shutdown();
          state = STATE_INIT;
          while (digitalRead(DFPlayer_BUSY) == HIGH);
        }
      }
      break;

    default:
      break;
  }
}

void unknown_error(uint8_t type, int value) {
  #if defined(__AVR_ATmega328P__)
  switch (type) {
    case TimeOut:
      ansi_error_ln(F("Time Out!"));
      break;
    case WrongStack:
      ansi_error_ln(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      ansi_notice_ln(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      ansi_error_ln(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      ansi_notice_ln(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      ansi_notice_ln(F("Track finished!"));
      break;
    case DFPlayerError:
      ansi_error();
      Serial.print(F("DFPlayerError: "));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      ansi_default();
      break;
    default:
      break;
  }
  #else
  switch (type) {
    case TimeOut:
    case WrongStack:
    case DFPlayerCardRemoved:
    case DFPlayerError:
      ansi_error();
      Serial.print((__FlashStringHelper*) STR_ERROR_DFPLAYER);
      if (type == DFPlayerError) {
        Serial.print(type);
        Serial.print(' ');
        Serial.print(value);
      } else Serial.println(type);
      ansi_default();
      break;

    case DFPlayerPlayFinished:
    case DFPlayerCardOnline:
    case DFPlayerCardInserted:
      ansi_notice();
      Serial.print((__FlashStringHelper*) STR_ERROR_DFPLAYER);
      Serial.println(type);
      ansi_default();
      break;

    default:
      break;
  }
  #endif
}

void process_switches() {
  vol_up.loop();
  vol_down.loop();

  if (digitalRead(PIN_TEST) == LOW) {
    last_activity = millis();
  }

  if (vol_up.isPressed()) {
    volume_up();
  }

  if (vol_down.isPressed()) {
    volume_down();
  }
}

void loop() {
  process_serial();
  process_switches();
  digitalWrite(PIN_LED, !digitalRead(DFPlayer_BUSY));

  if (mode == MODE_FLOPPY) loop_floppy();
  else loop_ide();
}