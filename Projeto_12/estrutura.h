#include <stddef.h>

#ifndef ESTRUTURA_H
#define ESTRUTURA_H


typedef struct listaSensores {
    int id;
    char tipo[50];
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
//void adicionarEvento(FilaEventos* fila, ListaDisp* lista, int idDisp, int idSensor, char* descricao, float valor, char prioridade);
void adicionarEvento(FilaEventos* fila, ListaDisp* lista);
void listarEventos(FilaEventos* fila, ListaDisp* lista);
void executarEvento(FilaEventos* fila);
void limparFilas(FilaEventos* fila);


// Função de teste completa
void iniciarSistema();

// ---------------------------
// menus.c
// ---------------------------

void limparTela();
void menuPrincipal(ListaDisp* lista, FilaEventos* fila);
void menuDispositivos(ListaDisp* lista);
void menuSensorAcionador(ListaDisp* lista);

void menuEventos(ListaDisp* lista, FilaEventos* fila);

// ---------------------------
// SensorAcionador.c
// ---------------------------

void adicionarSensor(ListaDisp** lista);
void listarSensores(ListaDisp* lista);
void removerSensor(ListaDisp* lista);
int verficarSeHaDisp(ListaDisp** lista);



// ---------------------------
// Dispositivo.c
// ---------------------------
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarSensorDireto(ListaSensores** lista);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);
void liberarMemoria(ListaDisp* lista);
void mostrarInformacao(ListaDisp* lista);

#endif
