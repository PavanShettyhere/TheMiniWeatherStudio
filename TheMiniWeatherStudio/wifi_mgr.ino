#include "config.h"

bool wifiSTAConnected = false;
String staIP = "";
String apIP  = "";

// ---- Backwards-compatible aliases (so existing code keeps working) ----
bool wifiConnected = false;   // alias: true when STA connected
String wifiIP = "";
int wifiRSSI = 0;
static bool apStarted = false;

static unsigned long lastAttemptMs = 0;
static unsigned long lastStatusMs  = 0;

static const unsigned long STA_TRY_WINDOW_MS = 15000;   // try STA for 15s at boot/attempt
static const unsigned long RETRY_EVERY_MS    = 30000;   // retry STA every 30s if failed

static bool tryingSTA = false;
static unsigned long tryStartMs = 0;

static void startAP() {
  if (apStarted) return;

  WiFi.softAP(AP_SSID, AP_PASS);
  apIP = WiFi.softAPIP().toString();
  apStarted = true;

  Serial.print("AP started. SSID: ");
  Serial.print(AP_SSID);
  Serial.print("  IP: ");
  Serial.println(apIP);
}


static void startSTATry() {
  tryingSTA = true;
  tryStartMs = millis();

  WiFi.disconnect(true);      // 🔧 ensure clean state
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Trying STA...");
  lastAttemptMs = millis();
}


void wifiBeginSmart() {
  WiFi.persistent(false);
  WiFi.setAutoReconnect(true);
  WiFi.mode(WIFI_AP);        // start AP first
  startAP();
  startSTATry();             // immediately try STA too
}

void wifiLoopSmart() {
  unsigned long now = millis();

  // status refresh
  if (now - lastStatusMs >= 1500) {
    lastStatusMs = now;

    wl_status_t st = WiFi.status();
    wifiSTAConnected = (st == WL_CONNECTED);

    if (wifiSTAConnected) {
      staIP = WiFi.localIP().toString();
      wifiRSSI = WiFi.RSSI();
    } else {
      staIP = "";
      wifiRSSI = 0;
    }

    // aliases used by your existing /api/sys
    wifiConnected = wifiSTAConnected;
    wifiIP = staIP;
  }

  // if connected, nothing else needed
  if (wifiSTAConnected) {
    tryingSTA = false;
    apStarted=false;
    return;
  }


  // if we are currently trying STA, time it out
  if (tryingSTA) {
    if (now - tryStartMs > STA_TRY_WINDOW_MS) {
      tryingSTA = false;

      // go AP-only to avoid ADC2/WiFi clashes and reduce noise
      WiFi.disconnect(true);
      WiFi.mode(WIFI_AP);
      startAP();

      Serial.println("STA failed -> AP-only mode. Will retry STA later.");
      lastAttemptMs = now;
    }
    return;
  }

  // retry STA periodically (while staying AP-only between attempts)
  if (now - lastAttemptMs >= RETRY_EVERY_MS) {
    startSTATry();
  }
}

void setupWiFiManager() { wifiBeginSmart(); }
void loopWiFiManager()  { wifiLoopSmart(); }
