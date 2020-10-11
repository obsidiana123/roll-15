# coding=UTF-8
import pickle
from modulos import fala
import os
import speech_recognition as sr

r = sr.Recognizer()

arq = open('dialogo.txt','rb') #abrir o arquivo para leitura - o "b" significa que o arquivo é binário
conversa = pickle.load(arq)#Ler a stream a partir do arquivo e reconstroi o objeto original.
arq.close() #fechar o arquivo

def modifique():
        
    fala.fala("qual pergunta deseja modificar")
    print("iniciando gravação")
    os.system("arecord -d 4 -D dmic_sv -c2 -r 44100 -f S32_LE -t wav -V mono -v som.wav") 
    WAV_FILE = 'som.wav'
    with sr.WavFile(WAV_FILE) as source:
        pergunta3 = r.record(source)
    try:
        escuta3 = r.recognize_google(pergunta3, language="pt-BR")
        print(" Voce disse:" + escuta3)
        testo22 = conversa[escuta3]
        fala.fala("qual a nova resposta para "+ escuta3)
        print("iniciando gravação")
                
        os.system("arecord -d 4 -D dmic_sv -c2 -r 44100 -f S32_LE -t wav -V mono -v som.wav") 
        WAV_FILE = 'som.wav'
        with sr.WavFile(WAV_FILE) as source:
            pergunta4 = r.record(source)
        try:
            escuta4 = r.recognize_google(pergunta4, language="pt-BR")
            print(" Voce disse:" + escuta4)
            conversa[escuta3] = escuta4
            arq = open('dialogo.txt','wb') #abrir o arquivo para gravação - o "b" significa que o arquivo é binário
            pickle.dump(conversa,arq) #Grava uma stream do objeto "dic" para o arquivo.
            arq.close()
            print(" resposta modificada")
                    
        except sr.UnknownValueError:
            print("não entendi")
        except sr.RequestError as e:
            print("erro ao chamar google speech; {0}".format(e))     

    except sr.UnknownValueError:
        print("não entendi")
        
        
    except sr.RequestError as e:
        print("erro ao chamar google speech; {0}".format(e))

def vazio(x):
    if(x == "vazio"):
        cv2.putText(frame,'nao encontrado',(50,50), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
        cv2.putText(frame,'nao encontrado',(50,70), cv2.FONT_HERSHEY_PLAIN, 1.0,vermelho)
        #beta = beta + 1
        #print(beta) 

        
