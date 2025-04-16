#ifndef ESTRUTURA_H
#define ESTRUTURA_H

// Estrutura para sensores
typedef struct ListaSensores {
    int id;
    char nome[50];
    //char tipo[50];
    //char subtipo[50];
    struct ListaSensores* prox;
} ListaSensores;

typedef struct listaDisp {
    int id;
    char descricao[50];
    char tipo[50];
    char status[50];
    ListaSensores* sensores; 
    struct listaDisp* prox;
} ListaDisp;

// Estrutura de eventos
typedef struct Evento {
    ListaDisp* dispositivo;
    //ListaSensores* sensor;
    char descricao[100];
    struct evento* prox;
} Evento;

// Filas de prioridade
typedef struct {
    Evento* Alta;
    Evento* Media;
    Evento* Baixa;
} FilaEventos;


extern int idDispositivo;
extern int idSensor;


// ---------------------------
// MENU
// ---------------------------
void menuPrincipal(ListaDisp** lista)
void menuDispositivos(ListaDisp** lista)
void menuSensorAcionador(ListaDisp** lista)
void menuEventos(ListaDisp** lista)

// ---------------------------
// DISPOSITIVOS
// ---------------------------
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);

// ---------------------------
// SENSORES E ACIONADOR
// ---------------------------
void adicionarSensor(ListaSensores** lista, char nome[]);
//void removerSensor(ListaSensores** lista, char nome[]);
//void adicionarSensor(ListaSensores** lista, char nome[]);
//void listarSensor(ListaSensores** lista, char nome[]);


// ---------------------------
// EVENTOS
// ---------------------------

// adicionarEventos
// listarEventos
// executarEvento

// ---------------------------
// UTILS
// ---------------------------
void liberarMemoria(ListaDisp* lista);
void mostrarInformacao(ListaDisp* lista);

#endif
