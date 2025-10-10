import serial
import time

port = "/dev/cu.HC-05"
baud = 9600



while True:
   try: 
      bluetooth = serial.Serial(port,baud, timeout=1)
      print("Connected")
      break
   except serial.SerialException:
      print("waiting for HC")
      time.sleep(2)

while True:
   if bluetooth.in_waiting > 0:
      print("Reading Bluetooth")
      line = bluetooth.readline().decode().strip()
      if line:
         print("Arduino Says: ", line)
      else:
         print("No")

   