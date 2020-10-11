import pickle
import os

def leia_dicionario():
    arq = open('dialogo.txt','rb') #abrir o arquivo para leitura - o "b" significa que o arquivo é binário
    conversa = pickle.load(arq)#Ler a stream a partir do arquivo e reconstroi o objeto original.
    arq.close() #fechar o arquivo
    print("Respotas programadas: " + str(len(conversa))) # mostra a quantdade de ites na lista conversa
    return(conversa) 
          


def escreva_dicionario(conversa):
    arq = open('dialogo.txt','wb') #abrir o arquivo para gravação - o "b" significa que o arquivo é binário
    pickle.dump(conversa,arq) #Grava uma stream do objeto "dic" para o arquivo.
    arq.close()
    
