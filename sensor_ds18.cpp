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

#include "sensor_ds18.h"

OneWire* SensorDS18::_oneWires;
DallasTemperature* SensorDS18::_sensors;

void SensorDS18::begin() {
	uint8_t buses[] = ONE_WIRE_BUSES;
	size_t buses_length = sizeof(buses) / sizeof(buses[0]);

	_oneWires = (OneWire*) malloc(buses_length * sizeof(OneWire));
	_sensors = (DallasTemperature*) malloc(
			buses_length * sizeof(DallasTemperature));
	for (size_t i = 0; i < buses_length; i++) {
		_oneWires[i] = OneWire(buses[i]);
		_sensors[i] = DallasTemperature(&_oneWires[i]);
		_sensors[i].begin();
		_sensors[i].setWaitForConversion(true);
		_sensors[i].setResolution(RESOLUTION);
		_sensors[i].requestTemperatures();
	}
}

void SensorDS18::get(JsonObject& json) {
	uint8_t buses[] = ONE_WIRE_BUSES;
	size_t buses_length = sizeof(buses) / sizeof(buses[0]);
	for (size_t i = 0; i < buses_length; i++) {
		for (size_t j = 0; j < _sensors[i].getDS18Count(); j++) {
			DeviceAddress address;
			_sensors[i].getAddress(address, j);
			float temperature = _sensors[i].getTempCByIndex(j);
			if (temperature ==  85.0 || temperature == -127.0)
				temperature = NAN;

			char sensor[17];
			snprintf(sensor, sizeof(sensor), "Temperature_%x%x", address[6],
					address[7]);
			json[sensor] = temperature;
		}
	}
}

