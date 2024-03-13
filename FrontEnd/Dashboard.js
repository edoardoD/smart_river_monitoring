document.addEventListener("DOMContentLoaded", function() {

    let dataWater = [];
    let valve;
    let system_status;
    let WL4 = 30;

    // Funzione per ottenere i messaggi dal server Flask
    function getMessages() {
        fetch('http://127.0.0.1:5000/api/messages')
            .then(response => response.json())
            .then(data => updateDashboard(data))
            .catch(error => console.error('Errore durante il recupero dei messaggi:', error));
    }

    // Funzione per aggiornare la dashboard con i dati ricevuti
    function updateDashboard(data) {

        //processinga data
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
        const valveLevel = document.getElementById('valveLevel');
        valveLevel.value = valve;

        // Send Valve Opening Level
        const setValveButton = document.getElementById("set_button");
        setValveButton.addEventListener('input', function() {
            valve = valveLevel.value;
            // TODO: Send API request to update valve opening level
        });

        // Update Water Level Status
        const water = document.getElementById("water");
        const valueWater = document.getElementById("value");
        water.style.opacity = 1;
        valueWater.textContent = Math.round((dataWater[dataWater.length-1]/WL4)*100) + "%";
        water.style.height = valueWater.textContent;
    }

    // Chiama la funzione per ottenere i messaggi e aggiornare la dashboard
    getMessages();
});