# Import the .NET SerialPort class
Add-Type -TypeDefinition @"
    using System;
    using System.IO.Ports;
    public class SerialPortManager : IDisposable
    {
        private SerialPort _serialPort;
        public SerialPortManager(string portName, int baudRate, Parity parity, int dataBits, StopBits stopBits)
        {
            _serialPort = new SerialPort(portName, baudRate, parity, dataBits, stopBits);
            _serialPort.Open();
        }
        public void Write(string data)
        {
            _serialPort.Write(data);
        }
        public void Dispose()
        {
            if (_serialPort != null)
            {
                _serialPort.Close();
                _serialPort = null;
            }
        }
    }
"@

# Create a new SerialPortManager instance
$port = New-Object SerialPortManager -ArgumentList "COM6", 115200, "None", 8, "One"
$jsonObject = @{
    "value"=90
}
# Cycle for 10 times
for ($i = 1; $i -le 10; $i++) {
    # Change the value of the JSON object
    $jsonObject.value = $i
    # Generate a random number between 0 and 180
    $randomNumber = Get-Random -Minimum 0 -Maximum 100

    # Change the value of the JSON object to the random number
    $jsonObject.value = $randomNumber

    # Convert the JSON object to a string
    $jsonString = ConvertTo-Json -InputObject $jsonObject
    # Pause for 1 second
    Start-Sleep -Seconds 4
    # Write your JSON data to the serial port
    $port.Write($jsonString)
    Write-Output $jsonString
}

# Dispose the SerialPortManager instance
$port.Dispose()
