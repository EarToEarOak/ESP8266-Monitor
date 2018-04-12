#!/usr/bin/env python3
# 
#  ESP8266 Monitor Receiver
# 
#  An example which receives broadcasts from the ESP_Monitor software
# 
#  https://eartoearoak.com/software/esp8266_monitor
# 
#  Copyright 2018 Al Brown
# 
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  The license is available from <http://www.gnu.org/licenses/gpl-2.0.html>.
#

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('', 7711))

while(True):
    data = sock.recvfrom(1024)
    print (data[0].decode('ascii'))
