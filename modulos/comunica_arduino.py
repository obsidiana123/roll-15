
def comunica_arduino():

    from modulos import arduino
    from modulos import comunica

    while True:
         x = comunica.ler_arduino()
         if(x != None):
             arduino.enviar(x)#envia para o arduino 
