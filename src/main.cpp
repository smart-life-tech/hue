#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";
const char *iftttApiKey = "YourIFTTTApiKey"; // Your IFTTT API key

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

// Define event structure for oz1, oz2, etc.
struct Event
{
  const char *name;
  int hour;
  int minute;
  const char *color;
};

// Define events with specific times and colors
Event events[] = {
    {"oz1", 14, 0, "red"}, // oz1 at 2pm with red color
    {"oz2", 17, 0, "blue"} // oz2 at 5pm with blue color
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
  // Construct IFTTT webhook URL
  String url = "https://maker.ifttt.com/trigger/";
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

  // Schedule trigger events for each oz1 to oz10
  for (int i = 0; i < sizeof(events) / sizeof(events[0]); i++)
  {
    uint32_t eventTime = getEpochTime(events[i].hour, events[i].minute);
    delayUntil(eventTime);
    triggerIFTTTEvent(events[i].name, events[i].color);
  }
}

void loop()
{
  timeClient.update();
  delay(1000); // Update time every second
}
