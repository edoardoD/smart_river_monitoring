document.addEventListener("DOMContentLoaded", function() {

    let dataWater = [];

    // Funzione per ottenere i messaggi dal server Flask
    function getMessages() {
        fetch('http://localhost:5000/api/messages')
            .then(response => response.json())
            .then(data => updateDashboard(data))
            .catch(error => console.error('Errore durante il recupero dei messaggi:', error));
    }

    // Funzione per aggiornare la dashboard con i dati ricevuti
    function updateDashboard(data) {
        dataWater.append(data);
        let lastTen = dataWater.slice(-10);
        // Chart setup
        const graph = document.getElementById('graph').getContext('2d');
        const waterLevelChart = new Chart(graph, {
            type: 'line',
            data: {
                labels: Array.from({ length: 10 }, (_, i) => i + 1),
                datasets: [{
                    label: 'Water Level',
                    data: lastTen,
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
        const systemStatus = document.getElementById('systemStatus');
        systemStatus.textContent = data.systemStatus;

        // Update Valve Opening Level
        const valveControl = document.getElementById('valveControl');
        const valveLevel = document.getElementById('valveLevel');

        valveControl.value = data.valveOpeningLevel;
        valveLevel.textContent = data.valveOpeningLevel;

        valveControl.addEventListener('input', function() {
            const valveLevel = this.value;
            valveLevel.textContent = valveLevel;
            // TODO: Send API request to update valve opening level
        });
    }

    // Chiama la funzione per ottenere i messaggi e aggiornare la dashboard
    getMessages();
});