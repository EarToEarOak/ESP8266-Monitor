LWIP_VARIANT = v2mss1460

BUILD_EXTRA_FLAGS = -g
COMP_WARNINGS = -Wall

UPLOAD_PORT = COM5
UPLOAD_SPEED = 921600

LIBS = 	$(ESP_LIBS)/ESP8266WiFi \
		$(ESP_LIBS)/Wire \
		$(ARDUINO_LIBS)/Adafruit_Unified_Sensor \
		$(ARDUINO_LIBS)/ArduinoJson/src \
		$(ARDUINO_LIBS)/DHT_sensor_library \
		$(ARDUINO_LIBS)/OneWire \
		src/Arduino-Temperature-Control-Library \

	
EXCLUDE_DIRS = ./src

include src/makeEspArduino/makeEspArduino.mk