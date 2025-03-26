/**
 * ESP32 OLED & WiFi Status Display
 * 
 * This program connects to multiple WiFi networks, syncs time via NTP,
 * and displays the current time, date, and WiFi status on an OLED display.
 * 
 * Author: Alfredo Sanchez Jr
 * Date: 2025-03-26
 */

#include "WiFiManager.h"
#include "DisplayManager.h"
#include "TimeManager.h"
#include "FingerprintManager.h"
 
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Attempt to connect to WiFi
  if (!connectToWiFi()) {
    Serial.println("❌📶 No WiFi connection available.");
    return;
  }

  Serial.println(isConnectedToInternet() ? "✅ Internet is available." : "❌ No internet access.");
  
  // Initialize OLED display
  initDisplay();

  // Start NTP time synchronization
  timeClient.begin();

  // ✅ Initialize fingerprint sensor
  initFingerprintSensor(); 
}
 
void loop() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate >= 1000) {  
    if (isConnectedToWiFi()) {  
      timeClient.update(); // Update time only if WiFi is connected
    }
    displayStatus(); // Update OLED display
    lastUpdate = millis();
  }

  // ✅ Check if fingerprint sensor is available before scanning
  if (!fingerprintAvailable) {
    delay(2000);
    return;  // Exit loop iteration early, but continue running the app
  }

  // ✅ Only run fingerprint scanning if the sensor is detected
  Serial.println("📌 Place your finger on the sensor...");
  delay(2000);

  if (verifyFingerprint()) {
    Serial.println("🔓 Access Granted!");
  } else {
    Serial.println("⛔ Access Denied.");
  }
}
 