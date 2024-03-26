#include <WiFiManager.h>
#include <MqttManager.h>
#include <Sonar.h>
#define MSG_BUFFER_SIZE  50

/* wifi network info */
const char* ssid = "Alle";
const char* password = "Franco789?";

/* MQTT server address */
const char* mqtt_server = "broker.emqx.io";

/* MQTT topic */
const char* topic = "eps32/topic";

WiFiManager wifiManager(ssid, password);
MQTTManager mqttManager(mqtt_server, topic);

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup() {
  Serial.begin(115200);
  wifiManager.setup();
  mqttManager.setup();
  randomSeed(micros());
}

void loop() {

  mqttManager.reconnect();
  unsigned long now = millis();
  if (now - lastMsgTime > 10000) {
    lastMsgTime = now;
    value = 10; /* da modificare con il vero valore del livello dell'acqua*/

    /* creating a msg in the buffer */
    snprintf (msg, MSG_BUFFER_SIZE, "#%ld", value);

    Serial.println(String("Publishing message: ") + msg);
    
    /* publishing the msg */
    mqttManager.publish(msg);  
  }

}