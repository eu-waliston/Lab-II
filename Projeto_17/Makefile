# Nome do executável
TARGET = sistema

# Fontes
SRCS = main.c dispositivos.c eventos.c menus.c sensores.c utils.c importarEexportar.c ordenar.c timestamp.c

# Objetos (.o)
OBJS = $(SRCS:.c=.o)

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Detectar sistema operacional
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	EXT =
	RUN = ./$(TARGET)
else ifeq ($(OS),Windows_NT)
	EXT = .exe
	RUN = $(TARGET)$(EXT)
else
	EXT =
	RUN = ./$(TARGET)
endif

# Regra padrão
all: $(TARGET)$(EXT)

# Como compilar o executável
$(TARGET)$(EXT): $(OBJS)
	$(CC) $(OBJS) -o $@

# Como compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: all
	$(RUN)

# Limpa os arquivos .o
clean:
	rm -f *.o

# Limpa tudo (inclusive executável)
cleanall: clean
	rm -f $(TARGET) $(TARGET).exe
