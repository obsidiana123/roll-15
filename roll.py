from threading import Thread


from modulos import detector
from modulos import audio
from modulos import comunica_arduino
from modulos import pygame


visao = Thread(target= detector.detector)
audio = Thread(target= audio.audio)
comun = Thread(target= comunica_arduino.comunica_arduino)
pygame =Thread(target= pygame.pygame)

visao.start()
audio.start()
comun.start()
pygame.start()

 
