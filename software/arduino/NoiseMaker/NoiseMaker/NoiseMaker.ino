#include <Arduino.h>
#include "constants.h"
#include "settings.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "serial_console.h"
#include "commands.h"
#include "ansi.h"
#include "storage.h"

bool ansi_enabled = DEFAULT_ANSI;
uint8_t setting_volume = DEFAULT_VOLUME;
uint8_t mode = MODE_FLOPPY;
uint8_t state = STATE_INIT;
uint8_t profile = DEFAULT_PROFILE;

SoftwareSerial dfplayer_serial(DFPlayer_RX, DFPlayer_TX);
DFRobotDFPlayerMini dfplayer;

unsigned long last_activity = 0;

void play_ide_startup() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_STARTUP);
}

void play_ide_active() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_ACTIVE);
}

void play_ide_shutdown() {
  dfplayer.playFolder(OFFSET_IDE + profile, SOUND_IDE_SHUTDOWN);
}

void setup_floppy() {
}

void ide_interrupt() {
  last_activity = millis();
}

void setup_ide() {
  play_ide_startup();
  attachInterrupt(digitalPinToInterrupt(ARD_P2), ide_interrupt, FALLING);
}

void setup() {
  dfplayer_serial.begin(BAUD_RATE_9600);
  process_serial_init();
  pinMode(MODE_PIN, INPUT_PULLUP);
  pinMode(TEST_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
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
  if (digitalRead(MODE_PIN) == LOW) {
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

void loop_floppy() {

}

bool replay = false;
void loop_ide() {
  switch (state) {

    /* Waiting for startup sound to finish */
    case STATE_INIT:
      while (dfplayer.available()) {
        if (dfplayer.readType() == DFPlayerPlayFinished) {
          Serial.println(F("set idle"));
          state = STATE_IDE_IDLE;
        } else unknown_error(DFPlayerPlayFinished, dfplayer.read());
      }
      break;

    /* Waiting for activity */
    case STATE_IDE_IDLE:
      while (digitalRead(DFPlayer_BUSY) == LOW);
      if (last_activity > 0 && ((millis() - last_activity) < IDLE_THRESHOLD)) {
        Serial.println(F("set_active"));
        state = STATE_IDE_ACTIVE;
        play_ide_active();
      }
      break;

    case STATE_IDE_ACTIVE:
      /* Check for activity timeout */
      replay = false;
      if ((millis() - last_activity) > IDLE_THRESHOLD) {
        Serial.println(F("set_paused"));
        state = STATE_IDE_PAUSED;
        dfplayer.pause();
      } else {
        while (dfplayer.available()) {
          if (dfplayer.readType() == DFPlayerPlayFinished) {
            replay = true;
          } else unknown_error(DFPlayerPlayFinished, dfplayer.read());
        }

        if (replay) {
            Serial.println(F("replay"));
            play_ide_active();
            while (digitalRead(DFPlayer_BUSY) == HIGH);
        }
      }
      break;

    case STATE_IDE_PAUSED:
      /* Check if we now see activity again */
      if ((millis() - last_activity) < IDLE_THRESHOLD) {
        Serial.println(F("resume"));
        state = STATE_IDE_ACTIVE;
        dfplayer.start();
        while (digitalRead(DFPlayer_BUSY) == HIGH);
      }
      break;

    default:
      break;
  }
}

void unknown_error(uint8_t type, int value) {
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
}

void loop() {
  process_serial();
  
  if (digitalRead(TEST_PIN) == LOW) {
    last_activity = millis();
  }
  digitalWrite(LED_PIN, !digitalRead(DFPlayer_BUSY));

  if (mode == MODE_FLOPPY) loop_floppy();
  else loop_ide();
}