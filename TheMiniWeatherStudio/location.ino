#include "config.h"

void fetchLocationName() {
  if (WiFi.status() != WL_CONNECTED) return;

  // FREE reverse geocoding (no API key)
  String url = "https://nominatim.openstreetmap.org/reverse?";
  url += "format=json";
  url += "&lat=" + String(LATITUDE, 4);
  url += "&lon=" + String(LONGITUDE, 4);

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, url);

  int code = http.GET();
  if (code == 200) {
    String payload = http.getString();

    DynamicJsonDocument doc(4096);
    if (deserializeJson(doc, payload) == DeserializationError::Ok) {
      Serial.print("Payload from location: ");
      Serial.println(payload);
      if (doc["address"]["city"]) {
        LOCATION_NAME = doc["address"]["city"].as<String>();
      } else if (doc["address"]["town"]) {
        LOCATION_NAME = doc["address"]["town"].as<String>();
      } else if (doc["address"]["village"]) {
        LOCATION_NAME = doc["address"]["village"].as<String>();
      }
    }
  }

  http.end();
}
