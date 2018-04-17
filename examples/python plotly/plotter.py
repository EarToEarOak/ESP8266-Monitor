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

import dash
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Output, Event
import datetime
import json
import plotly.graph_objs as go
import socket
import threading
import time


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
    x = []
    y = []

    for data in recData:
        if 'Time' in data and 'Temperature' in data:
            x.append(datetime.datetime.fromtimestamp(data['Time']))
            y.append(data['Temperature'])

    trace = go.Scatter(x=x, y=y)
    layout = go.Layout(
        title='Temperature',
        xaxis={'title': 'Time'},
        yaxis={'title': '°C', })

    return {'data': [trace], 'layout': layout}


class reciever(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self._sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._sock.bind(('', 7711))

    def run(self):
        while(True):
            rec = self._sock.recvfrom(1024)
            data = json.loads(rec[0])
            data['Time'] = time.time()
            recData.append(data)


if __name__ == '__main__':
    thread = reciever()
    thread.start()

    app.run_server()
