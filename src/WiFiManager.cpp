#include "WiFiManager.h"

const char* wifiNetworks[][2] = {
    {"AvegaBros_WIFI", ""},
    {"GlobeAtHome_e3440_2.4", "xf6tC7MN"},
    {"Mobile_Hotspot", "hotspot_password"}
};
const int numNetworks = sizeof(wifiNetworks) / sizeof(wifiNetworks[0]);

bool connectToWiFi() {
  Serial.println("Scanning for known WiFi networks...");
  for (int i = 0; i < numNetworks; i++) {
    const char* ssid = wifiNetworks[i][0];
    const char* password = wifiNetworks[i][1];

    Serial.print("Trying to connect to: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int attempts = 0;
    
    while (!isConnectedToWiFi() && attempts < 20) {
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (isConnectedToWiFi()) {
      Serial.println("\nConnected to " + String(ssid));
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      return true;
    }
  }
  return false;
}

bool isConnectedToWiFi() {
  return WiFi.status() == WL_CONNECTED;
}

bool isConnectedToInternet() {
  return isConnectedToWiFi() && Ping.ping("8.8.8.8");
}
