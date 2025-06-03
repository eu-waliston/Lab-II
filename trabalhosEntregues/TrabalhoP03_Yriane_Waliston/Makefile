# Nome do executável
TARGET = sistema

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Arquivos-fonte
SRCS = main.c \
       dispositivos.c \
       eventos.c \
       menus.c \
       sensores.c \
       utils.c \
       importarEexportar.c \
       ordenarListar.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Detecta sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    RUN = .\\$(TARGET).exe
    EXEC = $(TARGET).exe
else
    RM = rm -f
    RUN = ./$(TARGET)
    EXEC = $(TARGET)
endif

# Regra padrão
all: $(EXEC)

# Compilar
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Executar
run: $(EXEC)
	$(RUN)

# Limpar binários e objetos
clean:
	$(RM) $(OBJS) $(EXEC)
