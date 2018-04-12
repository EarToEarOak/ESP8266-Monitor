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


#ifndef HEADER_STATION
#define HEADER_STATION

#include <ESP8266WiFi.h>

#include "config.h"
#include "debug.h"


class Station {
  public:
    bool begin(String ssid, String ssidPassword);

  private:
    static WiFiEventHandler _stationConnected;
    static WiFiEventHandler _stationDisconnected;
    static WiFiEventHandler _stationDhcp;
    static WiFiEventHandler _stationDhcpTimeout;

    bool beginStation(String ssid, String ssidPassword);

    static void onStationConnected(const WiFiEventStationModeConnected& event);
    static void onStationDisconnected(const WiFiEventStationModeDisconnected& event);
    static void onStationDhcp(const WiFiEventStationModeGotIP& event);
    static void onStationDhcpTimeout();

    static String macToString(const unsigned char* mac);
};

#endif
