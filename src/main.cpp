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

// Define event names for each oz1 to oz10
const char *iftttEventNames[] = {"oz1", "oz2", "oz3", "oz4", "oz5", "oz6", "oz7", "oz8", "oz9", "oz10"};

// Define specific times (in local time) for each event (e.g., 5pm, 2pm)
const int eventHours[] = {17, 14}; // 5pm, 2pm
const int eventMinutes[] = {0, 0};
void delayUntil(uint32_t targetTime)
{
  uint32_t currentTime;
  do
  {
    currentTime = timeClient.getEpochTime();
    delay(1000); // Adjust delay time as needed
  } while (currentTime < targetTime);
}

void triggerIFTTTEvent(const char *eventName)
{
  // Create HTTP client object
  HTTPClient http;
  WiFiClient client;
  // Construct IFTTT webhook URL
  String url = "https://maker.ifttt.com/trigger/";
  url += eventName;
  url += "/with/key/";
  url += iftttApiKey;

  // Send HTTP POST request to trigger IFTTT event
  http.begin(client, url);
  int httpResponseCode = http.POST("");

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
  for (int i = 0; i < 2; i++)
  { // Change to match the number of events
    uint32_t eventTime = getEpochTime(eventHours[i], eventMinutes[i]);
    delayUntil(eventTime);
    triggerIFTTTEvent(iftttEventNames[i]);
  }
}

void loop()
{
  timeClient.update();
  delay(1000); // Update time every second
}
