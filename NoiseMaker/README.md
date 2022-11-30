# NoiseMaker Standard
The *NoiseMaker Standard*-version is really the first version I created for making noise when used with either 34-pin floppy drive replacements such as the Gotek - OR - the 40-pin IDE-replacements such as CF2IDE, SD2IDE etc. This document goes into building up a PCB for one of these, but not both at a time. For a more graceful introduction to what the *NoiseMaker* is meant to do, check out the main [documentation](https://github.com/tebl/NoiseMaker) before continuing.



- [1> Building the device](#1-building-the-device)
  - [1.1> Soldering it together](#11-soldering-it-together)
  - [1.2> IDE-version](#12-ide-version)
  - [1.3> Floppy-version](#13-floppy-version)
  - [1.4> Finishing touches](#14-finishing-touches)
- [2> Schematic](#2-schematic)
- [3> BOM](#3-bom)

# 1> Building the device
Building a device such as this assumes you have at least minor experience soldering things together, recommended is that you at the very least have access to a soldering station with adjustable temperature. If currently available, you should probably start with 60/40 rosin core solder as the lead-free alternatives tends to be a bit harder to work with.

With the requirements for basic equipment sorted, we need to talk a bit about what you want to achieve while building this project. The reason I ask is that as already mentioned, you need to pick between Floppy and IDE for each PCB you are building up, mainly because there are physical differences in how each of them connect to the your system. 

Now that you know what you want to build, we can get started on the most expensive step in any build process - shopping! So, head on over to the [BOM](#3-bom)-section for some information on what kind of components that you'll need. While I would have liked to give you specific part numbers for "reputable" electronic part suppliers, I can't afford to shop there so I usually make due with what I can find on sites such as ebay, AliExpress and any similar sites that sell cheap Chinese components. The downside to this is that I can't link to a part directly and expect it to stay listed, so you'll need to consider the description listed as a suggested *search term*.

## 1.1> Soldering it together
The construction of this unit should be fairly straight-forward, just take your time in order to make sure everything goes into place - more or less straight. I usually recommend starting by having a good look at the PCBs, try to figure out where all of the listed components go and in which orientation they go in (all of this should be clearly marked on the silkscreen). 

## 1.2> IDE-version
...

## 1.3> Floppy-version
...

## 1.4> Finishing touches
...

# 2> Schematic
The supplied KiCad files should be sufficient as both a schematic and as a  starting point for ordering PCBs (basically you could just zip the contents of the export folder and upload that on a fabrication site), the schematic is also available in [PDF-format](https://github.com/tebl/NoiseMaker/tree/main/documentation/schematic) and this is what you'll need to print and work your way through this things don't work as expected after assembly.

# 3> BOM
Most parts should be easy to get a hold of from your favourite local electronic component shop, but given that I don't have access to such shops where I live so everything was based on whatever I could get cheapest from eBay/AliExpress (free shipping, but plan on waiting 3-4 weeks for delivery). Components in parenthesis can be considered optional for features beyond the more basic functionality, but where's the fun in that? You deserve the complete package.

| Reference             | Item                                                              | Count | Order  |
| --------------------- | ----------------------------------------------------------------- | ----- | ------ |
| NoiseMaker Standard   | Fabricate using Gerber files                                      |     1 | PCBWay
| A1 | Arduino Nano (328, 168 with less features) | 1
| A2 | MP3-TF-16P (also known as DFPlayer Mini) | 1