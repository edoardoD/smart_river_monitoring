#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : _ssid(ssid), 
      _password(password) {
}

void WiFiManager::setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

IPAddress WiFiManager::getLocalIP() {
    return WiFi.localIP();
}