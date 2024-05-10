document.addEventListener("DOMContentLoaded", function() {

    let dataWater = []; // List of water level values over time
    let valve; // opening level valve
    let system_status;
    let WL4 = 30; // TODO:set-correct-value. Water Level 4 max-high of the river
    let frequency = 10000; // Frequency to be received from the server (10000 = 10 sc default)
    let waterLevelChart; 

    // Funzione per ottenere i messaggi dal server Flask
    function getMessages() {
        fetch('http://127.0.0.1:5000/api/messages')
            .then(response => response.json())
            .then(data => updateDashboard(data))
            .catch(error => console.error('Errore durante il recupero dei messaggi:', error));
    }

    // Funzione per inviare un messaggio al server Flask
    function sendMessage(valve) {
        const dato = {
            value: valve
        }

        const opzioni = {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify(dato)
        }

        fetch('http://127.0.0.1:5000/api/send_value', opzioni)
            .then(response => {
                if(!response.ok){
                    throw new Error('Errore durante l\'invio del valore al server');
                }
                console.log('Valore inviato con successo al server');
            })
            .catch(error => console.error('Errore durante l\'invio del valore al server'));
    }

    function drawChart(labels, data) {
        const graph = document.getElementById('graph').getContext('2d');
        return new Chart(graph, {
            type: 'line',
            data: {
                labels: labels,
                datasets: [{
                    label: 'Water Level',
                    data: data,
                    borderColor: 'blue',
                    borderWidth: 1,
                    fill: true
                }]
            },
            options: {
                scales: {
                    y: { beginAtZero: true }
                }
            }
        });
    }

    // Funzione per aggiornare la dashboard con i dati ricevuti
    function updateDashboard(data) {

        // Processing data
        data.forEach(element => {
            frequency = element.frequency;
            valve = element.valve_opening_level;
            system_status = element.system_status;
            element = element.water_level;
            dataWater.push(element);
        });

        if (waterLevelChart) {
            // se il grafico esiste aggionra solo i dati
            waterLevelChart.data.labels = Array.from({ length: dataWater.length }, (_, i) => i + 1);
            waterLevelChart.data.datasets[0].data = dataWater;
            waterLevelChart.update();

        } else {
            // se il grafico non esiste ne crea uno
            waterLevelChart = drawChart(Array.from({ length: dataWater.length }, (_, i) => i + 1), dataWater);
        }

        // Update System Status
        const systemStatus = document.getElementById('status');
        systemStatus.textContent = system_status;

        // Update Valve Opening Level
        const valveLevel = document.getElementById('valveLevel');
        valveLevel.value = valve;

        // Send Valve Opening Level
        const setValveButton = document.getElementById("manual");
        setValveButton.addEventListener('click', function() {
            valve = valveLevel.value;
            // Send API request to update valve opening level
            sendMessage(valve);
        });

        // Send Valve Opening Level
        const automatic = document.getElementById("automatic");
        setValveButton.addEventListener('click', function() {
            // Send API request to bring back algorithm control
            // TODO: creare l'endpoint
            fetch('http://127.0.0.1:5000/api/automatic')
        });

        // Update Water Level Status
        const water = document.getElementById("water");
        const valueWater = document.getElementById("value");
        water.style.opacity = 1;
        valueWater.textContent = Math.round((dataWater[dataWater.length-1]/WL4)*100) + "%";
        water.style.height = valueWater.textContent;

        // Call getMessages() again after the received frequency
        setTimeout(getMessages, frequency);
    }

    // Chiama la funzione per ottenere i messaggi e aggiornare la dashboard
    getMessages();
});