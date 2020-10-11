import serial
from serial import Serial
import time
from tkinter import *

line = 0
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






####################codigo em loop#######################################
def my_mainloop():
    ser.write(str.encode('v'))
    line = ser.readline()
    line = line.decode('utf-8')
    print(line)
    
    ARDUINOCORRENTE = Label(window, text= line, font="impact 20 bold").place( x = 200, y = 60)
    window.after(1, my_mainloop)
    
############################################################

        


      

############CRIA INTERFACE##################################
window = Tk()
window.geometry("1000x1000")
window.title("Rogerio IDE")

texto = Label(window, text= arduino, font="impact 20 bold")
texto.pack()


corrente = Label(window, text= "corrente  =", font="impact 20 bold").place( x = 4, y = 60)

tensao = Label(window, text= "tensao      =", font="impact 20 bold").place( x = 4, y = 100)  
ARDUINOtensao = Label(window, text= "10", font="impact 20 bold").place( x = 200, y = 100)                                                             

botao = Button(window, text="Clique Aqui")
botao.pack()


    
window.after(1, my_mainloop)    
window.mainloop()
#############################################################







  
  
  
    



