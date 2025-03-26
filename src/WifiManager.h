/**
 * WiFiManager.h - Handles WiFi connectivity, internet status, and MAC address spoofing
 * 
 * This module allows the ESP32 to:
 * - Connect to multiple predefined WiFi networks.
 * - Check WiFi and internet connectivity.
 * - Spoof a static MAC address for firewall authentication.
 * 
 * Author: Alfredo Sanchez Jr
 * Date: 2025-03-26
 */

 #ifndef WIFIMANAGER_H
 #define WIFIMANAGER_H
 
 #include <WiFi.h>
 #include <ESP32Ping.h>
 #include <esp_wifi.h> // Required for MAC address modification
 
 // Function Declarations
 void setStaticMAC();
 bool connectToWiFi();
 bool isConnectedToWiFi();
 bool isConnectedToInternet();
 
 #endif
 