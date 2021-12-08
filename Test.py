import pandas as pd
import time
import serial
import matplotlib.pyplot as plt
import numpy as np

# Setting up the values for opening the Serial port
# Use the same port as in Arduino IDE > Tools > Port
arduino_port = "COM10" 
baud = 9600
# Add any name you want for the file
fileName = "Trial1.csv" 

# Opening the serial port using the baud rate and arduino_port
ser = serial.Serial(arduino_port, baud) 
# Flushing the serial port buffer of any data
ser.flushInput() 
# Logging to the console that the connection is successful
print("Connected to Port: " + arduino_port) 

# Instantiating the headers to be used in the pandas dataframe
HEADERS = ['Timestamp', 'Anemometer 1', 'Anemometer 2', 'Anemometer 3', 'Anemometer 4', 'Pitot Tube'] 
# Creating the data frame
df = pd.DataFrame(columns = HEADERS)

# Starting loop to read from the Serial Port
while True:
    # Wrapping attempts to read the Serial port in a try/except so that when the Serial port is 
    # closed we will break the loop
    try:
        # Reading the line from the Serial port and decoding the bytes
        ser_bytes = ser.readline().decode()
        # Printing the bytes to the console so that we can see the output
        print(ser_bytes)
        # Linking the data to a timestamp
        data = [time.time()] + ser_bytes.split(",")
        # Writing the data to a dictionary
        writeDict = {
            "Timestamp": data[0],
            "Anemometer 1": data[1],
            "Anemometer 2": data[2],
            "Anemometer 3": data[3],
            "Anemometer 4": data[4],
            "Pitot Tube": data[5]
        }
        # Adding the dictionary to the dataframe
        df = df.append(writeDict, ignore_index=True)
        # Converting the dataframe to a csv
        df.to_csv(fileName, index=False)
    except:
         print("KeyBoard Interrupt")
         break


