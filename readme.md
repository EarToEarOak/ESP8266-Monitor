# ESP8266 Monitor #

Broadcasts the current state of an ESP8266 and DS18b20 temperature monitor, using deep sleep mode to keep current draw to a minimum - ideal for battery powered projects.

Measurements are broadcast as JSON data to the local network over UDP.

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



## Output

JSON formatted data is broadcast to the local network on the default port of 7711.

Example output:

`{"Voltage":0.283594,"GPIO0":true,"GPIO2":true,"GPIO5":true,"GPIO12":true,"GPIO13":true,"GPIO14":true,"GPIO15":false,"Temperature":14.3125,"Host":"ESP_F1DCD0","RSSI":-37} `



## Electrical Characteristics

| Parameter       | Min   | Max  | Units |
| --------------- | ----- | ---- | ----- |
| Supply Voltage  | 3.0   | 3.6  | V     |
| ESP8266 Current | 0.002 | 70   | mA    |
| DS18b20 Current | 0.75  | 1    | mA    |



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