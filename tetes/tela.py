import PySimpleGUI as sg
import serial
from serial import Serial
import time

try:
    ser = Serial(
    port='/dev/ttyACM0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

 
    #print("Arduino ok")
    arduino = "arduino encontado"
except:
    #print("Erro arduino nao conectado")
    arduino = "arduino não encontrado "

sg.theme('DarkAmber')	# Add a touch of color

line ="1"



# All the stuff inside your window.







while True:
    print(str.encode('3'))
    
    ser.write(b'3')
     
    try:
        time.sleep(10)
        ser.write(str.encode('3'))
        time.sleep(1)
        line = ser.readline()
        #time.sleep(1)
        line = line.decode('utf-8')
        #print(line)
    except:
        line = "ERRO"

     

 #servoX=211servoY=299 X=1412 Y=-16492 Z=660 Norte=231.45 A=1.01 V=10.47
    
    text= line[0:11]
    text= line[11:22]
    text=line[22:28]

    
    layout = [  [sg.Text(line)],
                [sg.Text("servoX="+line[0:11])],
                [sg.Text("servoX="+line[0:11])],
                [sg.Text("servoX="+line[0:11]),],
                [sg.Text(arduino),],
                
            [sg.Text("enviar"), sg.InputText()],
            [sg.Button('Ok'),sg.Button('Cancel')] ]

    
    # Create the Window
    window = sg.Window('Window Title', layout)
    

        
    event, values = window.read()
    
    if event == sg.WIN_CLOSED or event == 'Cancel':	# if user closes window or clicks cancel
        break
    print('You entered ', values[0])
    try:
        ser.write(str.encode(values[0]))
        time.sleep(1)
        line = ser.readline()
        #time.sleep(1)
        line = line.decode('utf-8')
        print(line)
    except:
        line = "ERRO"

window.close()
