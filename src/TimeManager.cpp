#include "TimeManager.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com", 8 * 3600, 60000);

String getCurrentTime() {
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int hours = timeInfo->tm_hour;
  int minutes = timeInfo->tm_min;
  String amPm = "AM";

  if (hours >= 12) {
      amPm = "PM";
      if (hours > 12) hours -= 12;
  } else if (hours == 0) {
      hours = 12;
  }

  String minuteStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);
  return String(hours) + ":" + minuteStr + " " + amPm;
}

String getCurrentDate() {
  time_t rawTime = timeClient.getEpochTime();
  struct tm* timeInfo = localtime(&rawTime);

  int day = timeInfo->tm_mday;
  int month = timeInfo->tm_mon + 1;
  int year = timeInfo->tm_year + 1900;

  String dayStr = (day < 10) ? "0" + String(day) : String(day);
  String monthStr = (month < 10) ? "0" + String(month) : String(month);

  return String(year) + "-" + monthStr + "-" + dayStr;
}
