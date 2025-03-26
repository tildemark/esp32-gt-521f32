/**
 * TimeManager.h - Handles time synchronization using NTP
 *
 * This module:
 * - Retrieves current time from NTP servers
 * - Formats time & date for display
 *
 * Author: Alfredo Sanchez Jr
 * Date: 2025-03-26
 */

 #ifndef TIMEMANAGER_H
 #define TIMEMANAGER_H
 
 #include <WiFiUdp.h>
 #include <NTPClient.h>
 
 extern NTPClient timeClient;
 
 // Function Declarations
 String getCurrentTime(bool);
 String getCurrentDate(bool);
 
 #endif
 