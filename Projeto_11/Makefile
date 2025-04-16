# Nome do executável final
TARGET = casa_inteligente

# Compilador e flags
CC = gcc
CFLAGS = -Wall -g

# Lista de arquivos fontes
SRCS = main.c estrutura.c dispositivos.c menus.c utils.c eventos.c sensores.c

# Dependências (headers)
DEPS = estrutura.h

# Detecta o sistema operacional
OS := $(shell uname -s)

# Define extensão de executável (Windows .exe / Linux não tem)
ifeq ($(OS),Windows_NT)
    EXE = .exe
else
    EXE =
endif

# Regra principal: compilar tudo
all: $(TARGET)$(EXE)

$(TARGET)$(EXE): $(SRCS) $(DEPS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)$(EXE)

# Rodar o programa
run: all
	./$(TARGET)$(EXE)

# Limpa arquivos de build
clean:
	@echo "Limpando arquivos antigos..."
	@rm -f *.o $(TARGET)$(EXE)

# Compatível com Windows (uso do del se quiser)
clean-win:
	@echo Limpando arquivos no Windows...
	@del /Q *.o $(TARGET).exe 2>nul || echo "Nada a remover"
