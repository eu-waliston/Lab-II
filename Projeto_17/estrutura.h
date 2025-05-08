#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef ESTRUTURA_H
#define ESTRUTURA_H


// Estrutura que representa um valor com timestamp
typedef struct Valor {
    char timestamp[30];   // Exemplo: "2025-04-23 20:08:34.329"
    float valor;          // Valor lido ou enviado
    struct Valor* prox;   // Próximo valor na lista
} Valor;

// Estrutura dos sensores
typedef struct ListaSensores {
    int id;
    char nome[50];
    char tipo[50];
    char subtipo[50];
    Valor* valores; // Lista de valores associada
    struct ListaSensores* prox;
} ListaSensores;

// Estrutura dos dispositivos, que contém lista de sensores
typedef struct ListaDisp {
    int id;
    char nome[50];
    char tipo[50];
    ListaSensores* sensores;
    struct ListaDisp* prox;
} ListaDisp;

// Estrutura do Evento
typedef struct Evento {
    ListaDisp* dispositivo;
    ListaSensores* sensor;
    char descricao[100];
    float valor;
    struct Evento* prox;
} Evento;

// Filas de prioridade (Alta, Média, Baixa)
typedef struct {
    Evento* Alta;
    Evento* Media;
    Evento* Baixa;
} FilaEventos;

extern int idDispositivo;
extern int idSensor;

// ---------------------------
// evento.c
// ---------------------------

void inicializarFilas(FilaEventos* fila);
void adicionarEvento(FilaEventos* fila, ListaDisp* lista);
void listarEventos(FilaEventos* fila);
void executarEvento(FilaEventos* fila);
void limparFilas(FilaEventos* fila);

// ---------------------------
// menus.c
// ---------------------------
void limparTela();
void menuPrincipal(ListaDisp* lista, FilaEventos* fila);
void menuDispositivos(ListaDisp* lista, FilaEventos* fila);
void menuSensorAcionador(ListaDisp* lista, FilaEventos* fila);
void menuEventos(ListaDisp* lista, FilaEventos* fila);

// ---------------------------
// SensorAcionador.c
// ---------------------------

void adicionarSensor(ListaDisp** lista);
void adicionarSensorNoDisp(ListaDisp** lista);
void listarSensores(ListaDisp* lista);
void removerSensor(ListaDisp* lista);
int verficarSeHaDisp(ListaDisp** lista);

// ---------------------------
// Dispositivo.c
// ---------------------------
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);


// ---------------------------
// utils.c
// ---------------------------
void liberarMemoria(ListaDisp* lista);
void mostrarInformacao(ListaDisp* lista);
ListaDisp* obterDispositivoPorID(ListaDisp* lista);
ListaSensores* obterSensorPorID(ListaDisp* lista, ListaSensores** anterior);
void liberarFilaEventos(FilaEventos* fila);
void liberarEventos(Evento* evento);

//import export 
void exportarValoresCSV(ListaDisp* lista, const char* nomeArquivo);

#endif
