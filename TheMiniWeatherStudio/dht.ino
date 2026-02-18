#include "config.h"

void setupDHT() {
  Serial.println("DHT started");
}

void readDHT() {
  int temperature = 0;
  int humidity = 0;

  // Best method: read both at once (faster + consistent)
  int result = dht11.readTemperatureHumidity(temperature, humidity);  // :contentReference[oaicite:3]{index=3}

  if (result != 0) {
    Serial.print("DHT11 error: ");
    Serial.println(DHT11::getErrorString(result));                    // :contentReference[oaicite:4]{index=4}
    return; // keep last good values
  }

  // DHT11 is integer resolution, but we store as float for easy formatting
  roomTempC = (float)temperature;
  roomHum   = (float)humidity;

  Serial.print("Room: ");
  Serial.print(roomTempC, 1);
  Serial.print("C, ");
  Serial.print(roomHum, 0);
  Serial.println("%");
}
