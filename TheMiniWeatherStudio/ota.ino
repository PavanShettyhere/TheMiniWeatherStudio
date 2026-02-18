#include "config.h"
#include <ArduinoOTA.h>

void setupOTA() {
  // Optional: device name shown in Arduino IDE network ports
  ArduinoOTA.setHostname("Deltoro");

  // Optional: OTA password (recommended)
  ArduinoOTA.setPassword("orotled");  

  ArduinoOTA
    .onStart([]() {
      String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
      Serial.println("OTA Start updating " + type);

      // Optional: show OTA status on OLED
      userMessage = "OTA updating...";
      drawOLEDPage(1);
    })
    .onEnd([]() {
      Serial.println("\nOTA End");
      userMessage = "OTA done. Rebooting";
      drawOLEDPage(1);
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      int pct = (total > 0) ? (progress * 100 / total) : 0;
      Serial.printf("OTA Progress: %u%%\r", pct);

      // Optional: show % on OLED bottom line
      userMessage = "OTA " + String(pct) + "%";
    })
    .onError([](ota_error_t error) {
      Serial.printf("OTA Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");

      userMessage = "OTA error";
      drawOLEDPage(1);
    });

  ArduinoOTA.begin();
  Serial.println("OTA ready. Upload via Arduino IDE Network Port.");
}

void handleOTA() {
  ArduinoOTA.handle();
}
