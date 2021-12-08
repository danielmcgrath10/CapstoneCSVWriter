import pandas as pd
import time
import serial
import matplotlib.pyplot as plt
import numpy as np


arduino_port = "COM10" # Use the same port as in Arduino IDE > Tools > Port
baud = 9600
fileName = "Trial1.csv" # Add any name you want for the file

ser = serial.Serial(arduino_port, baud)
ser.flushInput()
print("Connected to Port: " + arduino_port)

HEADERS = ['Timestamp', 'Anemometer 1', 'Anemometer 2', 'Anemometer 3', 'Anemometer 4', 'Pitot Tube']
df = pd.DataFrame(columns = HEADERS)

while True:
    try:
        ser_bytes = ser.readline().decode()
        print(ser_bytes)
        #ser_bytes.rstrip()
        data = [time.time()] + ser_bytes.split(",")
        writeDict = {
            "Timestamp": data[0],
            "Anemometer 1": data[1],
            "Anemometer 2": data[2],
            "Anemometer 3": data[3],
            "Anemometer 4": data[4],
            "Pitot Tube": data[5]
        }
        df = df.append(writeDict, ignore_index=True)
        df.to_csv(fileName, index=False)
    except:
         print("KeyBoard Interrupt")
         break


