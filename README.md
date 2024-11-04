
# Trabalho Multithread-Sort
Neste projeto, foi implementada a leitura e ordenação de numeros, utilizando arquivos em C, com múltiplas threads.

## Índice
- [Instalação](#instalação)
- [Uso](#uso)

## Instalação
As seguintes instruções descrevem o processo de instalação do projeto.

```bash
# Clone o repositório
git  clone  https://github.com/GabrielVScalese/multithread-sort.git

# Navegue até o diretório do projeto
cd  multithread-sort
```
  
## Uso

### Gerar  Arquivos  de  Entrada
Para utilizar o projeto, primeiro gere os arquivos de entrada. Para criá-los, utilize o script numbers_generator.py, localizado na pasta utils. Com esse script, você pode escolher o nome do arquivo e a quantidade de números que serão gerados, criando um arquivo .txt (salvo na raiz do projeto).

 
### Compilação
Compile o código utilizando o makefile (voce deve estar no mesmo diretório onde ele se encontra).

```bash
# Comando de compilacao
make
```

### Execução
Após a compilação, execute o programa utilizando a seguinte sequência de argumentos:

```bash
# Comando para a execução
./program  2  arq1.txt  -o  saida.txt
```
Explicação
- ./program: executável gerado pelo make
- 2: número de threads a serem utilizadas (pode ser 1, 2, 4 ou 8)
- arq1.txt: arquivos contendo os números para ordenação (pode especificar vários arquivos, separados por espaços)
- -o  saida.txt: arquivo de saída que conterá os números ordenados
