#include <stddef.h>

#ifndef ESTRUTURA_H
#define ESTRUTURA_H


//// Estrutura para sensores
//typedef struct ListaSensores {
//    int id;
//    char nome[50];
//    char tipo[50];
//    char subtipo[50];
//    struct ListaSensores* prox;
//} ListaSensores;


typedef struct listaSensores {
        int id;
        char subtipo[50];
        char nome[50];
        char tipo[50];
        struct listaSensores* prox;
} ListaSensores;


typedef struct listaDisp {
    int id;
    char descricao[50];
    char tipo[50];
    char status[50];
    ListaSensores* sensores; 
    struct listaDisp* prox;
} ListaDisp;

extern int idDispositivo;
extern int idSensor;


// ---------------------------
// Estrutura de eventos
// ---------------------------
typedef struct Evento {
    ListaDisp* dispositivo;
    ListaSensores* sensor;
    char descricao[100];
    struct Evento* prox;
} Evento;

// ---------------------------
// Filas de Prioridade
// ---------------------------
typedef struct {
    Evento* Alta;
    Evento* Media;
    Evento* Baixa;
} FilaEventos;

// ---------------------------
// Limpar Tela
// ---------------------------
void limparTela();

// ---------------------------
// menus.c
// ---------------------------
void menuPrincipal(ListaDisp* lista);
void menuDispositivos(ListaDisp* lista);
void menuSensorAcionador(ListaDisp* lista);
void menuEventos(ListaDisp* lista);

// ---------------------------
// SensorAcionador.c
// ---------------------------
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);

void adicionarSensor(ListaSensores** lista, int n );
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);
void liberarMemoria(ListaDisp* lista);

#endif
