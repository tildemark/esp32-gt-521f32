/**
 * DisplayManager.h - Handles OLED display functions
 *
 * This module controls the OLED screen, displaying:
 * - Current time & date (retrieved from NTP)
 * - WiFi status (connected/disconnected icons)
 *
 * Author: Alfredo Sanchez Jr
 * Date: 2025-03-26
 */

 #ifndef DISPLAYMANAGER_H
 #define DISPLAYMANAGER_H
 
 #include <Wire.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_SH110X.h>
 #include "WiFiManager.h"
 #include "TimeManager.h"
 
 // Function Declarations
 void initDisplay();
 void displayStatus();
 void drawWiFiIcon(int x, int y);
 void drawDisconnectedIcon(int x, int y);
 void drawFingerprintIcon(int x, int y);
 void drawFingerprintErrorIcon(int x, int y);
 
 #endif
 