
var graph = document.getElementById('graph').getContext('2d');

// data for demonstration purposes
var data = {
    labels: ["Time 1", "Time 2", "Time 3", "Time 4", "Time 5"],
    datasets: [{
    label: "River Level Graph",
    data: [20, 18, 20, 23, 20], // I dati del tuo grafico
    backgroundColor: "rgba(75,192,192)", // Colore di sfondo del grafico
    borderColor: "rgba(75,192,192)", // Colore del bordo del grafico
    borderWidth: 1 // Spessore del bordo del grafico
    }]
};

var chart = new Chart(graph, {
    type: 'line', // Puoi scegliere il tipo di grafico (bar, line, pie, etc.)
    data: data,
});

// Function to update the status
function updateStatus(status) {
    document.getElementById('statusValue').textContent = status;
}

// Function to update the valve level
function updateValveLevel() {
    const valveLevel = document.getElementById('valveLevel').value;
    console.log('Setting valve level to:', valveLevel);
    // TO-DO:  Implement the logic to update the valve level remotely
}

// Initialize the dashboard
function initializeDashboard() {
    updateGraph();
    updateStatus('NORMAL');
}

// Initialize the dashboard when the page loads
window.onload = initializeDashboard;