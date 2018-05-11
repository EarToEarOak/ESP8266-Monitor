/*
  ESP8266 Monitor

  Broadcasts the current state of an ESP8266 and DS18b20 temperature monitor,
  whilst keeping current draw to a minimum - ideal for battery powered projects.

  https://eartoearoak.com/software/esp8266_monitor

  Copyright 2018 Al Brown


  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as published by
  the Free Software Foundation

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  The license is available from <http://www.gnu.org/licenses/gpl-2.0.html>.
*/


#ifndef HEADER_CONFIG
#define HEADER_CONFIG

// WiFi Access Point
#define SSID_NAME "Wifi access point name"
#define SSID_PASSWORD "Wifi password"
#define WIFI_RETRIES 30

// Broadcast port
#define UDP_PORT 7711

// Refresh interval (ms)
#define INTERVAL 60000

// GPIOs to monitor
#define GPIOS {0, 2, 5, 12, 13, 14, 15}

// Uncomment to measure the supply voltage
//#define ADC_SUPPLY

// ADC parameters if not using ADC_VCC
#define VCC 3.3     // Supply voltage
#define DIVIDER 2   // Resitor divider ratio

// DS180b20 GPIO
#define ONE_WIRE_BUS 4
// DS180b20 resolution
#define RESOLUTION 10

// Debug to serial port
#define DEBUG

#endif
