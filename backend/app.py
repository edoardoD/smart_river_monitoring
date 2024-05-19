from flask import Flask, jsonify, request
from paho.mqtt import client as mqtt_client
from flask_cors import CORS
import random
import json
import serial
import asyncio

app = Flask(__name__)
CORS(app)  # Abilita CORS per tutte le route

messages = []  # Lista per memorizzare i messaggi ricevuti da MQTT (non ancora letti da js)
status = 'UNDEFINED'     # TODO: improve with real status
valve_opening_level = 0  # TODO: improve with real valve opening level [%]
frequency = 5000        # TODO: improve, 5 000 ms = 5sec solo per i test [sec]
algorithm = True

# Configurazione del broker MQTT
broker = 'broker.emqx.io'
port = 1883
topic = "eps32/topic"
# Generate a Client ID with the subscribe prefix.
client_id = f'subscribe-{random.randint(0, 100)}'


# crea un client e lo connette al nostro brokr
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

# sottoscrive il client creato al topic esp32
def subscribe(client: mqtt_client):
    global algorithm
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        try:
            water_level = float(msg.payload.decode())
            if algorithm==True:
                update_system_state(water_level)
            messages.append({
                'frequency': frequency,
                'water_level': water_level,
                'valve_opening_level': valve_opening_level,
                'system_status': status
            })
        except json.decoder.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")

    client.subscribe(topic)
    client.on_message = on_message

def update_system_state(water_level):
    global status, valve_opening_level, frequency
    WL1, WL2, WL3, WL4 = 0.1, 0.2, 0.3, 0.4
    F1, F2 = 15000, 10000

    if water_level >= WL1 and water_level <= WL2:
        status = 'NORMAL'
        valve_opening_level = 25
        frequency = F1
    elif water_level < WL1:
        status = 'ALARM-TOO-LOW'
        valve_opening_level = 0
    elif water_level > WL2:
        if water_level <= WL3:
            status = 'PRE-ALARM-TOO-HIGH'
            frequency = F2
        elif water_level <= WL4:
            status = 'ALARM-TOO-HIGH'
            valve_opening_level = 50
        else:
            status = 'ALARM-TOO-HIGH-CRITIC'
            valve_opening_level = 100
    send_value_to_arduino(valve_opening_level)


async def main():
    client = connect_mqtt()
    subscribe(client)
    client.loop_start()
    app.run(debug=True)

# Endpoint per ottenere i messaggi
@app.route('/api/messages', methods=['GET'])
def get_messages():
    json_msg = jsonify(messages)
    messages.clear()
    return json_msg

#   In questo codice:
# - Abbiamo definito un endpoint /api/send_value che accetta richieste POST.
# - Quando viene inviata una richiesta POST a questo endpoint, il valore viene estratto dal corpo della richiesta JSON.
# - Il valore estratto viene quindi passato alla funzione send_value_to_arduino per essere inviato all'Arduino tramite la porta seriale.
# - Infine, viene restituita una risposta JSON per confermare che il valore è stato inviato con successo all'Arduino.
# - Assicurati di aggiornare la porta seriale (/dev/ttyUSB0) e il baud rate (9600) secondo la tua configurazione.
def send_value_to_arduino(value):
    try:
        with serial.Serial('COM6', 115200, dsrdtr=True, rtscts = True) as ser:

            #Invia il valore tramite la porta seriale
            value_json = {"value" : int(value)}
            json_msg = json.dumps(value_json)
            ser.write((json_msg + '\n').encode())
            # ser.write(json_msg.encode())
            #Chiudi la porta seriale
            ser.close()
            print(f"Value {json_msg} sent to Arduino successfully")
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
    except Exception as e:
        print(f"Error: {e}")

@app.route('/api/send_value', methods=['POST'])
def send_value():
    global algorithm, valve_opening_level
    try:
        data = request.get_json()
        value = data['value']
        valve_opening_level = data['value']
        send_value_to_arduino(value)
        if algorithm == True:
            algorithm = False
        return jsonify({"message": "Value sent successfully to Arduino"})
    except Exception as e:
        return jsonify({"error": str(e)}), 400
    
@app.route('/api/automatic', methods=['GET'])
def automatic():
    global algorithm
    if algorithm == False:
        algorithm = True
    return jsonify({"message": "Automatic endpoint accessed"})

if __name__ == '__main__':
    asyncio.run(main())
