#include "config.h"

const int HIST_LEN = 60;
float tempHist[HIST_LEN];
float humHist[HIST_LEN];
uint8_t histCount = 0;
uint8_t histHead = 0;
unsigned long lastHistSampleMs = 0;

float todayMinT = NAN, todayMaxT = NAN, todayAvgT = NAN;
float todayMinH = NAN, todayMaxH = NAN, todayAvgH = NAN;
uint16_t todayCount = 0;
int todayYMD = 0;

static int ymdNow() {
  struct tm t;
  if (!getLocalTime(&t)) return 0;
  return (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday;
}

static void todayReset(int ymd) {
  todayYMD = ymd;
  todayCount = 0;
  todayMinT = todayMaxT = todayAvgT = NAN;
  todayMinH = todayMaxH = todayAvgH = NAN;
}

void historySetup() {
  for (int i = 0; i < HIST_LEN; i++) { tempHist[i] = NAN; humHist[i] = NAN; }
  todayReset(ymdNow());
}

static void pushHist(float t, float h) {
  tempHist[histHead] = t;
  humHist[histHead] = h;
  histHead = (histHead + 1) % HIST_LEN;
  if (histCount < HIST_LEN) histCount++;
}

static void updateToday(float t, float h) {
  int ymd = ymdNow();
  if (ymd != 0 && ymd != todayYMD) todayReset(ymd);

  if (todayCount == 0) {
    todayMinT = todayMaxT = t;
    todayMinH = todayMaxH = h;
    todayAvgT = t;
    todayAvgH = h;
    todayCount = 1;
    return;
  }

  todayCount++;
  if (t < todayMinT) todayMinT = t;
  if (t > todayMaxT) todayMaxT = t;
  if (h < todayMinH) todayMinH = h;
  if (h > todayMaxH) todayMaxH = h;

  // incremental average
  todayAvgT += (t - todayAvgT) / todayCount;
  todayAvgH += (h - todayAvgH) / todayCount;
}

void historyLoop() {
  // sample once per minute
  unsigned long now = millis();
  if (now - lastHistSampleMs < 60000UL) return;
  lastHistSampleMs = now;

  if (isnan(roomTempC) || isnan(roomHum)) return;
  pushHist(roomTempC, roomHum);
  updateToday(roomTempC, roomHum);
}
