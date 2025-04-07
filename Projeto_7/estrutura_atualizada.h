#ifndef ESTRUTURA_H
#define ESTRUTURA_H

// Estrutura para sensores
typedef struct ListaSensores {
    int id;
    char nome[50];
    char tipo[50];
    char subtipo[50];
    struct ListaSensores* prox;
} ListaSensores;

// Estrutura para dispositivos
typedef struct ListaDisp {
    int id;
    char nome[50];
    char tipo[50];
    int status;
    ListaSensores* sensores;
    struct ListaDisp* prox;
} ListaDisp;

// Estrutura de eventos
typedef struct Evento {
    ListaDisp* dispositivo;
    ListaSensores* sensor;
    char descricao[100];
    struct Evento* prox;
} Evento;

// Filas de prioridade
typedef struct {
    Evento* inicioAlta;
    Evento* fimAlta;
    Evento* inicioMedia;
    Evento* fimMedia;
    Evento* inicioBaixa;
    Evento* fimBaixa;
} FilaEventos;

// Funções de dispositivos
ListaDisp* adicionarDispositivo(ListaDisp* lista, int id, const char* nome, const char* tipo, int status);
void listarDispositivos(ListaDisp* lista);
void removerDispositivo(ListaDisp** lista, int id);

// Funções de sensores
void adicionarSensor(ListaDisp* lista, int idDispositivo, int idSensor, const char* nome, const char* tipo, const char* subtipo);
void listarSensores(ListaDisp* lista, int idDispositivo);
void removerSensor(ListaDisp* lista, int idDispositivo, int idSensor);

// Funções de eventos e filas
void inicializarFilas(FilaEventos* fila);
void adicionarEvento(FilaEventos* fila, ListaDisp* lista, int idDispositivo, int idSensor, char* descricao, char prioridade);
void listarEventos(FilaEventos* fila);
void executarEvento(FilaEventos* fila);

#endif
