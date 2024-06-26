#include <WiFiManager.h>
#include <MqttManager.h>
#include <Sonar.h>
#define MSG_BUFFER_SIZE  50

/* wifi network info, replace these with yours */
const char* ssid = "Oliver";
const char* password = "zxha6909";

/* MQTT server address and topic */
const char* mqtt_server = "broker.emqx.io";
const char* topic = "eps32/topic"; 
// TODO: creare topic per la frequenza !

/* Sonar */
#define TRIGGER_PIN  D0      //replace with real value
#define ECHO_PIN D1          //replace with real value
const long max_time = 20000; //replace with real value

/* Define Led */
#define GREEN_LED D2
#define RED_LED D3

#define F1 10000

WiFiManager wifiManager(ssid, password);
MQTTManager mqttManager(mqtt_server, topic);
Sonar sonar(ECHO_PIN, TRIGGER_PIN, max_time);

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];
unsigned long frequency = F1; // default value modifiable by the server

void setup() {
  Serial.begin(115200);
  wifiManager.setup();
  mqttManager.setup();
  randomSeed(micros());

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}

bool send_distance(float val);

void loop() {
  // reconnect to MQTT if connection lost
  mqttManager.reconnect();
  
  unsigned long now = millis();
  // if is time, mesure distance and send data
  if (now - lastMsgTime > frequency) {
    float value = sonar.getDistance();
    bool success = send_distance(value);
    if (success) {
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(RED_LED, LOW);
    } else {
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(RED_LED, HIGH);
    }
    lastMsgTime = millis();
  }
}

bool send_distance(float val) {
  /* creating a msg in the buffer */
    snprintf (msg, MSG_BUFFER_SIZE, "%f", val);

    Serial.println(String("val: ") + val);
    Serial.println(String("Publishing message: ") + msg);
    
    /* publishing the msg */
    return mqttManager.publish(msg); 
}