#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "TECNO SPARK 5 Air";
const char *password = "1234567890#q";
const char *iftttApiKey = "d5GVBgd3oJf4bXzDph1-0xdiyoIB53Zhw2FufYp6a05"; // Your IFTTT API key5

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
unsigned long eventTime = 0;
unsigned long eventCount = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

// Define event names, timings, and colors for each oz1 to oz10
const char *iftttEventNames[] = {"kansas1", "kansas2", "kansas3", "kansas4", "kansas5", "oz6", "oz7", "oz8", "oz9", "oz10"};

const char *colors1[88] = {"", "WHITE", "WHITE", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "RED", "", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "RED", "WHITE", ""};
const char *colors2[88] = {"", "", "WHITE", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "ORANGE", "WHITE", ""};
const char *colors3[88] = {"", "", "WHITE", "", "WHITE", "WHITE", "", "", "WHITE", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "GREEN", "WHITE", ""};
const char *colors4[87] = {"", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "RED", "RED", "", "", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "YELLOW", "WHITE", ""};
const char *colors5[97] = {"", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "", "WHITE", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "", "", "RED", "RED", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "GREEN", "GREEN", "GREEN", "WHITE", "BLUE", "WHITE", ""};
const char *colors6[50] = {"WHITE", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "PURPLE", "", "WHITE", "ORANGE", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"};
const char *colors7[61] = {"", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "", "PURPLE", "PURPLE", "RED", "BLUE", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "ORANGE", "WHITE"};
const char *colors8[55] = {"WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "PURPLE", "", "PURPLE", "YELLOW", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"};
const char *colors9[55] = {"", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "PURPLE", "GREEN", "RED", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "ORANGE", "WHITE"};
const char *colors10[50] = {"WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "", "PURPLE", "PURPLE", "RED", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE", "WHITE"};

// Define event colors for each event

unsigned long previousMillis = 0; // Previous millis for each event

// Define the timer intervals and colors
const unsigned long timerIntervals[] = {
    0,   // 00:00-00:28 OFF
    28,  // 00:28-00:29 ON/OFF WHITE
    29,  // 00:29-00:31 ON/OFF WHITE
    31,  // 00:31-00:32 OFF
    32,  // 00:32-00:33 ON/OFF WHITE
    33,  // 00:33-00:34 OFF
    34,  // 00:34-00:35 OFF
    35,  // 00:35-00:36 OFF
    36,  // 00:36-00:38 ON/OFF WHITE
    38,  // 00:38-00:39 ON/OFF WHITE
    39,  // 00:39-00:40 OFF
    40,  // 00:40-00:42 ON WHITE
    42,  // 00:42-00:47 OFF
    47,  // 00:47-00:49 ON WHITE
    49,  // 00:49-00:50 OFF
    50,  // 00:50-00:51 OFF
    51,  // 00:51-00:52 OFF
    52,  // 00:52-00:53 ON WHITE
    53,  // 00:53-00:54 OFF
    54,  // 00:54-00:56 ON WHITE
    56,  // 00:56-00:57 OFF
    57,  // 00:57-00:58 ON WHITE
    58,  // 00:58-00:59 OFF
    59,  // 00:59-01:02 OFF
    62,  // 01:02-01:03 ON WHITE
    63,  // 01:03-01:04 OFF
    64,  // 01:04-01:05 OFF
    65,  // 01:05-01:06 OFF
    66,  // 01:06-01:39 ON WHITE
    99,  // 01:39-01:44 OFF
    104, // 01:44-02:22 ON WHITE
    142, // 02:22-02:28 OFF
    148, // 02:28-03:08 ON WHITE
    188, // 03:08-03:28 PAN WHITE
    208, // 03:28-03:29 OFF
    209, // 03:29-04:34 FLICKER WHITE
    274, // 04:34-05:48 ON WHITE
    348, // 05:48-05:59 DIM WHITE
    359, // 05:59-07:07 FLICKER WHITE
    427, // 07:07-07:51 PAN RED
    471, // 07:51-07:57 ON RED
    477, // 07:57-08:02 OFF
    482, // 08:02-08:07 OFF
    487, // 08:07-08:36 ON RED
    516, // 08:36-09:17 ON WHITE
    557, // 09:17-09:32 ON RED
    572, // 09:32-09:57 ON WHITE
    597, // 09:57-10:03 ON RED
    603, // 10:03-10:12 ON WHITE
    612, // 10:12-10:15 ON GREEN
    615, // 10:15-10:24 ON WHITE
    624, // 10:24-10:52 ON WHITE
    652, // 10:52-10:53 ON GREEN
    653, // 10:53-16:26 ON WHITE
    986, // 16:26-16:30 ON RED
    990, // 16:30-18:28 OFF
};

const unsigned long timerIntervals2[] = {
    1116, // 18:36 ON WHITE
    1120, // 18:40 OFF
    1125, // 18:45 OFF
    1129, // 18:49 OFF
    1132, // 18:52 ON WHITE
    1136, // 18:56 OFF
    1140, // 19:00 OFF
    1144, // 19:04 OFF
    1148, // 19:08 OFF
    1152, // 19:12 OFF
    1156, // 19:16 ON WHITE
    1160, // 19:20 OFF
    1164, // 19:24 ON WHITE
    1168, // 19:28 OFF
    1172, // 19:32 OFF
    1176, // 19:36 OFF
    1180, // 19:40 ON WHITE
    1184, // 19:44 OFF
    1188, // 19:48 OFF
    1192, // 19:52 OFF
    1196, // 19:56 ON WHITE
    1200, // 20:00 OFF
    1204, // 20:04 OFF
    1211, // 20:11 ON WHITE
    1328, // 22:08 DIM WHITE
    1480, // 24:40:00 OFF
    1496, // 24:56:00 ON WHITE
    1513, // 25:13:00 ON PURPLE
    1514, // 25:14:00 OFF
    1515, // 25:15:00 ON PURPLE
    1518, // 25:18:00 OFF
    1520, // 25:20:00 ON PINK
    1521, // 25:21:00 OFF
    1522, // 25:22:00 ON PINK
    1527, // 25:27:00 ON PURPLE
    1528, // 25:28:00 OFF
    1529, // 25:29:00 ON WHITE
    1537, // 25:37:00 ON ORANGE
    1540, // 25:40:00 ON INDIGO
    1542, // 25:42:00 ON WHITE
    1778, // 29:38:00 OFF
    1787, // 29:47:00 FLICKER WHITE
    1807, // 30:07:00 ON WHITE
    2044, // 34:04:00 ON BLUE
    2396, // 39:56:00 ON WHITE
    2451, // 40:51:00 ON BLUE
    2791, // 46:31:00 ON WHITE
    2817, // 46:57:00 ON BLUE
    2883, // 48:03:00 ON YELLOW
    2908, // 48:28:00 ON WHITE
};

void delayUntil(uint32_t targetTime)
{
  uint32_t currentTime;
  do
  {
    currentTime = timeClient.getEpochTime();
    delay(1000); // Adjust delay time as needed
  } while (currentTime < targetTime);
}

void triggerIFTTTEvent(const char *eventName, const char *color)
{
  // Create HTTP client object
  HTTPClient http;
  WiFiClient client;
  if (1)
  {
    // Concatenate "off" to the eventName
    // std::string eventNameStr = eventName; // Convert eventName to std::string
    // eventNameStr = "alloff";              // Append "off" to eventName
    color = "0";
    // eventName = eventNameStr.c_str();
    // Serial.println(eventName);
    //  Construct IFTTT webhook URL
    String url = "http://maker.ifttt.com/trigger/";
    url += "alloff";
    url += "/with/key/";
    url += iftttApiKey;

    // Create JSON payload for triggering IFTTT event with color parameter
    String payload = "{\"value1\":\"" + String(color) + "\"}";

    // Send HTTP POST request to trigger IFTTT event
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);

    // Check for successful request
    if (httpResponseCode > 0)
    {
      Serial.print("IFTTT request sent for ");
      Serial.print(eventName);
      Serial.print(", response code: ");
      Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("IFTTT request failed for ");
      Serial.print(eventName);
      Serial.print(", error: ");
      Serial.println(httpResponseCode);
      return;
    }
  }

  {
    Serial.println(eventName);
    // Construct IFTTT webhook URL
    String url = "http://maker.ifttt.com/trigger/";
    url += eventName;
    url += "/with/key/";
    url += iftttApiKey;

    // Create JSON payload for triggering IFTTT event with color parameter
    String payload = "{\"value1\":\"" + String(color) + "\"}";

    // Send HTTP POST request to trigger IFTTT event
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);

    // Check for successful request
    if (httpResponseCode > 0)
    {
      Serial.print("IFTTT request sent for ");
      Serial.print(eventName);
      Serial.print(", response code: ");
      Serial.println(httpResponseCode);
    }
    else
    {
      Serial.print("IFTTT request failed for ");
      Serial.print(eventName);
      Serial.print(", error: ");
      Serial.println(httpResponseCode);
      return;
    }
  }
  // End HTTP client
  http.end();
}

