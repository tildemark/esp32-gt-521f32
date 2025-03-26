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

#endif
