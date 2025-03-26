#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <WiFiUdp.h>
#include <NTPClient.h>

extern NTPClient timeClient;

String getCurrentTime();
String getCurrentDate();

#endif
