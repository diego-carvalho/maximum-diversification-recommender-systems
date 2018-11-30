from subprocess import check_output
import os
import numpy as np
from math import sqrt

# Entrada
inst = './instancias' + '/'

# Saida
pasta = 'testes' + '/'

if not os.path.exists(pasta):
    os.makedirs(pasta)

objetos = ["10","5","6","7","8","7", "15", "24"]

# numero de testes
#n = 10
n = 8

# Para cada instancia
for i in range(1,9):

    soma = 0
    valores = []

    # Fazer 10 execucoes
    for j in range(1,n+1):

        # executa
        print(str("./main" +" "+ objetos[i-1] +" "+ inst + "p0" + str(i) + "_c.txt" +" "+ inst + "p0" + str(i) + "_w.txt" +" "+ inst + "p0" + str(i) + "_p.txt" +" "+ "3" +" "+ "4" +" "+ str(j)))
        u = check_output(["./main", objetos[i-1], inst + "p0" + str(i) + "_c.txt", inst + "p0" + str(i) + "_w.txt", inst + "p0" + str(i) + "_p.txt", "3", "4", str(j)])
        
        # salva resultado em arquivo
        fout = open(pasta + "result_" + str(i) + "_" + str(j) + ".txt", "w")
        fout.write(str(u))
        fout.close()

        # calculos
        soma = soma + float(u) 

        # armazena os 10 valores
        valores.append(float(u))

    # media
    media = soma/n
    print "media:", media

    # variancia
    variancia = 0
    for valor in valores:
        variancia = variancia + (valor - media)**2

    variancia = variancia/n
    print "variancia: ", variancia
    #print np.var(valores)

    # desvio
    desvio = sqrt(variancia)
    print "desvio: ", desvio
    #print np.std(valores)

    # IC de 95%
    inferior = media - 2.262*(desvio/sqrt(n))
    superior = media + 2.262*(desvio/sqrt(n))

    # Imprime
    print ">>> Instancia " + str(i) + ": " + str(inferior) + " <= " + str(media) + " <= " + str(superior) 
