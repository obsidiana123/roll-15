from pymemcache.client import base

client = base.Client(('localhost', 11211))

def escrever(x):
    client.set('detector', x)



def ler(x):
    x = client.get(x)
    return(x)


def nome(x):
    client.set('nome', x)

def ler_arduino():
    x = client.get('arduino')
    return(x)

def escrever_arduino(x):
    client.set('arduino', x)    
