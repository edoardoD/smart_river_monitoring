document.addEventListener("DOMContentLoaded", function() {

    let dataWater = [];
    let valve;
    let system_status;

    // Funzione per ottenere i messaggi dal server Flask
    function getMessages() {
        fetch('http://127.0.0.1:5000/api/messages')
            .then(response => response.json())
            .then(data => updateDashboard(data))
            .catch(error => console.error('Errore durante il recupero dei messaggi:', error));
    }

    // Funzione per aggiornare la dashboard con i dati ricevuti
    function updateDashboard(data) {
        data.forEach(element => {
            valve = element.valve_opening_level;
            system_status = element.system_status;
            element = element.water_level;
            dataWater.push(element);
        });
        // Chart setup
        const graph = document.getElementById('graph').getContext('2d');
        const waterLevelChart = new Chart(graph, {
            type: 'line',
            data: {
                labels: Array.from({ length: dataWater.length }, (_, i) => i + 1),
                datasets: [{
                    label: 'Water Level',
                    data: dataWater,
                    borderColor: 'blue',
                    borderWidth: 1,
                    fill: true
                }]
            },
            options: {
                scales: {
                    y: {
                        beginAtZero: true
                    }
                }
            }
        });

        // Update System Status
        const systemStatus = document.getElementById('status');
        systemStatus.textContent = system_status;

        // Update Valve Opening Level
        const valveControl = document.getElementById('valve-control');
        const valveLevel = document.getElementById('valveLevel');
        valveLevel.value = valve;

        valveControl.addEventListener('input', function() {
            const valveLevel = this.value;
            valveLevel.textContent = valveLevel;
            // TODO: Send API request to update valve opening level
        });
    }

    // Chiama la funzione per ottenere i messaggi e aggiornare la dashboard
    getMessages();
});