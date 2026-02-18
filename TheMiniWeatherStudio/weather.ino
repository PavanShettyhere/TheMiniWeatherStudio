#include "config.h"

void fetchWeather() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Weather: WiFi not connected");
    return;
  }

  String url = "https://api.open-meteo.com/v1/forecast?";
  url += "latitude=" + String(LATITUDE, 4);
  url += "&longitude=" + String(LONGITUDE, 4);
  url += "&current_weather=true";

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  Serial.println("Weather GET: " + url);

  if (!http.begin(client, url)) {
    Serial.println("Weather: http.begin failed");
    weatherTemp = "--.-";
    weatherDesc = "begin failed";
    return;
  }

  int code = http.GET();
  Serial.print("Weather HTTP code: ");
  Serial.println(code);

  if (code == 200) {
    String payload = http.getString();

    DynamicJsonDocument doc(4096);
    DeserializationError err = deserializeJson(doc, payload);

    if (!err) {
      float temp = doc["current_weather"]["temperature"] | NAN;
      float wind = doc["current_weather"]["windspeed"] | NAN;

      weatherTemp = String(temp, 1) + "C";
      weatherDesc = "Wi " + String(wind, 1) + " km/h";

      Serial.println("Parsed OK: " + weatherTemp + " / " + weatherDesc);
    } else {
      Serial.print("Weather JSON error: ");
      Serial.println(err.c_str());
      weatherTemp = "--.-";
      weatherDesc = "JSON error";
    }
  } else {
    weatherTemp = "--.-";
    weatherDesc = "HTTP " + String(code);
  }

  http.end();
}
