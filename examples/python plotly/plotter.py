#!/usr/bin/env python3
#
#  ESP8266 Monitor Plotter
#
#  An example which receives broadcasts from the ESP_Monitor software
#  and plots them using plotly and Dash
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

from collections import defaultdict
import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Output, Event
import datetime
import json
import os
from plotly.graph_objs import Scatter, Layout
import socket
import threading
import time

SAVEDATA = "recData.json"

recData = []

app = dash.Dash()
app.layout = html.Div(children=[
    html.H1(children='ESP8266 Monitor'),
    dcc.Graph(id='temperature'),
    dcc.Interval(id='interval', interval=10 * 1000)
])


@app.callback(Output('temperature', 'figure'),
              events=[Event('interval', 'interval')])
def updateTemperature():
    traces = []
    sensors = defaultdict(list)
    times = defaultdict(list)
    for data in recData:
        if 'Time' in data and 'Host' in data:
            time = datetime.datetime.fromtimestamp(data['Time'])
            host = data['Host']
            
            if host=='None':
                for sensor in sensors:
                    sensors[sensor].append(None)
                    times[sensor].append(time)               
                continue
            
            temperatures = [(key, value)
                            for key, value in data.items() if 'Temperature_' in key]
            for temperature in temperatures:
                name = host + " " + temperature[0]
                sensors[name].append(temperature[1])
                times[name].append(time)

    for sensor, temperature in sorted(sensors.items()):
        trace = Scatter(x=times[sensor],
                        y=temperature,
                        name=sensor)
        traces.append(trace)

    layout = Layout(
        title='Temperature',
        xaxis={'title': 'Time'},
        yaxis={'title': '°C'})

    return {'data': traces, 'layout': layout}


class reciever(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._sock.bind(('', 7711))

    def run(self):
        f = open(SAVEDATA, 'a')

        while True:
            rec = self._sock.recvfrom(1024)
            data = json.loads(rec[0])
            data['Time'] = time.time()
            recData.append(data)
            f.write(json.dumps(data) + '\n')
            f.flush()


if __name__ == '__main__':
    if os.path.isfile(SAVEDATA):
        f = open(SAVEDATA, 'r+')
        for line in f:
            recData.append(json.loads(line))

        gap = {"Host": "None", "Time": time.time()}
        recData.append(gap)
        f.write(json.dumps(gap) + '\n')
        f.close()

    thread = reciever()
    thread.start()

    app.run_server()
