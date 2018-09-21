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


#include "ESP8266_Monitor.h"

#ifdef ADC_SUPPLY
ADC_MODE(ADC_VCC);
#endif

Adc adc;
Gpio gpio;
SensorDS18 sensorDs18;
SensorDht sensorDht;
Station station;
Broadcast broadcast;
uint32_t start;


void setup() {
  start = millis() + BOOT_TIME;

  Serial.begin(115200);

  adc.begin();
  gpio.begin();
  sensorDht.begin();
  sensorDs18.begin();
  station.begin(SSID_NAME, SSID_PASSWORD);

  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  adc.get(json);
  gpio.get(json);
  sensorDht.get(json);
  sensorDs18.get(json);
  broadcast.multicast(json);
  json.prettyPrintTo(Serial);

  sint32_t sleep = millis() - start;
  sleep = INTERVAL - sleep;
  if (sleep < 50)
    sleep = 50;
  DEBUG_SERIAL_F("\nSleeping for %.3fs\n", sleep / 1000.0f);
  ESP.deepSleep(sleep * 1000);
}

void loop() {
}
