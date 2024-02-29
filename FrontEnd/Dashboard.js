document.addEventListener("DOMContentLoaded", function() {
    
    // test data - Replace with actual API calls
    const data = {
        waterLevel: [30, 40, 50, 60, 70, 80, 80, 75, 60, 50],
        systemStatus: "NORMAL",
        valveOpeningLevel: 50
    };

    // Chart setup
    const graph = document.getElementById('graph').getContext('2d');
    const waterLevelChart = new Chart(graph, {
        type: 'line',
        data: {
            labels: Array.from({ length: 10 }, (_, i) => i + 1),
            datasets: [{
                label: 'Water Level',
                data: data.waterLevel,
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
});