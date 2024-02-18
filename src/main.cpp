#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "TECNO SPARK 5 Air";
const char *password = "1234567890#";
const char *iftttApiKey = "d5GVBgd3oJf4bXzDph1-0xdiyoIB53Zhw2FufYp6a05"; // Your IFTTT API key5

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
unsigned long eventTime = 0;
unsigned long eventCount = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

// Define event names, timings, and colors for each oz1 to oz10
const char *iftttEventNames[] = {"kansas1", "kansas2", "kansas3", "kansas4", "kansas5", "ozcolor", "oz6", "oz7", "oz8", "oz9", "oz10", "oz2"};

const char *colors1[88] = {"WHITE", "WHITE", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "WHITE", "", "WHITE", "", "", "", "", "WHITE", "", "WHITE", "", "", "WHITE", "RED", "RED", "", "RED", "", "RED", "", "", ""};
const char *colors2[88] = {"", "", "WHITE", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "", "", "RED", "", "WHITE", "RED", "", "WHITE", "RED", "WHITE", "", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "ORANGE", "WHITE", ""};
const char *colors3[88] = {"", "", "WHITE", "", "WHITE", "WHITE", "", "", "WHITE", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "", "WHITE", "WHITE", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "WHITE", "WHITE", "RED", "", "RED", "", "RED", "", "", "RED", "", "WHITE", "RED", "", "WHITE", "RED", "WHITE", "", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "GREEN", "WHITE", ""};
const char *colors4[87] = {"", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "WHITE", "WHITE", "", "", "", "WHITE", "", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "DIM", "DIM", "RED", "RED", "", "", "RED", "", "", "RED", "", "WHITE", "RED", "WHITE", "RED", "WHITE", "", "GREEN", "WHITE", "WHITE", "GREEN", "WHITE", "YELLOW", "WHITE", ""};
const char *colors5[97] = {"", "", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "WHITE", "", "WHITE", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "WHITE", "", "WHITE", "", "", "RED", "RED", "", "", "WHITE", "RED", "WHITE", "RED", "WHITE", "GREEN", "GREEN", "GREEN", "GREEN", "WHITE", "BLUE", "WHITE", ""};
const char *colors6[50] = {"WHITE", "", "", "", "WHITE", "WHITE", "", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "PURPLE", "", "WHITE", "ORANGE", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"};
const char *colors7[61] = {"", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "", "PINK", "", "PINK", "", "PURPLE", "PURPLE", "RED", "BLUE", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "ORANGE", "WHITE"};
const char *colors8[55] = {"WHITE", "", "", "", "", "", "WHITE", "", "", "", "WHITE", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "", "PURPLE", "", "PURPLE", "YELLOW", "INDIGO", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "YELLOW", "WHITE"};
const char *colors9[55] = {"", "", "WHITE", "", "WHITE", "", "", "", "WHITE", "", "", "", "", "", "WHITE", "", "WHITE", "", "WHITE", "", "WHITE", "", "", "WHITE", "WHITE", "", "WHITE", "PURPLE", "", "PURPLE", "PINK", "", "PINK", "", "PURPLE", "GREEN", "RED", "WHITE", "", "WHITE", "WHITE", "BLUE", "WHITE", "BLUE", "WHITE", "BLUE", "ORANGE", "WHITE"};
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
    0,     // 18:36
    240,   // 18:40
    300,   // 18:45
    540,   // 18:49
    720,   // 18:52
    960,   // 18:56
    1200,  // 19:00
    1440,  // 19:04
    1680,  // 19:08
    1920,  // 19:12
    2160,  // 19:16
    2400,  // 19:20
    2640,  // 19:24
    2880,  // 19:28
    3120,  // 19:32
    3360,  // 19:36
    3600,  // 19:40
    3840,  // 19:44
    4080,  // 19:48
    4320,  // 19:52
    4560,  // 19:56
    4800,  // 20:00
    5040,  // 20:04
    6600,  // 20:11
    7968,  // 22:08
    14800, // 24:40:00
    16080, // 24:56:00
    16320, // 25:12:00
    16380, // 25:13:00
    16500, // 25:15:00
    16740, // 25:19:00
    16800, // 25:20:00
    16920, // 25:22:00
    17220, // 25:27:00
    17280, // 25:28:00
    17340, // 25:29:00
    17820, // 25:37:00
    18120, // 25:42:00
    20940, // 29:38:00
    21360, // 29:47:00
    21660, // 30:07:00
    24440, // 34:04:00
    28760, // 39:56:00
    30960, // 40:51:00
    41580, // 46:31:00
    42420, // 46:57:00
    48180, // 48:03:00
    49320  // 48:28:00
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
  if (strcmp(color, "") == 0)
  {
    // Concatenate "off" to the eventName
    std::string eventNameStr = eventName; // Convert eventName to std::string
    eventNameStr += "off";                // Append "off" to eventName
    color = "0";
    eventName = eventNameStr.c_str();
  }
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
  if (currentMillis - previousMillis > 1000)
  {
    previousMillis = millis();

    delay(20);
   // Serial.print("timer: ");
   // Serial.println(timerIntervals[eventCount]);
    if (eventTime == timerIntervals[eventCount])
    {
      eventCount++;
      if (eventCount > 55)
      {
        eventCount = 0;
      }

      Serial.print("triggered hue light: ");
      Serial.println(eventCount);
      Serial.print("triggered time: ");
      Serial.println(eventTime);
      Serial.print("timer: ");
      Serial.println(timerIntervals[eventCount]);
      if (eventCount < sizeof(colors1) / sizeof(colors1[0]))
      {
        triggerIFTTTEvent(iftttEventNames[0], colors1[eventCount]);
      }
      if (eventCount < sizeof(colors2) / sizeof(colors2[0]))
      {
        triggerIFTTTEvent(iftttEventNames[1], colors2[eventCount]);
      }
      if (eventCount < sizeof(colors3) / sizeof(colors3[0]))
      {
        triggerIFTTTEvent(iftttEventNames[2], colors3[eventCount]);
      }
      if (eventCount < sizeof(colors4) / sizeof(colors4[0]))
      {
        triggerIFTTTEvent(iftttEventNames[3], colors4[eventCount]);
      }
      if (eventCount < sizeof(colors5) / sizeof(colors5[0]))
      {
        triggerIFTTTEvent(iftttEventNames[4], colors5[eventCount]);
      }

      Serial.print("triggred colors: ");
      Serial.print(colors1[eventCount]);
      Serial.print(colors2[eventCount]);
      Serial.print(colors3[eventCount]);
      Serial.print(colors4[eventCount]);
      Serial.println(colors5[eventCount]);
     
    }

    if (eventTime == (990 + timerIntervals2[eventCount]))
    {
      eventCount++;
      if (eventCount > 56)
        eventCount = 0;
      Serial.print("triggered hue light 6 to 10: ");
      Serial.println(eventCount);
      if (eventCount < sizeof(colors6) / sizeof(colors6[0]))
      {
        triggerIFTTTEvent(iftttEventNames[5], colors6[eventCount]);
      }
      if (eventCount < sizeof(colors7) / sizeof(colors7[0]))
      {
        triggerIFTTTEvent(iftttEventNames[6], colors7[eventCount]);
      }
      if (eventCount < sizeof(colors8) / sizeof(colors8[0]))
      {
        triggerIFTTTEvent(iftttEventNames[7], colors8[eventCount]);
      }
      if (eventCount < sizeof(colors9) / sizeof(colors9[0]))
      {
        triggerIFTTTEvent(iftttEventNames[8], colors9[eventCount]);
      }
      if (eventCount < sizeof(colors10) / sizeof(colors10[0]))
      {
        triggerIFTTTEvent(iftttEventNames[9], colors10[eventCount]);
      }
      Serial.print("triggred colors: ");
      Serial.print(colors1[eventCount]);
      Serial.print(colors2[eventCount]);
      Serial.print(colors3[eventCount]);
      Serial.print(colors4[eventCount]);
      Serial.println(colors5[eventCount]);
    }
    eventTime++; // this keeps the counting time in seconds
    Serial.println(eventTime);
  }
}
