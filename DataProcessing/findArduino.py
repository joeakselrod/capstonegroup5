import serial.tools.list_ports

# returns a list of all the serial ports connected to computer
# Example 'COM3 - Arduino Nano (COM3)'
def get_ports():
    ports = serial.tools.list_ports.comports()
    return ports

# function to parse port names and look for arduino
def findArduino(portsFound):

    commPort = 'None'
    numConnection = len(portsFound)

    for i in range(0,numConnection):

        # cast each list item into string
        strPort = str(portsFound[i])

        if 'Arduino' in strPort:
            # split the name of the connection by spaces
            splitPort = strPort.split(' ')
            # 'COM3 - Arduino Nano (COM3)'
            # We just want the first part for the port so return that
            commPort = (splitPort[0])

    return commPort