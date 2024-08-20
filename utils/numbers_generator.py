import os
import random

# Script para escrever X (numero definido pelo usuario) inteiros aleatorios (de 1 ate 100) num arquivo texto

while True:
    os.system("clear")
    print("Criando um arquivo...\n")
    while True:
        try:
            file_name = input("Digite o nome do arquivo de saída: ")
            number_qnt = int(input("Digite a quantidade de números a serem impressos no arquivo: "))
            break
        except:
            print("Digite um valor numérico!")

    file = open(f"{file_name}.txt", "w")
    for j in range(1, number_qnt + 1):
        if j == number_qnt:
            file.write(str(random.randint(1, 100)))
        else:
            file.write(str(random.randint(1, 100)) + "\n")

    file.close()
    print(f"Arquivo {file_name}.txt criado com sucesso!")

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
