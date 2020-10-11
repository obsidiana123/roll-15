#CHAMA MICROFONE


import os
import speech_recognition as sr

r = sr.Recognizer()



def escute():
    try:
        print("iniciando gravação")
        os.system("arecord -d 4 -D dmic_sv -c2 -r 44100 -f S32_LE -t wav -V mono -v som.wav") 
        WAV_FILE = 'som.wav'
            
        with sr.WavFile(WAV_FILE) as source:
            pergunta = r.record(source)
        try:
            escuta = r.recognize_google(pergunta, language="pt-BR")
            print(" Voce disse:" + escuta)
            return(escuta)


        except sr.UnknownValueError:
            print("não escutei nada")
            return("não escutei nada")
        
        
        except sr.RequestError as e:
            print("erro ao chamar google speech; {0}".format(e))
        
    except:
        print(' microfone alternativo')

###################################################################################        
        with sr.Microphone() as som:
            
            audio = r.record(som, duration=4)
            try:
                escuta = r.recognize_google(audio, language="pt-BR")
                print(" Voce disse:" + escuta)
                return(escuta)


            except sr.UnknownValueError:
                print("não escutei nada")
                return("não escutei nada")
        
        
            except sr.RequestError as e:
                print("erro ao chamar google speech; {0}".format(e))
        
