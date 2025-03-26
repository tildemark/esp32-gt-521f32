/**
 * WiFiManager.cpp - Implements WiFi connectivity, MAC spoofing, and internet checks
 */

 #include "WiFiManager.h"

 // ✅ Office & Home WiFi Networks
 const char* wifiNetworks[][2] = {
     {"AvegaBros_WIFI", ""},  // Office WiFi (No password)
     {"GlobeAtHome_e3440_2.4", "xf6tC7MN"}  // Home WiFi
 };
 const int numNetworks = sizeof(wifiNetworks) / sizeof(wifiNetworks[0]);
 
 // ✅ Static MAC Address to EC:64:C9:7B:7F:9C (Used for all ESP32 devices)
 const uint8_t staticMAC[6] = {0xEC, 0x64, 0xC9, 0x7B, 0x7F, 0x9C}; 
 
/**
 * Sets a predefined static MAC address for all ESP32 devices.
 * - Prints the original MAC before changing it.
 */
void setStaticMAC() {
    uint8_t originalMAC[6];
  
    // ✅ Get the current (original) MAC address
    esp_wifi_get_mac(WIFI_IF_STA, originalMAC);
  
    // ✅ Print the original MAC address
    Serial.print("🔍 Original MAC Address: ");
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n", 
                  originalMAC[0], originalMAC[1], originalMAC[2], 
                  originalMAC[3], originalMAC[4], originalMAC[5]);
  
    // ✅ Set the new (spoofed) MAC address
    esp_wifi_set_mac(WIFI_IF_STA, staticMAC);
  
    // ✅ Print the new (spoofed) MAC address
    Serial.print("🔄 Spoofed MAC Address: ");
    Serial.println(WiFi.macAddress());
  }
  
 
 /**
  * Attempts to connect to one of the known WiFi networks.
  * Tries each network until a connection is established.
  * @return true if connected, false otherwise.
  */
 bool connectToWiFi() {
   Serial.println("🔍 Scanning for known WiFi networks...");
   
   setStaticMAC(); // ✅ Apply static MAC address before connecting
 
   for (int i = 0; i < numNetworks; i++) {
     const char* ssid = wifiNetworks[i][0];
     const char* password = wifiNetworks[i][1];
 
     Serial.print("📡 Trying to connect to: ");
     Serial.println(ssid);
 
     WiFi.begin(ssid, (strlen(password) > 0) ? password : NULL);
     
     int attempts = 0;
     while (!isConnectedToWiFi() && attempts < 20) { // Try for 10 seconds
       delay(500);
       Serial.print(".");
       attempts++;
     }
 
     if (isConnectedToWiFi()) {
       Serial.println("\n✅ Connected to " + String(ssid));
       Serial.print("🌐 IP Address: ");
       Serial.println(WiFi.localIP());
       return true;  // ✅ Stop trying once connected
     }
   }
 
   Serial.println("\n❌ No available WiFi networks.");
   return false;
 }
 
 /**
  * Checks if the ESP32 is connected to WiFi.
  * @return true if WiFi is connected, false otherwise.
  */
 bool isConnectedToWiFi() {
   return WiFi.status() == WL_CONNECTED;
 }
 
 /**
  * Checks if the ESP32 has internet access by pinging Google's DNS.
  * @return true if internet is accessible, false otherwise.
  */
 bool isConnectedToInternet() {
   return isConnectedToWiFi() && Ping.ping("8.8.8.8");
 }
 