#include "MqttManager.h"

MQTTManager::MQTTManager(const char* mqtt_server, const char* topic)
    : _mqtt_server(mqtt_server),
      _topic(topic), 
      _client(_espClient) {
}

void MQTTManager::setup() {
    _client.setServer(_mqtt_server, 1883);
}

void MQTTManager::reconnect() {
    while ( !_client.connected() ) {
        String clientId = String("esiot-2122-client") + String(random(0xfffff), HEX);
        if ( _client.connect(clientId.c_str()) ) {
            _client.subscribe(_topic);
        } else {
            delay(500);
        }
    }
}

boolean MQTTManager::publish(const char* msg) {
    return _client.publish(_topic, msg);
}