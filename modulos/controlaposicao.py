#from modulos import arduino
#vermelho = (0, 0, 255)
#azul = (255, 0, 0)

def controlaposicaoX(x):
    #controlapoicao
    if(x < 30):
        try:
            #ser.write(str.encode('a'))
            #arduino.enviar('a')
            comunica.escrever_arduino('a')
            return('direita')
        except:
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ')

            
 

    if(x > 50):
        try:
            #ser.write(str.encode('d'))
            #arduino.enviar('d')
            comunica.escrever_arduino('d')
            return('esquerda')
        except:
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ')


    if((x >= 30) & (x < 50)):
        try:
            #ser.write(str.encode('p'))
            #arduino.enviar('p')
            comunica.escrever_arduino('p')
            return('centro horizoltal')
        except:
            print("erro no arduino")
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ')


def controlaposicaoY(y):

    if(y < 30):
        try:
            #ser.write(str.encode('q'))
            #arduino.enviar('q')
            comunica.escrever_arduino('q')
            return('cima')
        except:
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ')


    if(y > 50):     
        try:
            #ser.write(str.encode('e'))
            #arduino.enviar('e')
            comunica.escrever_arduino('e')
            return('baixo')
        except:
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ')
        
    if((y >= 30) & (y < 50)):
        try:
            #ser.write(str.encode('p'))
            #arduino.enviar('p')
            comunica.escrever_arduino('p')
            return('centro vertical')
        except:
            print("erro no arduino")
            #cv2.putText(frame,'erro ao envar comando ',(50,90), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            return('erro ao envar comando ') 
