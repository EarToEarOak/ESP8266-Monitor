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


#include "station.h"


WiFiEventHandler Station::_stationConnected;
WiFiEventHandler Station::_stationDisconnected;
WiFiEventHandler Station::_stationDhcp;
WiFiEventHandler Station::_stationDhcpTimeout;


bool Station::begin(String ssid, String ssidPassword) {
  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.setAutoReconnect(true);

  _stationConnected = WiFi.onStationModeConnected(&onStationConnected);
  _stationDisconnected = WiFi.onStationModeDisconnected(&onStationDisconnected);
  _stationDhcp = WiFi.onStationModeGotIP(&onStationDhcp);
  _stationDhcpTimeout = WiFi.onStationModeDHCPTimeout(&onStationDhcpTimeout);

  bool status = beginStation(ssid, ssidPassword);

  DEBUG_SERIAL_F("Hostname     : %s\r\n", WiFi.hostname().c_str());
  DEBUG_SERIAL_F("RSSI         : %d dBm\r\n", WiFi.RSSI());
  DEBUG_SERIAL_F("DNS          : %s\r\n", WiFi.dnsIP().toString().c_str());
  DEBUG_SERIAL_F("MAC          : %s\r\n", WiFi.macAddress().c_str());

  return status;
}

bool Station::beginStation(String ssid, String ssidPassword) {
  WiFi.setOutputPower(20.5);

  DEBUG_SERIAL("\r\nConnecting to AP " + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), ssidPassword.c_str());

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < WIFI_RETRIES) {
    DEBUG_SERIAL(".");
    delay(500);
  }
  if (i == WIFI_RETRIES + 1) {
    DEBUG_SERIAL_LN("\r\nFailed.");
    return false;
  }
  DEBUG_SERIAL_LN("\r\nConnected.\n");

  return true;
}

void Station::onStationConnected(const WiFiEventStationModeConnected& event) {
  DEBUG_SERIAL_F("\r\nConnected to station: %s CH%u (%s)\r\n",
                 event.ssid.c_str(),
                 event.channel,
                 macToString(event.bssid).c_str());
}

void Station::onStationDisconnected(const WiFiEventStationModeDisconnected& event) {
  DEBUG_SERIAL_F("\r\nDisconnected from station: %s (%s) - %u\r\n",
                 event.ssid.c_str(),
                 macToString(event.bssid).c_str(),
                 event.reason);
}

void Station::onStationDhcp(const WiFiEventStationModeGotIP& event) {
  DEBUG_SERIAL_F("\r\nDHCP: %s/%s gw %s\r\n",
                 event.ip.toString().c_str(),
                 event.mask.toString().c_str(),
                 event.gw.toString().c_str());
}

void Station::onStationDhcpTimeout() {
  DEBUG_SERIAL_LN("\r\nDHCP timeout");
}

String Station::macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
