# ESP8266 Monitor #

Broadcasts the current state of an ESP8266 and DS18b20 temperature monitor, whilst keeping current draw to a minimum - ideal for battery powered projects.

https://eartoearoak.com/software/esp8266_monitor

Copyright 2018 Al Brown

al [at] eartoearoak.com



## Requirements

- [Arduino IDE](https://www.arduino.cc/)
- [Arduino ESP8266](https://github.com/esp8266/Arduino#installing-with-boards-manager)
- ArduinoJSON Library (installed via the Arduino IDE)
- [Arduino-Temperature-Control-Library (included)](https://github.com/milesburton/Arduino-Temperature-Control-Library)



## Usage

![](schematic\breadboard.png)

Edit 'config.h' changing the necessary `#define` statements to suit your needs:

- SSID_NAME: The name of your WiFi access point
- SSID_PASSWORD: The WiFi password
- INTERVAL:  The time between measurements (if this is too short it will never deep sleep)
- VCC: The power supply voltage (3 - 3.6 v)
- DIVIDER: If you have a voltage divider on the ADC input



Use the Arduino IDE to upload the 'ESP8266_Monitor.ino' sketch.



## Examples

A Python 3.x monitor and [ELK](https://www.elastic.co/) Logstash configuration are included in the examples directory. 

​	

## License ##

This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License version 2 as published by
 the Free Software Foundation

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 The license is available from <http://www.gnu.org/licenses/gpl-2.0.html>.