# Clock for Generation Klick

A basic clock framework for the ESP8266 to build a WiFi syncronized clock.

![](https://github.com/holgerlembke/ClockfGK/blob/main/img/303WifiLC01f.jpg?raw=true)

# History

## Hardware

It started with a simple request: could you please design a clock concept for a clock that is good readable for visually impaired humans. It should be easy to build, low cost, technological not challenging, educational, offer a path for some more DIY. Something like an eierlegende Wollmilchsau.

My 'research' resulted in that there are not so many options. I settled with three builds.

- a 2004 LC display
    - ![](https://github.com/holgerlembke/ClockfGK/blob/main/img/clock20041s.jpg?raw=true)
    - esp8266 wemos d1 mini
    - LCD2004 display
    - i2c adapter for those displays
    - 4 x M3 x 27 screw, washer and nut
    - 2 x M3 x 20 screw, washer and nut
    - 2 x M3 x 34 screw, washer and nut
    - 30 cm x 70 cm prototype pcb
    - 2 channel bidirectional level shifter
    - some "Dupont" female header cables
    - (4.7 kOhm resistors)

- a 128x64 LC display
    - ![](https://github.com/holgerlembke/ClockfGK/blob/main/img/clock128642s.jpg?raw=true)
    - esp8266 wemos d1 mini
    - 128 x 64 pixel i2c st7567s display
    - a 3 cm x 70 cm prototype pcb
    - 4 x M3 x 14 screw and nut
    - 4 x M2 x 12 screw and nut
    - 4-pin "Dupont" header male + female
    - (4.7 kOhm resistors)
    - (10 µF capacitor)

- a 4 x 7 segment LE display
    - Nixie Tube Wifi Clock Modul 0,8 Zoll, called 303WifiLC01
    - 79 mm long / 40 mm diameter Polymethylmethacrylat (PMMA, Acrylglas) tube
    - only for programming:
        - Programmer PCB is 2 cm x 8 cm with 6 rows of 28 holes
        - Pogo-Pins are named P75-E2 / P75-E3
        - Switches are Mini Push Button 8 mm x 8 mm Self Locking
        - UART modul is "Ch340g ch340e modul usb ttl". Look out for those that can do 3.3 V and 5 V by jumper. You need 3.3 V!
        - Clamp is a Wolfcraft FZR 3016000
        - Look at xxxxxxxxxx for more details.

The last option is by far the simples, cheapest, low energy consumpting and totally unsexiest one. 

The 2004 LCD is the largest and best readable. But more difficult to build.

The 128 x 64 is for those who want an old style analog clock.


## Software

It started with a quite simple solution for the [303WifiLC01](https://github.com/holgerlembke/ClockfGK/tree/main/clock303wifilc01). Then the other hardware options came and
I decided to build a more universal clock software. So [ClockfGK](ClockfGK) came into the world.


# Software

- simple web gui for configuration
- *no* WiFi connection during runtime (other than some seconds every other hours for syncronization)
- all the time zone stuff and daylight saving
- sunrise/sundown support

It is a good starting point for designing your own clock.

## Config

At power up it always boots into Access Point mode and waits for clients. It can be configured
at http://192.168.1.1 via browser.

If no client connects it will reboot into Station mode, syncronize the clock and disconnect from WiFi.

# 3D Prints

There are some [OpenSCAD scripts](https://github.com/holgerlembke/ClockfGK/tree/main/3d%20prints) for every build.



# Stuff I used

* for the hardware schematic: https://github.com/maarten-pennings/303WIFILC01
* for the TM1650 code: https://github.com/arkhipenko/TM1650
* for the ST7567S display: https://github.com/holgerlembke/st7567sfGK
* for the LCD2004/1602: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
* for the solar calculator: https://github.com/jpb10/SolarCalculator 
* Arduino core for ESP8266 WiFi chip from https://github.com/esp8266/Arduino
* Infinidash certification NDA toolkit
