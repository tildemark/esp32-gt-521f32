#include <Arduino.h>      // Includes the Arduino core library for basic Arduino functions

// required for oled
#include <Wire.h>         // Includes the Wire library for I2C communication
#include <Adafruit_GFX.h> // Includes the Adafruit GFX library for graphics functions
#include <Adafruit_SH110X.h> // Includes the Adafruit SH110X library for the OLED display driver

// required for time
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP32Ping.h>  // Add this library for better internet checking

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

// WiFi Networks (Multiple SSIDs)
const char* wifiNetworks[][2] = {
  {"AvegaBros_WIFI", ""},
  {"Home_WiFi", "home_password"},
  {"Mobile_Hotspot", "hotspot_password"}
};
const int numNetworks = sizeof(wifiNetworks) / sizeof(wifiNetworks[0]);

// NTP setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com", 8 * 3600, 60000);

// function declarations
// Function Declarations
bool connectToWiFi();
bool isConnectedToWiFi();
bool isConnectedToInternet();
String getCurrentTime();
String getCurrentDate();
void displayStatus();

void setup() {
  Serial.begin(115200);  // Initializes serial communication at 115200 baud rate
  delay(1000); // Give serial monitor time to open

  // get the mac address
  Serial.println("\nESP32 MAC Address: " + WiFi.macAddress());

  if (!connectToWiFi()) {
    Serial.println("No WiFi connection available.");
    return;
  }
  Serial.println("Checking internet access...");
  Serial.println(isConnectedToInternet() ? "Internet is available." : "No internet access.");

  // Initializes the OLED display
  // The parameters are:
  // - I2C address of the display
  // - reset (true/false)
  if (!display.begin(OLED_ADDR, true)) {
    Serial.println("SH110X OLED not found"); // Prints an error message if the display doesn't initialize
    return;
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

// 📶 Connect to WiFi (Tries multiple SSIDs)
bool connectToWiFi() {
  Serial.println("Scanning for known WiFi networks...");

  for (int i = 0; i < numNetworks; i++) {
    const char* ssid = wifiNetworks[i][0];
    const char* password = wifiNetworks[i][1];

    Serial.print("Trying to connect to: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int attempts = 0;
    
    while (!isConnectedToWiFi() && attempts < 20) {  // Try for 10 seconds
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (isConnectedToWiFi()) {
      Serial.println("\nConnected to " + String(ssid));
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      return true;  // Stop trying once connected
    } else {
      Serial.println("\nFailed to connect to " + String(ssid));
    }
  }

  return false;  // No networks available
}

// 📡 Check if WiFi is connected
bool isConnectedToWiFi() {
  return WiFi.status() == WL_CONNECTED;
}

// 🌎 Check if internet is available (Uses Google's DNS)
bool isConnectedToInternet() {
  return isConnectedToWiFi() && Ping.ping("8.8.8.8");
}
