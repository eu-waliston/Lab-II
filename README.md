# 💡 Laboratório de Programação II – UFSM

Este repositório reúne projetos, atividades e práticas desenvolvidas ao longo da disciplina **Laboratório de Programação II** do curso de Sistemas de Informação na **Universidade Federal de Santa Maria (UFSM)**.

O objetivo da disciplina é aplicar conceitos fundamentais de programação estruturada em C, com foco em:

- Estruturas de dados
- Manipulação de memória
- Modularização de código
- Projetos com múltiplos arquivos e persistência de dados

---

## 🔧 Projeto Principal: Sistema de Gerenciamento de Casa Inteligente

Um dos projetos centrais da disciplina é um **sistema modular de controle de dispositivos e sensores inteligentes**, que simula funcionalidades de uma casa conectada.

### ⚙️ Funcionalidades implementadas:

- 📲 **Dispositivos inteligentes**: Representam itens como lâmpadas, câmeras, tomadas, etc.
- 🧠 **Sensores e atuadores acoplados**: Como sensores de movimento, temperatura ou luminosidade.
- 📥 **Lista de valores por sensor**: Cada sensor armazena uma lista de valores lidos ao longo do tempo, com timestamp.
- 🔁 **Fila de eventos por prioridade**: Os eventos são agendados e executados por prioridade (Alta, Média, Baixa).
- 🔄 **Execução de eventos**: Simula ações como “ligar/desligar dispositivo” ao executar eventos da fila.
- 💾 **Importação/Exportação em CSV**: Todos os dados podem ser persistidos e recuperados em arquivos `.csv`.
- 🚫 **Prevenção de duplicações**: O sistema evita registros duplicados ao importar os dados.

---

## 🧱 Tecnologias e Conceitos Utilizados

- ✅ **Linguagem C (padrão C99)**
- 🗃️ **Modularização** usando `.h` e `.c`
- 🧠 **Ponteiros e alocação dinâmica** (`malloc`, `free`)
- 🧺 **Listas encadeadas** e manipulação de estruturas complexas
- 🔄 **Filas com múltiplas prioridades**
- 🗂️ **Persistência de dados com arquivos CSV**
- 🖥️ **Compatível com Linux e Windows**
- 🛠️ **Makefile multiplataforma**
- 📄 **Documentação do código em Markdown e comentários**

---

## ⚙️ Compilação e Execução – Makefile

Este projeto foi configurado com um **Makefile** inteligente que:
- Detecta automaticamente o sistema operacional (Linux/Windows)
- Compila todos os arquivos `.c`
- Gera o executável `sistema` ou `sistema.exe`

### 📁 Estrutura do Projeto

```
.
├── main.c
├── dispositivos.c
├── eventos.c
├── sensores.c
├── menus.c
├── utils.c
├── importarEexportar.c
├── ordenarListar.c
├── estrutura.h
├── Makefile
└── README.md
```

### 🧰 Requisitos

- Compilador `gcc`
- Ferramenta `make`

### 📦 Comandos

```bash
make        # Compila o projeto
make run    # Executa o projeto
make clean  # Remove os binários
```

| Plataforma | Executável     | Comando execução |
|------------|----------------|-------------------|
| Linux/macOS | `./sistema`    | `make run`        |
| Windows     | `sistema.exe`  | `make run`        |

---

## 👨‍🏫 Disciplina

**Laboratório de Programação II**  
Curso de Sistemas de Informação – UFSM   
Ano: 2025 – 1º Semestre

---

## ✍️ Autoria

Projeto desenvolvido em dupla para fins didáticos:

- Nome 1 – Yriane
- Nome 2 – Waliston
