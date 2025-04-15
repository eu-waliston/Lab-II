#include <stddef.h>

#ifndef ESTRUTURA_H
#define ESTRUTURA_H


typedef struct listaSensores {
    int id;
    char subtipo[50];

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
// menus.c
// ---------------------------

void limparTela();
void menuPrincipal(ListaDisp* lista);
void menuDispositivos(ListaDisp* lista);
void menuSensorAcionador(ListaDisp* lista);
void menuEventos(ListaDisp* lista);

// ---------------------------
// SensorAcionador.c
// ---------------------------




void adicionarSensor(ListaSensores** lista, int n );
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);
void liberarMemoria(ListaDisp* lista);

#endif
