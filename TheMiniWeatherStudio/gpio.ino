#include "config.h"

int indexOfPin(int pin) {
  for (int i = 0; i < pinCount; i++) {
    if (pins[i] == pin) return i;
  }
  return -1;
}

bool checkAuth() {
  if (!server.authenticate(www_username, www_password)) {
    server.requestAuthentication();
    return false;
  }
  return true;
}
