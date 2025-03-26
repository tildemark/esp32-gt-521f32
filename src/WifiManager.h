#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <ESP32Ping.h>

// Function Declarations
bool connectToWiFi();
bool isConnectedToWiFi();
bool isConnectedToInternet();

#endif