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


#include "adc.h"


float Adc::_adc;

void Adc::begin() {
#ifdef ADC_SUPPLY
  _adc = ESP.getVcc();
  _adc /= 1000;
#else
  _adc = analogRead(A0);
  _adc *= VCC;
  _adc /= 1024;
  _adc /= DIVIDER;
#endif
}

void Adc::get(JsonObject& json) {
  json["Voltage"] = _adc;
}

