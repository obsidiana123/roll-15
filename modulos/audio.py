
def audio():
    
    # coding=UTF-8
    import unidecode
    from modulos import fala
    from modulos import modifique_a_pergunta
    from modulos import escute
    from modulos import dicionario
    from modulos import linux
    from modulos import arduino
    from modulos import comunica

    ## indica que esta tudo funcionando    
    fala.fala("sistema funcionando")

    ###### abrir visao
    #import os
    #os.system("python3 visao.py & > log.txt  ")

   


    while True:
        ##abre o dicionario
        conversa = dicionario.leia_dicionario()

        ## ouve o que foi dito
        arduino.piscar() ## indica que vai começar a gravação 
        pergunta=escute.escute()
        ## verifica se o que foi dito esta no dicionario
        verifica= pergunta in conversa  
        if(verifica == True):
            arduino.brilha()
            ## dias a respoesta codificada no dicionario
            fala.fala(conversa[pergunta])  
                
    ##############comandos de sistema#############################################

        ##modifica uma resposta do dicionario
        if(pergunta == "modificar resposta" ):
            modifique_a_pergunta.modifique()          
            verifica = True  ### para continuar codigo
        
        if(pergunta == "não escutei nada" ):
            #não fazer nada          
            verifica = True  ### para continuar codigo
            
        ###desligue o sistema
        if(pergunta == "desligar sistema" ):
            fala.fala("desligando o sistema")
            linux.desligar()         
            verifica = True  ### para continuar codigo
            
        ### reinicia o sistema
        if(pergunta == "reiniciar sistema" ):
            fala.fala("reiniciando sistema")
            linux.reiniciar()
            verifica = True  ### para continuar codigo


            
    ###############comandos para detector #####################################
        ### apaga base
        if(pergunta == "apagar base" ):
            fala.fala("apagando base de pessoas ")
            comunica.escrever('a')
            verifica = True  ### para continuar codigo


        ###  conhecer pessoas 
        if(pergunta == "identificar pessoas" ):
            while True:
                fala.fala("qual é o seu nome ? ")
                nome=escute.escute()
                processamento_1 = unidecode.unidecode(nome) ### retira acentos
                print(nome)
                comunica.nome(processamento_1)
                if (nome != 'não escutei nada'): ## se não escutarnada continua em loop
                    break ###comando que finaliza o while 
                    
            fala.fala("salvando face de  " + nome + ' no banco de dados ')
            comunica.escrever('b')
            verifica = True  ### para continuar codigo

        ### fechar decetor 
        if(pergunta == "fechar decetor" ):
            fala.fala("detector de visao fechado ")
            comunica.escrever('q')
            verifica = True  ### para continuar codigo

        ### treinar base 
        if(pergunta == "treinar base" ):
            fala.fala("base treinada ")
            comunica.escrever(' ')  ##########fazer depois 
            verifica = True  ### para continuar codigo
            
    ###########################################################################        


    #################comando de controle do corpo###########################
        ## pisca o olho 
        if(pergunta == "piscar o olho"):
            fala.fala("ok")
            arduino.piscar()
            verifica = True  ### para continuar codigo

        ## pisca o olho 
        if(pergunta == "pisca o olho"):
            fala.fala("ok")
            arduino.piscar()
            verifica = True  ### para continuar codigo        

       ## setido
        if(pergunta == "sentido"):
            fala.fala("Em posição desentido")
            arduino.sentido()
            verifica = True  ### para continuar codigo

      ## olhe para direita
        if(pergunta == "olhe para direita"):
            fala.fala("olhando para direita")
            arduino.direita()
            verifica = True  ### para continuar codigo

      ## olhe para esquerda
        if(pergunta == "olhe para esquerda"):
            fala.fala("olhando para esquerda")
            arduino.esquerda()
            verifica = True  ### para continuar codigo

     ## olhe para frente
        if(pergunta == "olhe para frente"):
            fala.fala("olhando para frente")
            arduino.sentido()
            verifica = True  ### para continuar codigo  

     ## ande
        if(pergunta == "andar"):
            fala.fala("andando")
            arduino.ande()
            verifica = True  ### para continuar codigo
            
      ## andar para atrais
        if(pergunta == "andar para atrais"):
            fala.fala("andando para atrais")
            arduino.andar_para_atrais()
            verifica = True  ### para continuar codigo

     ## meia volta dieita
        if(pergunta == "meia volta dieita"):
            fala.fala("olhando para frente")
            arduino.meia_volta_dieita()
            verifica = True  ### para continuar codigo

     ## meia volta esquerda
        if(pergunta == "meia volta esquerda"):
            fala.fala("meia volta esquerda")
            arduino.meia_volta_esquerda()
            verifica = True  ### para continuar codigo         

     ## parar
        if(pergunta == "parar"):
            fala.fala("parando movimento")
            arduino.parar()
            verifica = True  ### para continuar codigo         
    ##########################################################################################
                

    ##################não sei responder isto ###################################           
        if(verifica == False): # se o item digitado não esta contido no item executa o codigo abaixo
            fala.fala("ainda não posso responder "+ pergunta + " ,  o que devia responder")

            escuta2 = escute.escute()
            
            if(escuta2 == 'nada'):
                fala.fala("ok")
            else:         
                conversa[pergunta] = escuta2
                dicionario.escreva_dicionario(conversa)
              

    ############################################################################             
