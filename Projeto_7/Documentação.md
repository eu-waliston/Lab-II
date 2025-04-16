# 2 [ DOCUMENTAÇÃO ]

# Sistema de Gerenciamento de Casa Inteligente

## Visão Geral
Este documento descreve as atualizações realizadas no projeto da Casa Inteligente, com foco na integração de sensores, gerenciamento de eventos e uso de filas com diferentes prioridades (Alta, Média e Baixa). As modificações foram feitas nos arquivos `estrutura.h`, `estrutura.c` e `main.c`, visando a expansão da funcionalidade do sistema.

---

## Arquivo `estrutura.h`

### O que foi adicionado:
- **Structs novas:**
    - `ListaSensores`: representa uma lista encadeada de sensores em um dispositivo.
    - `Evento`: representa um evento associado a um sensor e dispositivo.
    - `FilaEventos`: organiza os eventos por prioridade (Alta, Média, Baixa).

- **Protótipos de funções:**
    - Manipulação de sensores (`adicionarSensor`, `listarSensores`, `removerSensor`).
    - Gerenciamento de eventos e filas (`inicializarFilas`, `adicionarEvento`, `listarEventos`, `executarEvento`).

---

## Arquivo `estrutura.c`

### O que foi adicionado:

#### 1. Manipulação de sensores
- Permite adicionar, listar e remover sensores vinculados a dispositivos específicos.
- Os sensores são organizados como uma lista encadeada dentro de cada dispositivo.

#### 2. Gerenciamento de eventos com fila de prioridades
- Cada evento está ligado a um dispositivo e a um sensor.
- As filas são separadas por prioridade:
    - Alta (`inicioAlta` / `fimAlta`)
    - Média (`inicioMedia` / `fimMedia`)
    - Baixa (`inicioBaixa` / `fimBaixa`)
- Funções permitem:
    - Inicialização das filas
    - Adição de eventos conforme prioridade
    - Execução (e remoção) do evento mais urgente

---

## Arquivo `main.c`

### Atualizações feitas:
- Menu interativo expandido com opções para:
    - Adicionar/remover sensores
    - Listar sensores de um dispositivo
    - Adicionar eventos com prioridade
    - Listar eventos agendados por prioridade
    - Executar eventos e alternar status do dispositivo

### Funcionalidades novas:
- Sistema de buffer limpo após uso de `scanf` para evitar bugs com `fgets`.
- Verificação de existência do dispositivo e sensor antes de adicionar eventos.
- Uso de listas encadeadas para garantir expansão dinâmica.

---



## Compilação


```bash 
### 1 Execução do projeto V1

gcc main.c sensores.c -o casa_inteligente

```

```bash
### 1 Execução do projeto V2

gcc main.c sensores.c -o sistema

./sistema


```



