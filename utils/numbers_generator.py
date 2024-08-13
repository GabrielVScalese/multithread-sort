import os
import random

i = 1

while True:
    os.system("clear")
    print("Criando um arquivo...\n")
    while True:
        try:
            numberQnt = int(input("Digite a quantidade de números a serem impressos no arquivo: "))
            break
        except:
            print("Digite um valor numérico!")
            
    file = open(f"arq{i}.txt", "w")
    for j in range(1, numberQnt + 1):
        if j == numberQnt:
             file.write(str(random.randint(1, 100)))
        else:
            file.write(str(random.randint(1, 100)) + "\n")
    
    file.close()
    print(f"Arquivo arq{i}.txt criado com sucesso!")

    while True:
        try:
            option = int(input("Deseja continuar a criar arquivos? Digite 1 para continuar ou 2 para encerrar: "))

            if option != 1:
                if option == 2:
                    break
                else:
                    print("Digite 1 ou 2!")
            else:
                break
        except:
            print("Digite um valor numérico!")

    if option == 2:
        break
                
    i += 1