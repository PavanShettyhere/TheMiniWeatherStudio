#pragma once
#include "secrets.h"
#include <Preferences.h>
#include <Update.h>


#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>

#include <DHT11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ===================== WiFi manager =====================
extern bool wifiConnected;
extern String wifiIP;
extern int wifiRSSI;



// ===================== Storage (Preferences) =====================
extern Preferences prefs;


// User configurable settings stored in flash
extern String LOCATION_NAME;       // shown on OLED + Web
extern bool locationOverride;      // if true, use stored name
extern bool oledUsePotSelector;    // if true, pot selects page


extern float todayMinT, todayMaxT, todayAvgT;
extern float todayMinH, todayMaxH, todayAvgH;
extern uint16_t todayCount;
extern int todayYMD;               // YYYYMMDD



// ===================== OLED pages =====================
extern uint8_t oledPage;           // 0..2
extern unsigned long lastPageSwitchMs;
extern const unsigned long PAGE_INTERVAL_MS;


// ===================== Potentiometer =====================
extern const int POT_PIN;
extern int potRaw;        // 0..4095
extern int potPercent;    // 0..100

extern unsigned long lastPotReadMs;
extern const unsigned long POT_INTERVAL_MS;

// ===================== Basic Auth =====================
extern const char* www_username;
extern const char* www_password;

// ===================== Time (NTP) =====================
extern const char* TZ_INFO;
extern const char* NTP1;
extern const char* NTP2;

// ===================== Weather (Open-Meteo) =====================
extern const float LATITUDE;
extern const float LONGITUDE;
extern String LOCATION_NAME;

// ===================== Web Server =====================
extern WebServer server;

// ===================== GPIO Control =====================
extern const int pins[];
extern const int pinCount;
extern bool pinState[];

// ===================== OLED =====================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

extern Adafruit_SSD1306 display;

// ===== AP (ESP32 hotspot) =====
#define AP_SSID "GreatWall-ESP32"
#define AP_PASS "12345678"   // min 8 chars

// ===== Smart WiFi fallback =====
extern bool wifiSTAConnected;
extern String staIP;
extern String apIP;

void wifiBeginSmart();
void wifiLoopSmart();
void drawWiFiQRScreen();


// =================== Display Data =====================
extern String weatherDesc;
extern String weatherTemp;
extern String userMessage;

// ===================== Timers =====================
extern unsigned long lastTimeDrawMs;
extern unsigned long lastWeatherFetchMs;

extern const unsigned long DRAW_INTERVAL_MS;
extern const unsigned long WEATHER_INTERVAL_MS;

// ===================== DHT11 =====================
extern const int DHT_PIN;
extern DHT11 dht11;

extern float roomTempC;
extern float roomHum;

extern unsigned long lastDhtReadMs;
extern const unsigned long DHT_INTERVAL_MS;

void setupDHT();
void readDHT();

// ===================== Shared functions =====================
bool checkAuth();
int indexOfPin(int pin);

String getLocalTimeString();
String getLocalDateString();

void setupOTA();
void handleOTA();

void setupTime();
void fetchWeather();
void drawOLED();
void fetchLocationName();

void setupWebRoutes();  // registers all server.on(...)

//POT
void setupPot();
void readPot();

void oledPagesLoop();              // page switching logic
void drawOLEDPage(uint8_t page);   // draw one page

// ===================== Web extras =====================
void setupWebOTA();                // /update routes

void loadSettings();
void saveUserMessage();
void saveLocationOverride();
void saveOledMode();

void setupWiFiManager();
void loopWiFiManager();
