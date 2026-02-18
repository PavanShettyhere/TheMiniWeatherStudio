#include "config.h"
#include "qrcodegen.h"

void drawWiFiQRScreen() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // -------- Text --------
  display.setCursor(0, 0);
  display.print("Scan to join WiFi");

  display.setCursor(0, 10);
  display.print(AP_SSID);

  display.setCursor(0, 22);
  display.print("Open:");

  display.setCursor(0, 32);
  display.print("http://");
  display.print(apIP.length() ? apIP : "192.168.4.1");

  if (wifiSTAConnected && staIP.length()) {
    display.setCursor(0, 44);
    display.print("STA:");
    display.print(staIP);
  }

  // -------- WiFi QR payload --------
  String payload = String("WIFI:T:WPA;S:") + AP_SSID + ";P:" + AP_PASS + ";;";

  // -------- QR generation (Nayuki C version) --------
  uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
  uint8_t temp[qrcodegen_BUFFER_LEN_MAX];

  bool ok = qrcodegen_encodeText(
    payload.c_str(),
    temp,
    qrcode,
    qrcodegen_Ecc_LOW,
    qrcodegen_VERSION_MIN,
    3,                      // Version 3 → 29x29
    qrcodegen_Mask_AUTO,
    true
  );

  if (!ok) {
    display.display();
    return;
  }

  int size = qrcodegen_getSize(qrcode);
  int scale = 2;             // 29*2 = 58px
  int x0 = 128 - (size * scale);
  int y0 = 64  - (size * scale);

  // -------- Draw QR --------
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      if (qrcodegen_getModule(qrcode, x, y)) {
        display.fillRect(
          x0 + x * scale,
          y0 + y * scale,
          scale,
          scale,
          SSD1306_WHITE
        );
      }
    }
  }

  display.display();
}
