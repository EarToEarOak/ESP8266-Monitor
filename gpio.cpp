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


#include "gpio.h"


uint8_t Gpio::_gpios[] = GPIOS;
bool Gpio::_states[sizeof(_gpios) / sizeof(_gpios[0])];


void Gpio::begin() {
  for (uint8_t pin : _gpios)
    pinMode(pin, INPUT_PULLUP);

  delay(1);

  int i = 0;
  for (uint8_t pin : _gpios) {
    _states[i] = digitalRead(pin);
    i++;
  }
}

void Gpio::get(JsonObject& json) {
  int i = 0;
  char buffer[7];
  for (uint8_t pin : _gpios) {
    snprintf(buffer, 7, "GPIO%d", pin);
    json[buffer] = _states[i];
    i++;
  }
}

