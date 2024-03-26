#ifndef MQTTManager_h
#define MQTTManager_h

#include <PubSubClient.h>
#include <WiFiManager.h>

class MQTTManager {
    public:
        MQTTManager(const char* mqtt_server, const char* topic);
        void setup();
        void reconnect();
        void publish(const char* msg);

    private:
        const char* _mqtt_server;
        const char* _topic;
        WiFiClient _espClient;
        PubSubClient _client;
};

#endif