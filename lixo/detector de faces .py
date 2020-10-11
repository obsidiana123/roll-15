## "a" apaga base
## "b" treina base
## "c" pergunta o nome 
## "q" fecha o programa
## "e" base apagada
## "r"  responde que o programa foi finalizado 

## client.set('detector', 'a')

import cv2
import numpy as np 
import sqlite3
import os
import imutils

from modulos import treinando_base
from modulos import apagar_database
from modulos import recorta_imagens
from pymemcache.client import base

client = base.Client(('localhost', 11211))


vermelho = (0, 0, 255)
azul = (255, 0, 0)
treina = ' '

while(not (client.get('detector') == b'q')):
  conn = sqlite3.connect('database.db')
  c = conn.cursor()

  fname = "recognizer/trainingData.yml"
  if not os.path.isfile(fname):
    print("Please train the data first")
    exit(0)

  face_cascade = cv2.CascadeClassifier('Haar/haarcascade_frontalcatface.xml')
  cap = cv2.VideoCapture(0)
  recognizer = cv2.face.LBPHFaceRecognizer_create()
  recognizer.read(fname)


  

  
  while(not (client.get('detector') == b'b')):
  
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for (x,y,w,h) in faces:
      cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),3)
      ids,conf = recognizer.predict(gray[y:y+h,x:x+w])
      c.execute("select name from users where id = (?);", (ids,))
      result = c.fetchall()
      try:
        name = result[0][0]
      except IndexError:
        name = " DESCONHEVIDO"
        
      if conf < 50:
        cv2.putText(img, name, (x+2,y+h-5), cv2.FONT_HERSHEY_SIMPLEX, 1, (150,255,0),2)
        cv2.putText(img, str(int(13800/w)), (x,y), cv2.FONT_HERSHEY_SIMPLEX, 1, azul,2) ## distancia face para camera
        cv2.putText(img, str( 320 - (x+ (w/2))), (x,y-50), cv2.FONT_HERSHEY_SIMPLEX, 1, azul,2) # #distancia do centro do face para centro imagem 

      else:
        cv2.putText(img, 'DESCONHECIDO', (x+2,y+h-5), cv2.FONT_HERSHEY_SIMPLEX, 1, vermelho,2)
        cv2.putText(img, str(int(13800/w)), (x,y), cv2.FONT_HERSHEY_SIMPLEX, 1, azul,2)
        cv2.putText(img, str(320 - (x+ (w/2))), (x,y-50), cv2.FONT_HERSHEY_SIMPLEX, 1, azul,2)

    cv2.circle(img, (320, 237), 10, (0,255,0) , -1) # cria um circulo no centro 

    if(client.get('detector') == b'a'):
      #print(client.get('deyector'))
      cv2.putText(img, 'APAGAR BASE', (10,50), cv2.FONT_HERSHEY_SIMPLEX, 1, vermelho,2)
      apagar_database.apagar_database()
      client.set('detector', 'e')

    cv2.imshow('Face Recognizer',img)
  

     
    if cv2.waitKey(20) & 0xFF == ord('e'):
      # apaga database
      apagar_database.apagar_database()

    

      
    

  cap.release()
  cv2.destroyAllWindows()


  
  client.set('detector', 'c')       # pergunta o nome 
  recorta_imagens.recorta_imagens() # captura fotos e cria uma nova data base

print("programa finalizado")
client.set('detector', 'r')

