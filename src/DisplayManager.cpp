/**
 * DisplayManager.cpp - Implements OLED display functions
 */

 #include "DisplayManager.h"
 #include "FingerprintManager.h"

 // ✅ OLED display settings
 #define SCREEN_WIDTH 128
 #define SCREEN_HEIGHT 64
 #define OLED_ADDR 0x3C
 #define OLED_RESET -1
 
 Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 /**
  * Initializes the OLED display.
  * - If the display is not found, prints an error message.
  */
 void initDisplay() {
   if (!display.begin(OLED_ADDR, true)) {
     Serial.println("❌ SH110X OLED not found!");
     return;
   }
   display.display();
   delay(2000);
 }
 
 /**
  * Updates the OLED display with:
  * - Current time & date (from NTP)
  * - WiFi status (WiFi or Disconnected icon)
  */
 void displayStatus() {
   display.clearDisplay();
   display.setTextColor(SH110X_WHITE);
 
   // 📅 Display Current Date
   display.setCursor(0, 10);
   display.setTextSize(2);
   display.print(getCurrentTime());
 
   // 🕒 Display Current Time
   display.setCursor(0, 40);
   display.setTextSize(1);
   display.print(getCurrentDate());
 
   // 📡 Show WiFi or Disconnected Icon
   if (isConnectedToInternet()) {
     drawWiFiIcon(110, 0); // WiFi Connected
   } else {
     drawDisconnectedIcon(110, 0); // No Internet
   }
 
    // 🔍 Show Fingerprint Sensor Status (Top-Right, Left Side)
    if (fingerprintAvailable) {
        drawFingerprintIcon(90, 0);  // Fingerprint detected
    } else {
        drawFingerprintErrorIcon(90, 0);  // Fingerprint missing
    }

   display.display();
 }
 
 /**
  * Draws a WiFi signal icon at the specified position.
  * - Represents an active internet connection.
  * 
  * @param x X position on the screen
  * @param y Y position on the screen
  */
 void drawWiFiIcon(int x, int y) {
    display.fillCircle(x + 5, y + 7, 2, SH110X_WHITE);  // Center dot
    display.drawLine(x, y + 5, x + 10, y + 5, SH110X_WHITE);  // Small arc
    display.drawLine(x - 2, y + 3, x + 12, y + 3, SH110X_WHITE);  // Medium arc
    display.drawLine(x - 4, y + 1, x + 14, y + 1, SH110X_WHITE);  // Large arc
  }
 
 /**
  * Draws an "X" icon at the specified position.
  * - Represents a disconnected internet status.
  * 
  * @param x X position on the screen
  * @param y Y position on the screen
  */
 void drawDisconnectedIcon(int x, int y) {
   display.drawLine(x, y, x + 10, y + 10, SH110X_WHITE);  // Slash line
   display.drawLine(x + 10, y, x, y + 10, SH110X_WHITE);  // Cross slash
 }
 
 void drawFingerprintIcon(int x, int y) {
    display.drawCircle(x + 5, y + 7, 4, SH110X_WHITE);  // Outer fingerprint ring
    display.drawPixel(x + 5, y + 7, SH110X_WHITE);  // Center dot
    display.drawLine(x + 2, y + 4, x + 8, y + 4, SH110X_WHITE);  // Top line
    display.drawLine(x + 2, y + 10, x + 8, y + 10, SH110X_WHITE);  // Bottom line
  }

void drawFingerprintErrorIcon(int x, int y) {
    display.drawCircle(x + 3, y + 6, 3, SH110X_WHITE);  // Outer circle
    display.drawLine(x, y + 3, x + 6, y + 9, SH110X_WHITE);  // Cross line
    display.drawLine(x + 6, y + 3, x, y + 9, SH110X_WHITE);  // Reverse cross line
}