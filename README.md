# NoiseMaker
When I first started out with my somewhat weird hobby of working with seriously to extremely outdated computers, the first things to go were naturally the inevitably failing hard-drives that ended up being replaced by Compact Flash solutions. The second to go were the physical floppy disk drives, having been replaced by Gotek drives. The result, while enjoyable to use, were vintage computers that even the wife could even stand to listen to. Except... that's not good, they're supposed to go *whirr*, *click*, *whine* and rotate grinding gears at such a rate that your significant other simply won't just accept a room dedicated to your vintage computers, they should demand that you get started on building such a room!

![NoiseMaker Standard, with Compact Flash](https://github.com/tebl/NoiseMaker/raw/main/gallery/2022-11-19%2000.57.58.jpg)

Was I going back to the old failiure rate of old mechanical drives? Nope, I followed the tutorials and installed a buzzer kit on that Gotek. Was I happy with it? Not really. So I did what I tend to do, go on AliExpress and ordered a bucketload of Arduino-modules listed as capable of playing back sound files. The cheapest of the bunch by far, was the *MP3-TF-16P* - also commonly known as the *DFPlayer Mini*. The very next thing that I discovered was that I didn't really understand enough about the various signals used to communicate with floppy disk drives, so they all sat in box somewhere until someone created something called *HDD Clicker*. I saw the videos made about it, but I wanted more options and so I started tinkering with the modules again - especially with the realization of how simple an IDE-version could have been made if I had just started there instead.

The result was this project, an amalgamation of the cheapest hardware in an oversized package that somehow probably ends up costing several times more to build than the popular thing. I could certainly have gone for more compact or powerful options, but it was an excuse to use some  Arduino Nano boards "powered" by ATmega168, which I had accidentally ordered a couple of years ago and never got around to throwing out.

- [1> Modules](#1-modules)
  - [1.1> NoiseMaker Standard](#11-noisemaker-standard)
- [3> Acknowledgements](#3-acknowledgements)

# 1> Modules
The following modules have been provided as part of this project. While more modules may have been included as part of this repository, these are the ones that I have actually built and tested. As mentioned in the relevant license for this project - that's not a warranty, just an indication that it worked that one time I tried it with my particular setup.

| Module                            | Description                                      |
| --------------------------------- | ------------------------------------------------ | 
| [NoiseMaker Standard](#11-noisemaker-standard) | Standard Arduino-based *NoiseMaker*, supporting 34-pin floppy and 40-pin IDE.

## 1.1> NoiseMaker Standard
This is the standard version of the *NoiseMaker*, created as a carrier board for both the *MP3-TF-16P* and an Arduino Nano. It can be built to work directly with IDE-devices, adding a female 40-pin header to the bottom of the card it can also be attached directly onto common *Compact Flash to IDE*-module. It can also be used in the "middle" of the cable, or just plugged into an unused part of the cable. The Arduino unfortunately doesn't have anywhere near the capability needed to actually interpret the communication between the devices, it is only responding to the same signal that your motherboard would normally read in order to light up your *HDD LED* (if you have one). 

![Compact Flash](https://github.com/tebl/NoiseMaker/raw/main/gallery/2022-11-19%2000.57.58.jpg)

 Alternatively you can build the device for use with 34-pin floppy drive replacements such as the Gotek instead. Similarly as with the IDE-version, it can also be plugged into an unused connector on your cable or in-between your drive and motherboard. Note that since the 34-pin cables have a twist on it, you need to set the *DRV_SEL* to the opposite value if connecting it up by itself after the twist.

![Floppy Interface](https://github.com/tebl/NoiseMaker/raw/main/gallery/2022-11-30%2000.10.39.jpg)

The documentation belonging to different variations of the standard NoiseMaker have been listed below, click the name for build documentation or follow the documentation links to jump to different sections within it. Ideally all of them should support being built as a NoiseMaker for either floppy or IDE, but not both at the same time (for that you will need two separate copies of the PCB).

| Module                 | Description                        | Documentation                      | Order      |
| ---------------------- | ---------------------------------- | ---------------------------------- | ---------- |
| [NoiseMaker](https://github.com/tebl/NoiseMaker/tree/main/NoiseMaker) | Arduino Nano, MP3-TF-16P | [Documentation](https://github.com/tebl/NoiseMaker/tree/main/NoiseMaker), [BOM](https://github.com/tebl/NoiseMaker/blob/main/NoiseMaker/README.md#3-bom), [Setting it up](https://github.com/tebl/NoiseMaker/blob/main/documentation/setting_it_up.md), [Getting started](https://github.com/tebl/NoiseMaker/blob/main/documentation/getting_started.md) | PCBWay

# 3> Acknowledgements
Everything comes from something, in particular when it comes to most of my electronics projects. I mainly build things I would like to own, often doing a respin to fit my own particular style and preferences. As mentioned I originally started making a module for making noise when used with modern floppy drive replacements, but it was only with inspiration from seeing the *HDD Clicker* that I went back and actually finished building it.