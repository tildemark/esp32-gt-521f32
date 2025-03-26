/**
 * TimeManager.cpp - Implements NTP-based time synchronization
 */

 #include "TimeManager.h"

 // ✅ NTP Configuration (Google Time Server)
 WiFiUDP ntpUDP;
 NTPClient timeClient(ntpUDP, "time.google.com", 8 * 3600, 60000);
 
 /**
  * Retrieves the current time in HH:MM AM/PM format.
  * 
  * @return Formatted time string (e.g., "10:45 PM")
  */
 String getCurrentTime(bool fullFormat = false) {
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int hours = timeInfo->tm_hour;
  int minutes = timeInfo->tm_min;
  int seconds = timeInfo->tm_sec;
  String amPm = "AM";

  if (hours >= 12) {
    amPm = "PM";
    if (hours > 12) hours -= 12;
  } else if (hours == 0) {
    hours = 12;
  }

  String minuteStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);
  String secondStr = (seconds < 10) ? "0" + String(seconds) : String(seconds);

  if (fullFormat) {
    return String(hours) + ":" + minuteStr + ":" + secondStr + " " + amPm;
  } else {
    return String(hours) + ":" + minuteStr + " " + amPm;
  }
}

 /**
  * Retrieves the current date in YYYY-MM-DD format.
  * 
  * @return Formatted date string (e.g., "2025-03-26")
  */
 String getCurrentDate(bool fullFormat = false) {
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int year = timeInfo->tm_year + 1900;
  int month = timeInfo->tm_mon + 1;
  int day = timeInfo->tm_mday;

  String yearStr = String(year);
  String monthStr = (month < 10) ? "0" + String(month) : String(month);
  String dayStr = (day < 10) ? "0" + String(day) : String(day);

  if (fullFormat) {
    return yearStr + "-" + monthStr + "-" + dayStr;
  } else {
    return monthStr + "-" + dayStr;
  }
}

 