uint32_t getEpochTime(int hours, int minutes)
{
  struct tm tmstruct;
  time_t t;
  time(&t);
  tmstruct = *localtime(&t);
  tmstruct.tm_hour = hours;
  tmstruct.tm_min = minutes;
  tmstruct.tm_sec = 0;
  return mktime(&tmstruct);
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize NTP client
  timeClient.begin();

  for (int i = 0; i <= 60; i++)
  {
    // Serial.print(timerIntervals[i]);
  }
}

void loop()
{

  unsigned long currentMillis = millis();
  // Determine the current interval
  if (currentMillis - previousMillis > 10000)
  {
    previousMillis = millis();

    delay(20);
    // Serial.print("timer: ");
    // Serial.println(timerIntervals[eventCount]);
    if (eventTime == timerIntervals[eventCount])
    {

      Serial.print("triggered hue light: ");
      Serial.println(eventCount);
      Serial.print("triggered time: ");
      Serial.println(eventTime);
      Serial.print("timer: ");
      Serial.println(timerIntervals[eventCount]);
      if (eventCount < (sizeof(colors1) / sizeof(colors1[0])))
      {
        triggerIFTTTEvent(iftttEventNames[0], colors1[eventCount]);
      }
      if (eventCount < (sizeof(colors2) / sizeof(colors2[0])))
      {
        triggerIFTTTEvent(iftttEventNames[1], colors2[eventCount]);
      }
      if (eventCount < (sizeof(colors3) / sizeof(colors3[0])))
      {
        triggerIFTTTEvent(iftttEventNames[2], colors3[eventCount]);
      }
      if (eventCount < (sizeof(colors4) / sizeof(colors4[0])))
      {
        triggerIFTTTEvent(iftttEventNames[3], colors4[eventCount]);
      }
      if (eventCount < (sizeof(colors5) / sizeof(colors5[0])))
      {
        triggerIFTTTEvent(iftttEventNames[4], colors5[eventCount]);
      }

      Serial.print("triggred colors1: ");
      Serial.print(colors1[eventCount]);
      Serial.print("triggred colors2: ");
      Serial.print(colors2[eventCount]);
      Serial.print("triggred colors3: ");
      Serial.print(colors3[eventCount]);
      Serial.print("triggred colors4: ");
      Serial.print(colors4[eventCount]);
      Serial.print("triggred colors5: ");
      Serial.println(colors5[eventCount]);
      eventCount++;
      if (eventCount > 55)
      {
        eventCount = 0;
      }
    }

    if (eventTime == (timerIntervals2[eventCount]))
    {
      eventCount++;
      if (eventCount > 56)
        eventCount = 0;
      Serial.print("triggered hue light 6 to 10: ");
      Serial.println(eventCount);
      if (eventCount < (sizeof(colors6) / sizeof(colors6[0])))
      {
        triggerIFTTTEvent(iftttEventNames[5], colors6[eventCount]);
      }
      if (eventCount < (sizeof(colors7) / sizeof(colors7[0])))
      {
        triggerIFTTTEvent(iftttEventNames[6], colors7[eventCount]);
      }
      if (eventCount < (sizeof(colors8) / sizeof(colors8[0])))
      {
        triggerIFTTTEvent(iftttEventNames[7], colors8[eventCount]);
      }
      if (eventCount < (sizeof(colors9) / sizeof(colors9[0])))
      {
        triggerIFTTTEvent(iftttEventNames[8], colors9[eventCount]);
      }
      if (eventCount < (sizeof(colors10) / sizeof(colors10[0])))
      {
        triggerIFTTTEvent(iftttEventNames[9], colors10[eventCount]);
      }
      Serial.print("triggred colors: ");
      Serial.print(colors1[eventCount]);
      Serial.print(colors2[eventCount]);
      Serial.print(colors3[eventCount]);
      Serial.print(colors4[eventCount]);
      Serial.println(colors5[eventCount]);
      eventCount++;
      if (eventCount > 55)
      {
        eventCount = 0;
      }
    }
    eventTime++; // this keeps the counting time in seconds
    Serial.println(eventTime);
  }
}
