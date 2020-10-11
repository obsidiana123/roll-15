from modulos import controlaposicao
from modulos import arduino
import time 
import cv2, os
#from numba import jit

width = 150
height = 170
dim = (width, height)

vermelho = (0, 0, 255)
azul = (255, 0, 0)

#CONTROLE DE PROCURA
contole   = "encontrado"
controle2 = 0

# executa codigo roll
os.system("python3 /home/rogerio/Desktop/roll/roll/roll.py & > log.txt")


# Funcao para busca de arquivos
def find(name, path):
    for root, dirs, files in os.walk(path):
        if (name in files) or (name in dirs):
            print("O diretorio/arquivo {} encontra-se em: {}".format(name, root))
            return os.path.join(root, name)
    # Caso nao encontre, recursao para diretorios anteriores
    return find(name, os.path.dirname(path))

# Importar arquivo XML
cv2path = os.path.dirname(cv2.__file__)
haar_path = find('haarcascades', cv2path)
xml_name = 'haarcascade_frontalface_alt2.xml'
xml_path = os.path.join(haar_path, xml_name)

# TODO: Inicializar Classificador
clf = cv2.CascadeClassifier(xml_path)

# Inicializar webcam
cap = cv2.VideoCapture(0)



# Loop para leitura do conteúdo
while(not cv2.waitKey(20) & 0xFF == ord('q')):

        
        
        # Capturar proximo frame
        ret, frame = cap.read()
        
        # redimenciona a imagem 
        frame = cv2.resize(frame, dim, interpolation = cv2.INTER_AREA)

        
        

        # TODO: Converter para tons de cinza
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # TODO: Classificar
        faces = clf.detectMultiScale(gray)
         

        x = 'vazio'

        # le o aquivo message.txt e envia para arduino
        #f = open('message.txt', 'r')           
        #cv2.putText(frame,f.readline(),(50,110), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
        #f.close()

        
      
        # TODO: Desenhar retangulo
        for x, y, w, h in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (azul))
            cv2.putText(frame,str(x),(x,y), cv2.FONT_HERSHEY_PLAIN, 1.0,azul)
            

        
        


            #se encontrar face
            posiçãoX = controlaposicao.controlaposicaoX(x)
            cv2.putText(frame,posiçãoX,(10,10), cv2.FONT_HERSHEY_PLAIN, 1.0,azul)
            posiçãoY = controlaposicao.controlaposicaoY(y)
            cv2.putText(frame,posiçãoY,(10,20), cv2.FONT_HERSHEY_PLAIN, 1.0,azul)
            if(contole == "nao_encontrado"):
                arduino.enviar('6')#brilla os olhos rapidament       
                contole = "encontrado"
            
        
        #se nãp encontar faces
        if(x == "vazio"):
            cv2.putText(frame,"nao encontrado",(10,10), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            cv2.putText(frame,"procuranco",(10,20), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
            #print(contole)
            if(contole == 'encontrado'):            
                contole = "nao_encontrado" 
          
                     
               
        
        
        # Visualizar
        cv2.imshow('Roll',frame)

# Desligar a webcam
cap.release()

#Fechar janela do vídeo
cv2.destroyAllWindows() 
