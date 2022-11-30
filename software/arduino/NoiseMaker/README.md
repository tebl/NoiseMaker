# NoiseMaker

The functionality of the *NoiseMaker* has been realized using what for all purposes can be considered the least common denominator when it comes to MCUs, the standard ATmega328-based *Arduino Nano*. Due to an accidental order a couple years back I ended up with a handful of boards even more limited than these ones, based on the ATmega168 instead - offering half of the RAM and flash space expected - in order to get some usage out of them there is the option of using these lower capacity chips as well. This does however come at the cost of some nice-to-have features, but beyond being slightly less configurable on-the-fly using the serial interface - you should be able to enjoy it just the same once things are properly set up.

Consider editing *settings.h* to your liking instead of relying on run-time configuration, if you already have a preference for the values you want to use in the end. For either version of board, just make sure that you've correctly specified the chip used - before compiling the code.

## Libraries

While the installation of libraries should be handled automatically when using PlatformIO from within Visual Studio Code, but I recognize that many will simply want to get the code onto the board while using the standard *Arduino IDE* instead. In that case you may need to install libraries manually, the ones that are currently needed are as follows:

- [DFRobotDFPlayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini)
- [ezButton](https://github.com/ArduinoGetStarted/button)