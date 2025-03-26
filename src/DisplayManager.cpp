#include "DisplayManager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define OLED_RESET -1

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  if (!display.begin(OLED_ADDR, true)) {
    Serial.println("❌ SH110X OLED not found!");
    return;
  }
  display.display();
  delay(2000);
}

void displayStatus() {
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print(getCurrentTime());

  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print(getCurrentDate());

  if (isConnectedToInternet()) {
    drawWiFiIcon(110, 0);
  } else {
    drawDisconnectedIcon(110, 0);
  }

  display.display();
}

void drawWiFiIcon(int x, int y) {
  display.fillCircle(x + 3, y + 6, 2, SH110X_WHITE);
  display.drawLine(x, y + 4, x + 6, y + 4, SH110X_WHITE);
  display.drawLine(x - 2, y + 2, x + 8, y + 2, SH110X_WHITE);
  display.drawLine(x - 4, y, x + 10, y, SH110X_WHITE);
}

void drawDisconnectedIcon(int x, int y) {
  display.drawLine(x, y, x + 10, y + 10, SH110X_WHITE);
  display.drawLine(x + 10, y, x, y + 10, SH110X_WHITE);
}
