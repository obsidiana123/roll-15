# coding=UTF-8
from gtts import gTTS
import os


def fala(diga):
    print("Roll:  "+diga)
    AudioDoTexto = gTTS(text= diga, lang='pt')
    AudioDoTexto.save("/tmp/audio.mp3")
    os.system("mpg321 /tmp/audio.mp3")
