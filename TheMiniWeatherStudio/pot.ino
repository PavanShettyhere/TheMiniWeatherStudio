#include "config.h"

void setupPot() {
  pinMode(POT_PIN, INPUT);

  // Optional but recommended for more stable ADC behavior:
  analogReadResolution(12); // 0..4095
  analogSetAttenuation(ADC_11db); // full range close to 3.3V
}

static int smoothValue(int prev, int curr, int alphaPercent) {
  // alphaPercent: 0..100 (higher = follow new faster)
  return (prev * (100 - alphaPercent) + curr * alphaPercent) / 100;
}

void readPot() {
  int raw = analogRead(POT_PIN);           // 0..4095
  potRaw = smoothValue(potRaw, raw, 20);   // smoothing (20% new, 80% old)

  int pct = map(potRaw, 0, 4095, 0, 100);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  potPercent = pct;
}
