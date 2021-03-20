import serial.tools.list_ports
from findArduino import *

foundPorts = get_ports()
connectPort = findArduino(foundPorts)

if connectPort != 'None':
    print('Connected to ' + connectPort)
    # initiate serial connection
    ser = serial.Serial(connectPort,baudrate = 9600, timeout = 1)
    # baudrate will need to be set
    while 1:
        arduinoData = ser.readline()
        print(arduinoData)
    
else:
    print('Connection Issue')

print('Done')