import numpy as np
import math
import serial
from GUI import variable
from time import sleep
from threading import Thread
import csv

def timer():
    for i in range(40):
        variable["T"].set(value=str(i))
        variable["P"].set(value = str((i/40)*100))
        sleep(1)


def process_data(data):
    final_parsed = {}
    data = data[1:-1]
    sep = data.split(",")
    for i in sep:
        d = i.split(":")
        print(d)
        final_parsed[d[0]] = d[1]
    for key,value in final_parsed.items():
        if key == "R":
            if value == "0":
                variable["W"].set(value="Exercise:\n"+"NA")
                variable["I"].set(value="Repetition:\n"+"0")
                variable["ID"].set(value="Scan RFID to Begin")
                variable["T"].set(value = "0")
                variable["P"].set(value = "0")
            elif value == "1":
                Timer = Thread(target=timer, args=[])
                Timer.start()
        elif key == "W":
            variable["W"].set(value = "Exercise:\n"+value)
        elif key == "I":
            variable["I"].set(value = "Repetition:\n"+value)
        elif key == "ID":
            variable["ID"].set(value = "Welcome:\n"+value)
        
    print(final_parsed)
    
def BT(port_num,speed):
    global variable
    
    ser = serial.Serial(
            # Serial Port to read the data from
            port=port_num,
     
            #Rate at which the information is shared to the communication channel
            baudrate = speed,
       
            #Applying Parity Checking (none in this case)
            parity=serial.PARITY_NONE,
     
           # Pattern of Bits to be read
            stopbits=serial.STOPBITS_ONE,
         
            # Total number of bits to be read
            bytesize=serial.EIGHTBITS,
     
            # Number of serial commands to accept before timing out
            timeout=1
    )
    a= []
    packet_flag = 0
    data = ""
    # Pause the program for 1 second to avoid overworking the serial port
    while(1):
            x=ser.read(1)
            #print(x)
            x = x.decode("utf-8")
            print(x)
            if(x=="["):
                packet_flag = 1
            elif(x=="]"):
                packet_flag = 0
                data = data + x
                print(data)
                process_data(data)
                data = ""
            if packet_flag == 1:
                data = data + x


    ser.close()
