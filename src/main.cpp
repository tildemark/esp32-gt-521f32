#include "WiFiManager.h"
#include "DisplayManager.h"
#include "TimeManager.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nESP32 MAC Address: " + WiFi.macAddress());

  if (!connectToWiFi()) {
    Serial.println("No WiFi connection available.");
    return;
  }

  Serial.println(isConnectedToInternet() ? "Internet is available." : "No internet access.");
  initDisplay(); // Initialize OLED

  timeClient.begin();
}

void loop() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate >= 1000) {  
    if (isConnectedToWiFi()) {  
      timeClient.update();
    }
    displayStatus();
    lastUpdate = millis();
  }
}
