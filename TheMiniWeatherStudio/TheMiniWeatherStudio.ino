#include "config.h"

// ===================== Definitions (globals) =====================
const char* www_username = "admin";
const char* www_password = "esp32";

// Europe/Berlin DST rules
const char* TZ_INFO = "CET-1CEST,M3.5.0/2,M10.5.0/3";
const char* NTP1 = "pool.ntp.org";
const char* NTP2 = "time.nist.gov";

// Dortmund: 51.5136 N, 7.4653 E
const float LATITUDE = 51.5136;
const float LONGITUDE = 7.4653;

// Chennai 13.0843° N, 80.2705° E
// const float LATITUDE  = 13.0843;
// const float LONGITUDE = 80.2705;

// Web server
WebServer server(80);

// GPIO pins
const int pins[] = { 4, 16, 5 };
const int pinCount = sizeof(pins) / sizeof(pins[0]);
bool pinState[pinCount] = { 0 };

// Potentiometer
const int POT_PIN = 34;  // ADC1 pin recommended
int potRaw = 0;
int potPercent = 0;

unsigned long lastPotReadMs = 0;
const unsigned long POT_INTERVAL_MS = 200;  // smooth UI updates

// OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Display data
String weatherDesc = "Weather: --";
String weatherTemp = "--.- C";
String userMessage = "Type message on web";
String LOCATION_NAME = "Loc...";

// DHT11
const int DHT_PIN = 17;  // change if you wired to another GPIO
DHT11 dht11(DHT_PIN);

float roomTempC = NAN;
float roomHum = NAN;

unsigned long lastDhtReadMs = 0;
const unsigned long DHT_INTERVAL_MS = 2000;  // DHT11 should be read ~1-2s or slower

// Timers
unsigned long lastTimeDrawMs = 0;
unsigned long lastWeatherFetchMs = 0;

const unsigned long DRAW_INTERVAL_MS = 1000;
const unsigned long WEATHER_INTERVAL_MS = 10UL * 60UL * 1000UL;

void setup() {
  Serial.begin(115200);

  // GPIO init
  for (int i = 0; i < pinCount; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
    pinState[i] = false;
  }

  // OLED init
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed (addr 0x3C). Check wiring/address.");
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Booting...");
    display.display();
  }

  wifiBeginSmart();


  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  setupOTA();


  // Time + Weather
  fetchLocationName();
  setupTime();     // NTP + DST
  fetchWeather();  // immediate fetch at boot
  lastWeatherFetchMs = millis();

  setupDHT();
  readDHT();  // first reading at boot

  setupPot();
  readPot();

  setupWiFiManager();
  loadSettings();


  // Web routes
  setupWebRoutes();
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  handleOTA();
  loopWiFiManager();




  unsigned long now = millis();

  // Refresh display each second
  if (now - lastTimeDrawMs >= DRAW_INTERVAL_MS) {
    lastTimeDrawMs = now;
    oledPagesLoop();
    drawOLEDPage(oledPage);   // replace your old drawOLED() call
  }

  if (now - lastPotReadMs >= POT_INTERVAL_MS) {
    lastPotReadMs = now;
    readPot();
  }
  // Fetch weather periodically
  if (now - lastWeatherFetchMs >= WEATHER_INTERVAL_MS) {
    lastWeatherFetchMs = now;
    fetchWeather();
  }

  //DHT Sensor Update Time
  if (now - lastDhtReadMs >= DHT_INTERVAL_MS) {
    lastDhtReadMs = now;
    readDHT();
  }

  wifiLoopSmart();

}
