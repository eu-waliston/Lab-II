
33


#Nome do executaél final
EXEC = programa

# Lista de arquivos fonte
SRC = dispositivo.c eventos.c main.c menus.c sensores.c utils.c

# Geração os arquivos objetos
OBS = $(SRC:.c=o)

# Compilaor
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Regra padrão para compilar o executavel
all: $(EXEC)

# Como gerar o executável a partir dos objetos
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para executar o programa apos compilar
run: all
	./$(EXEC)

# Limpar arquivos compiladores
clean:
	rm -f $(OBG) $(EXEC)