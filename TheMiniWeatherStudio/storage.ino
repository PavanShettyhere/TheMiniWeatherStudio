#include "config.h"

Preferences prefs;

//String LOCATION_NAME = "Dortmund";
bool locationOverride = false;
bool oledUsePotSelector = true;

void loadSettings() {
  prefs.begin("grand", false);

  userMessage = prefs.getString("msg", userMessage);
  LOCATION_NAME = prefs.getString("loc", LOCATION_NAME);

  locationOverride = prefs.getBool("loc_ovr", false);
  oledUsePotSelector = prefs.getBool("oled_pot", false);

  // sanitize
  if (userMessage.length() > 24) userMessage = userMessage.substring(0, 24);
  if (LOCATION_NAME.length() > 16) LOCATION_NAME = LOCATION_NAME.substring(0, 16);
}

void saveUserMessage() {
  prefs.putString("msg", userMessage);
}

void saveLocationOverride() {
  prefs.putString("loc", LOCATION_NAME);
  prefs.putBool("loc_ovr", locationOverride);
}

void saveOledMode() {
  prefs.putBool("oled_pot", oledUsePotSelector);
}
