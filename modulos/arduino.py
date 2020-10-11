import serial
from serial import Serial
import time




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
    print("Arduino ok")
except:
    print("Erro arduino nao conectado") 
############################################################

###############PISCA O OLHO#################################        


def piscar():
    try:
        print("piscarndo olhos")
        line=ser.readline()
        ser.write(str.encode('v'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")

def sentido():
    try:
        print("em posicao de sentido")
        line=ser.readline()
        ser.write(str.encode('s'))
        line=ser.readline()
        print("cabeca para centro horizontal")
        ser.write(str.encode('w'))
        line=ser.readline()
        print("cabeca para centro vertical")
    except:
        print("erro ao envar comando")        


def brilha():
    try:
        print("piscarndo olhos")
        line=ser.readline()
        ser.write(str.encode('t'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")

def direita():
    try:
        print("virando a cabeça para direita")
        line=ser.readline()
        ser.write(str.encode('a'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")


def esquerda():
    try:
        print("virando a cabeça para esquerda")
        line=ser.readline()
        ser.write(str.encode('d'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")
        

def enviar(aa):
    try:
        ser.write(str.encode(aa))
    except:
        print("erro ao envar comando")

#################################################################
def ande():
    try:
        print("Roll: andando")
        line=ser.readline()
        ser.write(str.encode('l'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")        
        
def andar_para_atrais():
    try:
        print("Roll: andando para atrais")
        line=ser.readline()
        ser.write(str.encode('k'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")    

def meia_volta_dieita():
    try:
        print("Roll: meia volta direita")
        line=ser.readline()
        ser.write(str.encode('n'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")

def meia_volta_esquerda():
    try:
        print("Roll: meia volta esquerda")
        line=ser.readline()
        ser.write(str.encode('h'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")

def parar():
    try:
        print("Roll: parando movimento")
        line=ser.readline()
        ser.write(str.encode('j'))
        line=ser.readline()
        print("line")
    except:
        print("erro ao envar comando")        
        
