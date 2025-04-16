# 💡 Laboratório de Programação II – UFSM

<p align="center">
  <img src="https://img.shields.io/badge/Linguagem-C-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/Disciplina-Lab--Prog%20II-blueviolet?style=flat-square" />
  <img src="https://img.shields.io/badge/Semestre-2025.1-green?style=flat-square" />
</p>

---

📍 **Curso**: Sistemas de Informação  
🏫 **Universidade**: Universidade Federal de Santa Maria – UFSM  
👨‍💻 **Objetivo da disciplina**: Aplicar os fundamentos da programação estruturada em C, com foco em:

- Estruturas de Dados
- Modularização de código
- Alocação dinâmica e ponteiros
- Projetos reais com múltiplos arquivos

---

## 🔧 Projeto Principal: Sistema de Gerenciamento de Casa Inteligente

Este projeto simula uma **casa inteligente**, onde dispositivos podem ser inseridos, removidos, atualizados e executados com base em eventos organizados por **níveis de prioridade**.

### Funcionalidades principais:

✅ Cadastro e gerenciamento de dispositivos inteligentes  
📡 Inclusão de sensores em cada dispositivo  
🗃️ Organização de eventos em filas de prioridade (Alta, Média, Baixa)  
🎯 Execução de eventos por ordem de prioridade  
🧠 Uso de listas encadeadas e alocação dinâmica de memória

---

## 🧠 Conceitos Abordados

| Conceito                         | Descrição                                                                 |
|----------------------------------|---------------------------------------------------------------------------|
| 📁 Modularização                 | Separação lógica entre arquivos `.c` e `.h` para organização e manutenção |
| 🧠 Ponteiros & Memória Dinâmica  | Uso de `malloc`, `free`, e referências entre estruturas                   |
| 🔁 Listas Encadeadas             | Representação dinâmica de dispositivos e sensores                         |
| ⏳ Fila de Prioridade            | Agendamento inteligente dos eventos com base na urgência                  |
| 🧱 Structs Aninhadas             | Estruturação dos dados com múltiplos níveis hierárquicos                  |
| 🧹 Makefile Multiplataforma     | Compilação automatizada em **Linux** e **Windows**                        |

---

## ⚙️ Estrutura de Arquivos

```
📁 projeto-casa-inteligente/
├── estrutura.c        # Implementação das funções e lógica de dados
├── estrutura.h        # Cabeçalhos e definições de estruturas
├── main.c             # Função principal e interface do sistema
├── Makefile           # Script de build multiplataforma
└── README.md          # Este documento
```

---

## ▶️ Executando o Projeto

### 🐧 Linux / MacOS

```bash
make
./main
```

### 🪟 Windows (via Git Bash, CMD com gcc, ou WSL)

```bash
make
main.exe
```

### 🧹 Para limpar os arquivos compilados:

```bash
make clean
```

---

## 📌 Exemplos de Ações Suportadas

- [x] Inserir novo dispositivo
- [x] Atualizar sensores
- [x] Excluir dispositivos
- [x] Visualizar status da casa
- [x] Executar todos os eventos pendentes

---

## 📚 Aprendizados e Experiência

Este projeto proporcionou:

- 🧠 Consolidação de conceitos avançados em C
- 🛠️ Vivência em organização de projetos modulares
- 🔍 Experiência com filas de prioridade na prática
- 📐 Boas práticas de engenharia de software
- 🔄 Testes manuais e controle de fluxo com menus interativos

---

## ✍️ Autor

Desenvolvido por **[Yriane & Waliston]**, estudantes de Sistemas de Informação – UFSM.

> “A melhor forma de aprender é programando e errando com propósito.” – alguém com um `segmentation fault` no coração 🖤

---

## 📜 Licença

Este repositório está sob a licença [MIT](LICENSE).  
Sinta-se à vontade para estudar, adaptar e compartilhar este material com os devidos créditos.

