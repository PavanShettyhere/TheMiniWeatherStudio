#include "config.h"

uint8_t oledPage = 0;
unsigned long lastPageSwitchMs = 0;
const unsigned long PAGE_INTERVAL_MS = 5000;

// Tiny 8x8 icons (very simple)
static const uint8_t ICON_THERM[8] = {
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b01110000,
  0b01110000,
  0b00100000
};

static const uint8_t ICON_DROP[8] = {
  0b00100000,
  0b00100000,
  0b01010000,
  0b01010000,
  0b10001000,
  0b10001000,
  0b01110000,
  0b00100000
};

static const uint8_t ICON_WIND[8] = {
  0b00000000,
  0b01111000,
  0b00001000,
  0b11111000,
  0b00000000,
  0b01111000,
  0b00001000,
  0b00000000
};

static void drawPotBar(int x, int y, int w, int h, int pct) {
  if (pct < 0) pct = 0; if (pct > 100) pct = 100;
  display.drawRect(x, y, w, h, SSD1306_WHITE);
  int fill = (w - 2) * pct / 100;
  display.fillRect(x + 1, y + 1, fill, h - 2, SSD1306_WHITE);
}

void oledPagesLoop() {
  unsigned long now = millis();

  if (oledUsePotSelector) {
    // Pot chooses page
    // 0..100 -> 0..2
    uint8_t p = (potPercent < 25) ? 0 : (potPercent < 50 ? 1 : (potPercent < 75 ? 2 : 3));
    oledPage = p;
  } else {
    // Auto rotate
    if (now - lastPageSwitchMs >= PAGE_INTERVAL_MS) {
      lastPageSwitchMs = now;
      oledPage = (oledPage + 1) % 4;
    }
  }
}

void drawOLEDPage(uint8_t page) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (page == 0) {
    // Page 1: Time + Room
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print(getLocalTimeString());

    display.setTextSize(1);
    display.setCursor(0, 18);
    display.print(getLocalDateString());
    display.print(" | ");
    display.print(LOCATION_NAME);

    // Icons
    display.drawBitmap(0, 28, ICON_THERM, 8, 8, SSD1306_WHITE);
    display.setCursor(10, 28);
    display.print("T: ");
    if (isnan(roomTempC)) display.print("--.-C");
    else { display.print(roomTempC, 1); display.print("C"); }

    display.drawBitmap(0, 40, ICON_DROP, 8, 8, SSD1306_WHITE);
    display.setCursor(10, 40);
    display.print("H: ");
    if (isnan(roomHum)) display.print("--%");
    else { display.print(roomHum, 0); display.print("%"); }

    // Today min/max quick
    display.setCursor(0, 56);
    display.print("Min/Max ");
    if (!isnan(todayMinT)) { display.print(todayMinT,0); display.print("/"); display.print(todayMaxT,0); display.print("C"); }
    else display.print("--/--");

  } else if (page == 1) {
    // Page 2: Weather + Location
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Location: ");
    display.print(LOCATION_NAME);

    display.setCursor(0, 12);
    display.print("Outside: ");
    display.print(weatherTemp);

    display.drawBitmap(0, 24, ICON_WIND, 8, 8, SSD1306_WHITE);
    display.setCursor(10, 24);
    display.print(weatherDesc);

    display.setCursor(0, 38);
    display.print("WiFi: ");
    display.print(wifiConnected ? "OK" : "DOWN");
    if (wifiConnected) {
      display.print(" ");
      display.print(wifiRSSI);
      display.print("dBm");
    }

    display.setCursor(0, 56);
    display.print(userMessage);

  } else if(page ==2) {
    // Page 3: Pot + GPIO
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Pot: ");
    display.print(potPercent);
    display.print("%");
    drawPotBar(0, 12, 128, 10, potPercent);

    display.setCursor(0, 28);
    display.print("GPIO4:");
    display.print(pinState[indexOfPin(4)] ? "ON " : "OFF");
    display.print("  GPIO5:");
    display.print(pinState[indexOfPin(5)] ? "ON" : "OFF");

    display.setCursor(0, 40);
    display.print("GPIO16:");
    display.print(pinState[indexOfPin(16)] ? "ON " : "OFF");

    display.setCursor(0, 56);
    display.print(oledUsePotSelector ? "Mode: POT" : "Mode: AUTO");
  }
  else if (page == 3) {
  drawWiFiQRScreen();
  return; // this function already display.display()
}


  display.display();
}
