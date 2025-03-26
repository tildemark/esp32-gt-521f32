#include <Arduino.h>      // Includes the Arduino core library for basic Arduino functions

// required for oled
#include <Wire.h>         // Includes the Wire library for I2C communication
#include <Adafruit_GFX.h> // Includes the Adafruit GFX library for graphics functions
#include <Adafruit_SH110X.h> // Includes the Adafruit SH110X library for the OLED display driver

// Defines the screen dimensions
#define SCREEN_WIDTH 128  // OLED display width in pixels
#define SCREEN_HEIGHT 64   // OLED display height in pixels
#define OLED_ADDR 0x3C    // I2C address of the OLED display (often 0x3C or 0x3D)
#define OLED_RESET -1 

// Creates an instance of the Adafruit SH1106G display object
// The parameters are:
// - width of the display
// - height of the display
// - pointer to the Wire instance (for I2C)
// - reset pin (not used here, so -1)
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// required for time
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Wi-Fi credentials
#define WIFI_SSID "AvegaBros_WIFI"
#define WIFI_PASSWORD ""
const char* ssid = "AvegaBros_WIFI";
const char* password = "";
WiFiClient client;

// NTP setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com", 8 * 3600, 60000);

// function declarations
String getCurrentTime();
String getCurrentDate();
void displayStatus();
bool isConnectedToWiFi();
bool isConnectedToInternet();

void setup() {
  Serial.begin(115200);  // Initializes serial communication at 115200 baud rate
  delay(1000); // Give serial monitor time to open

  // get the mac address
  Serial.println("ESP32 MAC Address:");
  Serial.println(WiFi.macAddress());

  Serial.print("Connecting to : ");
  Serial.print(WIFI_SSID);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try for 10 seconds
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (isConnectedToWiFi()) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Checking internet access...");
    if (isConnectedToInternet()) {
      Serial.println("Internet is available.");
    } else {
      Serial.println("No internet access.");
    }
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }

  // Initializes the OLED display
  // The parameters are:
  // - I2C address of the display
  // - reset (true/false)
  if (!display.begin(OLED_ADDR, true)) {
    Serial.println("SH110X OLED not found"); // Prints an error message if the display doesn't initialize
    while (1)  // Infinite loop to stop the program if the display is not found
      ;
  }
  display.display(); // Clears the display and shows the Adafruit splashscreen
  delay(2000);       // Waits for 2000 milliseconds (2 seconds)
}

void loop() {
  static unsigned long lastUpdate = 0;
  
  if (millis() - lastUpdate >= 1000) {  // Update once per second
    timeClient.update();
    displayStatus();
    lastUpdate = millis();
  }
}

// Function to display current time, operation mode, and fingerprint logo
void displayStatus() {
  display.clearDisplay();

  // Display current time
  display.setCursor(0, 0); 
  display.setTextSize(2); 
  display.print(getCurrentTime());

  display.setCursor(0, 30); 
  display.setTextSize(1);
  display.print(getCurrentDate());
  
  display.display();
  delay(2000);
}

String getCurrentTime()
{
  timeClient.update();
  time_t rawTime = timeClient.getEpochTime();
  struct tm * timeInfo = localtime(&rawTime);

  int hours = timeInfo->tm_hour;
  int minutes = timeInfo->tm_min;
  String amPm = "AM";

  // Adjust to 12-hour format
  if (hours >= 12) {
      amPm = "PM";
      if (hours > 12) hours -= 12;
  } else if (hours == 0) {
      hours = 12;
  }

  // Ensure two-digit minutes
  String minuteStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);

  return String(hours) + ":" + minuteStr + " " + amPm;
}

// Function to get current date
String getCurrentDate() {
  timeClient.update();
  time_t rawTime = timeClient.getEpochTime();
  struct tm * timeInfo = localtime(&rawTime); 

  int day = timeInfo->tm_mday;
  int month = timeInfo->tm_mon + 1; 
  int year = timeInfo->tm_year + 1900; 

  // Ensure two-digit day/month
  String dayStr = (day < 10) ? "0" + String(day) : String(day);
  String monthStr = (month < 10) ? "0" + String(month) : String(month);

  return String(year) + "-" + monthStr + "-" + dayStr;
}

bool isConnectedToWiFi() {
  return WiFi.status() == WL_CONNECTED;
}

bool isConnectedToInternet() {
  if (!isConnectedToWiFi()) return false;

  // Try to connect to a known reliable server (Google DNS)
  WiFiClient client;
  if (client.connect("google.com", 80)) {
    client.stop();
    return true;
  }
  return false;
}