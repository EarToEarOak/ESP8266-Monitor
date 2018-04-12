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


#include "temperature.h"


OneWire Temperature::_oneWire(ONE_WIRE_BUS);
DallasTemperature Temperature::_sensors(&_oneWire);
float Temperature::_temperature;


void Temperature::begin() {
  _sensors.setWaitForConversion(true);
  _sensors.setResolution(RESOLUTION);
  _sensors.requestTemperatures();
  _temperature = _sensors.getTempCByIndex(0);
}


void Temperature::get(JsonObject& json) {
  if (_temperature ==  85.0 || _temperature == -127.0)
    return;

  json["Temperature"] = _temperature;
}
