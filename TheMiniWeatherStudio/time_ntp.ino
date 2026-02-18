#include "config.h"

String getLocalTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "--:--:--";
  char buf[16];
  strftime(buf, sizeof(buf), "%H:%M:%S", &timeinfo);
  return String(buf);
}

String getLocalDateString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "----/--/--";
  char buf[16];
  strftime(buf, sizeof(buf), "%Y-%m-%d", &timeinfo);
  return String(buf);
}

void setupTime() {
  configTzTime(TZ_INFO, NTP1, NTP2);

  struct tm timeinfo;
  Serial.print("Waiting for NTP sync");
  for (int i = 0; i < 30; i++) {
    if (getLocalTime(&timeinfo)) {
      Serial.println("\nTime synced!");
      Serial.printf("Local time: %04d-%02d-%02d %02d:%02d:%02d\n",
                    timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                    timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
      Serial.printf("DST active? tm_isdst=%d\n", timeinfo.tm_isdst);
      return;
    }
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nNTP sync not ready yet (will update later)");
}
