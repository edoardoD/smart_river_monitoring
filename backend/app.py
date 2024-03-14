from flask import Flask, jsonify
import random
import json
from paho.mqtt import client as mqtt_client
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # Abilita CORS per tutte le route

messages = []  # Lista per memorizzare i messaggi ricevuti da MQTT
status = 'ALARM_TO_LOW'

# fake dati per testare js
messages.append({
    'water_level': 10,
    'valve_opening_level': 75,
    'system_status': status
})

# Configurazione del broker MQTT
broker = 'broker.emqx.io'
port = 1883
topic = "eps32/topic"
# Generate a Client ID with the subscribe prefix.
client_id = f'subscribe-{random.randint(0, 100)}'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        try:
            # Converti il payload in un dizionario Python
            payload_dict = json.loads(msg.payload.decode())
            # Aggiungi il messaggio alla lista, la conversione json viene fatta dopo, prima dell'invio
            messages.append(payload_dict)
            # Converti il dizionario in una stringa JSON
            json_payload = json.dumps(payload_dict)
            print(json_payload)
        except json.decoder.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")

    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()

# Endpoint per ottenere i messaggi
@app.route('/api/messages', methods=['GET'])
def get_messages():
    return jsonify(messages)

if __name__ == '__main__':
    app.run(debug=True)
