from flask import Flask, jsonify, request
import random
import json
from paho.mqtt import client as mqtt_client
from flask_cors import CORS
import serial

app = Flask(__name__)
CORS(app)  # Abilita CORS per tutte le route

messages = []  # Lista per memorizzare i messaggi ricevuti da MQTT
status = 'ALARM_TO_LOW'
valve_opening_level = 0

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
            water_level = payload_dict # potrebbe volerci: payload_dict.get('water_level')
            messages.append({
                'water_level': water_level,
                'valve_opening_level': valve_opening_level,
                'system_status': status
            })
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

#   In questo codice:
# - Abbiamo definito un endpoint /api/send_value che accetta richieste POST.
# - Quando viene inviata una richiesta POST a questo endpoint, il valore viene estratto dal corpo della richiesta JSON.
# - Il valore estratto viene quindi passato alla funzione send_value_to_arduino per essere inviato all'Arduino tramite la porta seriale.
# - Infine, viene restituita una risposta JSON per confermare che il valore è stato inviato con successo all'Arduino.
# - Assicurati di aggiornare la porta seriale (/dev/ttyUSB0) e il baud rate (9600) secondo la tua configurazione.
def send_value_to_arduino(value):
    try:
        # Apre la porta seriale verso Arduino (verifica la porta seriale corretta)
        ser = serial.Serial('/dev/ttyUSB0', 9600)  # Assicurati di usare la porta seriale corretta
        # Invia il valore tramite la porta seriale
        # ser.write(str(value).encode())
        # Converti il valore in una stringa JSON
        json_value = json.dumps(value)
        # Invia il valore tramite la porta seriale
        ser.write(json_value.encode())
        # Chiudi la porta seriale
        ser.close()
        print(f"Value {value} sent to Arduino successfully")
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
    except Exception as e:
        print(f"Error: {e}")

@app.route('/api/send_value', methods=['POST'])
def send_value():
    try:
        data = request.get_json()
        #value = data['value']
        send_value_to_arduino(data)
        return jsonify({"message": "Value sent successfully to Arduino"})
    except Exception as e:
        return jsonify({"error": str(e)}), 400
######################################################################
if __name__ == '__main__':
    app.run(debug=True)
