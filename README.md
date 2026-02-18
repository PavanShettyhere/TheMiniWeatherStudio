# TheMiniWeatherStudio 🌦️📟 (ESP32)

An ESP32-based mini “weather studio” that combines:
- Outdoor weather (via Open-Meteo API)
- Indoor temperature & humidity (DHT11)
- OLED dashboard pages (time/date, weather, GPIO status, Wi-Fi QR)
- Web dashboard + API endpoints
- OTA updates (ArduinoOTA + Web OTA upload)
- Preferences storage (message/location/mode)

---

## Features

### ✅ OLED Dashboard (128x64 SSD1306)
Multiple pages (auto-rotating or selectable by potentiometer):
1. **Time + Date + Location + Room temp/humidity**
2. **Outside weather + Wi-Fi status + message**
3. **Potentiometer + GPIO status + mode**
4. **Wi-Fi QR screen** to join the ESP32 AP quickly

### ✅ Web Dashboard (ESP32 WebServer)
- Modern web UI (served from the ESP32)
- Live values for:
  - Outdoor weather temperature & wind (Open-Meteo)
  - Indoor temp/humidity (DHT11)
  - Potentiometer %
  - GPIO control/status
  - System/Wi-Fi status
- Basic Auth protected (default user/pass shown below)

### ✅ Smart Wi-Fi Mode + AP fallback
- Starts a hotspot if STA Wi-Fi fails
- Shows a QR code on OLED to connect to AP

### ✅ OTA Updates
- **ArduinoOTA**: upload from Arduino IDE network port
- **Web OTA**: upload firmware `.bin` from `/update`

### ✅ Stored Settings (flash)
Using `Preferences`:
- Web message text (shown on OLED)
- Location name override
- OLED page mode (AUTO vs POT selection)

---

## Parts List
- ESP32 Dev board
- SSD1306 OLED (I2C, 128x64, typically address `0x3C`)
- DHT11 temperature/humidity sensor
- 10k potentiometer (for page selection)
- LEDs/Relay module (optional) for GPIO outputs
- Breadboard + jumper wires
- 5V/USB power (ESP32 regulates to 3.3V)

---

## Pin Diagram / Wiring

### OLED (I2C SSD1306)
- **SDA → GPIO21**
- **SCL → GPIO22**
- **VCC → 3.3V**
- **GND → GND**
- I2C address used: **0x3C**

### DHT11
- **DATA → GPIO17**
- **VCC → 3.3V**
- **GND → GND**

### Potentiometer (10k)
- One end → **3.3V**
- Other end → **GND**
- Middle (wiper) → **GPIO34** (ADC1)

### GPIO outputs (examples)
Configured pins:
- **GPIO4**
- **GPIO5**
- **GPIO16**

Use these for LEDs (with resistor) or relay control (with proper driver module).

---

## Default Credentials / Security Notes

### Web Basic Auth
- **username:** `admin`
- **password:** `esp32`

### ArduinoOTA
- Hostname: `Deltoro`
- Password: `orotled`

⚠️ **Change these defaults before real deployment.**

---

## Setup Instructions

1. Install Arduino libraries:
   - `Adafruit SSD1306`
   - `Adafruit GFX`
   - `ArduinoJson`
   - `DHT11` (the library used by `#include <DHT11.h>`)

2. Create your Wi-Fi secrets file:
   - Copy `secrets_example.h` → `secrets.h`
   - Put your SSID/password in `secrets.h`
   - **Do not commit `secrets.h`** (it should be in `.gitignore`)

3. Open the sketch:
   - `firmware/TheMiniWeatherStudio/TheMiniWeatherStudio.ino`
   - Select ESP32 board + COM port
   - Upload

4. Access web UI:
   - Check Serial Monitor for the IP
   - Open `http://<ESP32-IP>/`
   - OTA page: `http://<ESP32-IP>/update`

---

## API Endpoints
- `GET  /api/status`
- `POST /api/gpio`
- `POST /api/message`
- `GET  /api/dht`
- `GET  /api/pot`
- `GET  /api/weather`
- `GET  /api/sys`

---

## Purpose / Why this exists
This project is a compact “desk weather station + control panel”:
- Glanceable OLED pages for time, indoor comfort, and outdoor conditions
- Web dashboard for control and monitoring
- OTA updates for quick iteration without cables

---

## Credits
- Weather data: Open-Meteo
- Reverse geocoding: Nominatim (OpenStreetMap)
- QR generation: Nayuki QR Code generator (C implementation)

---

## License
Choose a license (MIT recommended) if you want others to reuse it.
