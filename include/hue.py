import requests
import time
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse

# Define event names and colors for each oz1 to oz10
ifttt_event_names = ["kansas1", "kansas2", "kansas3", "kansas4", "kansas5", "ozcolor", "oz6", "oz7", "oz8", "oz9", "oz10", "oz2"]
ifftt_off=["k1off,k2off,k3off,k4off,k5off","o6off,o7off,oz8off,o9off,oz10off"]
current_millis = int(round(time.time() * 1000))

#previous_millis = 0
event_count = 0
event_counts = 0
event_time = 0



colors1= ["", "WHITE", "WHITE", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "RED", "", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "RED", "WHITE", ""],
colors2= ["", "", "WHITE", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "ORANGE", "WHITE", ""],
colors3= ["", "", "WHITE", "", "WHITE", "WHITE", "", "", "WHITE", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "GREEN", "WHITE", ""],
colors4= ["", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "RED", "RED", "", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "YELLOW", "WHITE", ""],
colors5= ["", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "", "WHITE", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "", "", "RED", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "GREEN", "GREEN", "GREEN", "WHITE", "BLUE", "WHITE", ""],
colors6= ["WHITE", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "PURPLE", "", "WHITE", "ORANGE", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"],
colors7= ["", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "", "PURPLE", "PURPLE", "RED", "BLUE", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "ORANGE", "WHITE"],
colors8= ["WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "PURPLE", "", "PURPLE", "YELLOW", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"],
colors9= ["", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "PURPLE", "GREEN", "RED", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "ORANGE", "WHITE"],
colors10=["WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "", "PURPLE", "PURPLE", "RED", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE"]


# Define the timer intervals and colors
timer_intervals = [
    0,   # 00:00-00:28 OFF
    28,  # 00:28-00:29 ON/OFF WHITE
    29,  # 00:29-00:31 ON/OFF WHITE
    31,  # 00:31-00:32 OFF
    32,  # 00:32-00:33 ON/OFF WHITE
    33,  # 00:33-00:34 OFF
    34,  # 00:34-00:35 OFF
    35,  # 00:35-00:36 OFF
    36,  # 00:36-00:38 ON/OFF WHITE
    38,  # 00:38-00:39 ON/OFF WHITE
    39,  # 00:39-00:40 OFF
    40,  # 00:40-00:42 ON WHITE
    42,  # 00:42-00:47 OFF
    47,  # 00:47-00:49 ON WHITE
    49,  # 00:49-00:50 OFF
    50,  # 00:50-00:51 OFF
    51,  # 00:51-00:52 OFF
    52,  # 00:52-00:53 ON WHITE
    53,  # 00:53-00:54 OFF
    54,  # 00:54-00:56 ON WHITE
    56,  # 00:56-00:57 OFF
    57,  # 00:57-00:58 ON WHITE
    58,  # 00:58-00:59 OFF
    59,  # 00:59-01:02 OFF
    62,  # 01:02-01:03 ON WHITE
    63,  # 01:03-01:04 OFF
    64,  # 01:04-01:05 OFF
    65,  # 01:05-01:06 OFF
    66,  # 01:06-01:39 ON WHITE
    99,  # 01:39-01:44 OFF
    104, # 01:44-02:22 ON WHITE
    142, # 02:22-02:28 OFF
    148, # 02:28-03:08 ON WHITE
    188, # 03:08-03:28 PAN WHITE
    208, # 03:28-03:29 OFF
    209, # 03:29-04:34 FLICKER WHITE
    274, # 04:34-05:48 ON WHITE
    348, # 05:48-05:59 DIM WHITE
    359, # 05:59-07:07 FLICKER WHITE
    427, # 07:07-07:51 PAN RED
    471, # 07:51-07:57 ON RED
    477, # 07:57-08:02 OFF
    482, # 08:02-08:07 OFF
    487, # 08:07-08:36 ON RED
    516, # 08:36-09:17 ON WHITE
    557, # 09:17-09:32 ON RED
    572, # 09:32-09:57 ON WHITE
    597, # 09:57-10:03 ON RED
    603, # 10:03-10:12 ON WHITE
    612, # 10:12-10:15 ON GREEN
    615, # 10:15-10:24 ON WHITE
    624, # 10:24-10:52 ON WHITE
    652, # 10:52-10:53 ON GREEN
    653, # 10:53-16:26 ON WHITE
    986, # 16:26-16:30 ON RED
    990, # 16:30-18:28 OFF
]

timer_intervals2 = [
    1116, # 18:36 ON WHITE
    1120, # 18:40 OFF
    1125, # 18:45 OFF
    1129, # 18:49 OFF
    1132, # 18:52 ON WHITE
    1136, # 18:56 OFF
    1140, # 19:00 OFF
    1144, # 19:04 OFF
    1148, # 19:08 OFF
    1152, # 19:12 OFF
    1156, # 19:16 ON WHITE
    1160, # 19:20 OFF
    1164, # 19:24 ON WHITE
    1168, # 19:28 OFF
    1172, # 19:32 OFF
    1176, # 19:36 OFF
    1180, # 19:40 ON WHITE
    1184, # 19:44 OFF
    1188, # 19:48 OFF
    1192, # 19:52 OFF
    1196, # 19:56 ON WHITE
    1200, # 20:00 OFF
    1204, # 20:04 OFF
    1211, # 20:11 ON WHITE
    1328, # 22:08 DIM WHITE
    1480, # 24:40:00 OFF
    1496, # 24:56:00 ON WHITE
    1513, # 25:13:00 ON PURPLE
    1514, # 25:14:00 OFF
    1515, # 25:15:00 ON PURPLE
    1518, # 25:18:00 OFF
    1520, # 25:20:00 ON PINK
    1521, # 25:21:00 OFF
    1522, # 25:22:00 ON PINK
    1527, # 25:27:00 ON PURPLE
    1528, # 25:28:00 OFF
    1529, # 25:29:00 ON WHITE
    1537, # 25:37:00 ON ORANGE
    1540, # 25:40:00 ON INDIGO
    1542, # 25:42:00 ON WHITE
    1778, # 29:38:00 OFF
    1787, # 29:47:00 FLICKER WHITE
    1807, # 30:07:00 ON WHITE
    2044, # 34:04:00 ON BLUE
    2396, # 39:56:00 ON WHITE
    2451, # 40:51:00 ON BLUE
    2791, # 46:31:00 ON WHITE
    2817, # 46:57:00 ON BLUE
    2883, # 48:03:00 ON YELLOW
    2908, # 48:28:00 ON WHITE
]
def check_and_trigger_event():
    global event_count, event_time,event_counts

    if event_time == timer_intervals[event_counts]:
        print(f"Triggered hue light: {event_count}")
        print(f"Triggered time: {event_time}")
        print(f"Timer: {timer_intervals[event_count]}")

        if event_count < len(colors1[0]):
            trigger_ifttt_event(ifttt_event_names[0], colors1[0][event_count])
        if event_count < len(colors2[0]):
            trigger_ifttt_event(ifttt_event_names[1], colors2[0][event_count])
        if event_count < len(colors3[0]):
            trigger_ifttt_event(ifttt_event_names[2], colors3[0][event_count])
        if event_count < len(colors4[0]):
            trigger_ifttt_event(ifttt_event_names[3], colors4[0][event_count])
        if event_count < len(colors5[0]):
            trigger_ifttt_event(ifttt_event_names[4], colors5[0][event_count])

        print(f"Triggered colors1: {colors1[0][event_count]}")
        print(f"Triggered colors2: {colors2[0][event_count]}")
        print(f"Triggered colors3: {colors3[0][event_count]}")
        print(f"Triggered colors4: {colors4[0][event_count]}")
        print(f"Triggered colors5: {colors5[0][event_count]}")
        print("triggred event: ", ifttt_event_names[0])

        event_count += 1
        if event_count > 56:#for colors
            event_count = 0
            
        event_counts += 1
        if event_count >= len(timer_intervals) - 1:
            event_counts = 0

    if event_time == timer_intervals2[event_counts]:
        event_count += 1
        if event_count > 56:
            event_count = 0
        if event_count >= len(timer_intervals) - 1:
            event_counts = 0

        print(f"Triggered hue light 6 to 10: {event_count}")

        if event_count < len(colors6[0]):
            trigger_ifttt_event(ifttt_event_names[5], colors6[0][event_count])
        if event_count < len(colors7[0]):
            trigger_ifttt_event(ifttt_event_names[6], colors7[0][event_count])
        if event_count < len(colors8[0]):
            trigger_ifttt_event(ifttt_event_names[7], colors8[0][event_count])
        if event_count < len(colors9[0]):
            trigger_ifttt_event(ifttt_event_names[8], colors9[0][event_count])
        if event_count < len(colors10[0]):
            trigger_ifttt_event(ifttt_event_names[9], colors10[0][event_count])

        #print(f"Triggered colors: {colors6[event_count]} {colors7[event_count]} {colors8[event_count]} {colors9[event_count]} {colors10[event_count]}")


    event_time += 1
    print(event_time)
#code starts here
  
def timer():
    global previous_millis,event_counts
    previous_millis=0
    event_count = 0
    event_counts = 0
    event_time = 0
    while(startup==True):
        current_millis = int(round(time.time() * 1000))
        if current_millis - previous_millis > 1000:
            previous_millis = current_millis
            time.sleep(0.02)
            check_and_trigger_event()
            
class RequestHandler(BaseHTTPRequestHandler):
    def _set_headers(self, status_code=200):
        self.send_response(status_code)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        global startup
        parsed_path = urlparse(self.path)
        if parsed_path.path == '/test':
            # Run your set of Python code here
            # For example:
            
            startup=True
            print("Received a request to /test")
            self._set_headers()
            self.wfile.write(b"Triggered our Python codes!")
            # Stop the server after handling the request
            timer()
            print("server shutdown")
            self.server.shutdown()  # This will stop the server
            print("server shutdown")
        else:
            self._set_headers(404)
            self.wfile.write(b"Not Found")

def run(server_class=HTTPServer, handler_class=RequestHandler, addr="localhost", port=14999):
    server_address = (addr, port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting server on {addr}:{port}...")
    httpd.serve_forever()

def trigger_ifttt_event(event_name, color):
    # Concatenate "off" to the eventName
    if event_name == "kansas1" and color == "":
        event_name="k1off"
    elif event_name == "kansas2" and color == "":
        event_name="k2off"
    elif event_name == "kansas3" and color == "":
        event_name="k3off"
    elif event_name == "kansas4" and color == "":
        event_name="k4off"
    elif event_name == "kansas5" and color == "":
        event_name="k5off"
    elif event_name == "oz6" and color == "":
        event_name="o6off"
    elif event_name == "oz7" and color == "":
        event_name="o7off"
    elif event_name == "oz8" and color == "":
        event_name="oz8off"
    elif event_name == "oz9" and color == "":
        event_name="oz9off"
    elif event_name == "oz10" and color == "":
        event_name="oz10off"
        
    # Construct IFTTT webhook URL
    url = f"https://maker.ifttt.com/trigger/{event_name}/with/key/d5GVBgd3oJf4bXzDph1-0xdiyoIB53Zhw2FufYp6a05"

    # Create JSON payload for triggering IFTTT event with color parameter
    payload = {"value1": color}

    # Send HTTP POST request to trigger IFTTT event
    headers = {"Content-Type": "application/json"}
    try:
        response = requests.post(url, json=payload, headers=headers)
        response.raise_for_status()

        print(f"IFTTT request sent for {event_name}, response code: {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"IFTTT request failed for {event_name}, error: {e}")

    print("triggred event: ", event_name)

  
url = 'https://maker.ifttt.com/trigger/alloff/with/key/d5GVBgd3oJf4bXzDph1-0xdiyoIB53Zhw2FufYp6a05'
data = {"value1": "red"}
headers = {"Content-Type": "application/json"}

response = requests.post(url, json=data, headers=headers)
print(len(colors1[0]))
if response.status_code == 200:
    print("IFTTT event triggered successfully.")
else:
    print(f"Failed to trigger IFTTT event. Status code: {response.status_code}")
    print(response.text)

# Example usage:
while True:
    startup=False
    run()
    print(startup)
    