import serial
from serial import Serial
import time
from tkinter import *

line = "ERRO"
#####configura a comunicação seriel###########################
try:
    ser = Serial(
    port='/dev/ttyACM0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1)

    ser.write(str.encode('w')) 
    time.sleep(1) 
    ser.write(str.encode('s'))  
    #print("Arduino ok")
    arduino = "arduino encontado"
except:
    #print("Erro arduino nao conectado")
    arduino = "arduino não encontrado "
############################################################


 #servoX=211servoY=299 X=1412 Y=-16492 Z=660 Norte=231.45 A=1.01 V=10.47



####################codigo em loop#######################################
def my_mainloop():
    
    try:
        ser.write(str.encode('3'))
        line = ser.readline()
        line = line.decode('utf-8')
        ##print(line)
    except:
        line = "ERRO"
        
    arduino = Label(window, text= line, font="impact 20 bold").place( x = 150, y = 30)


    line = "servoX=211servoY=299 X=1412 Y=-16492 Z=660 Norte=231.45 A=1.01 V=10.47"

    ##print(line[0:12])
    servoX = Label(window, text= line[0:11], font="impact 20 bold").place( x = 4, y =60)
    servoy = Label(window, text= line[11:22], font="impact 20 bold").place( x = 7, y =90)
    x = Label(window, text= line[22:28], font="impact 20 bold").place( x = 7, y =120)


    window.after(1, my_mainloop)
    
############################################################

        


      

############CRIA INTERFACE##################################
window = Tk()
window.geometry("1000x1000")
window.title("Rogerio IDE")

#texto = Label(window, text= arduino, font="impact 20 bold")
#exto.pack()


#arduino1 = Label(window, text= "arduino  =", font="impact 20 bold").place( x = 4, y = 30)


botao = Button(window, text="Clique Aqui")
botao.pack()


    
window.after(1, my_mainloop)    
window.mainloop()
#############################################################







  
  
  
    



