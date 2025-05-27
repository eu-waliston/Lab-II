#include <stddef.h>

#ifndef ESTRUTURA_H
#define ESTRUTURA_H

typedef struct ListaValores {
    char timestamp[30];   
    float valor;          
    struct ListaValores* prox;   
} Valor;

typedef struct listaSensores {
    int id;
    char tipo[50];
    char subtipo[50];
    Valor* valores; // Lista de valores associada
    struct listaSensores* prox;
} ListaSensores;


typedef struct listaDisp {
    int id;
    char descricao[50];
    char tipo[50];
    char status[50];
    ListaSensores* sensores; 
    int contadorSensores; 
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
//ordenarListar.c 
// ---------------------------
void listarValoresSensor(ListaDisp* lista);
void listarValores(ListaSensores* sensor, int ordemCrescente);
int compararTimestamps(const void* a, const void* b);

// ---------------------------
// importarEexportar.c
// ---------------------------
void importarValoresCSV(ListaDisp** lista,  char* nomeArquivo);
ListaDisp* encontrarOuCriarIDDispositivo(ListaDisp** lista, int id);
ListaSensores* encontrarOuCriarIDSensor(ListaSensores** sensores, int id);
void adicionarValorSensor(ListaSensores* sensor, const char* timestamp, float valor);
int jaFoiExportado(const char* nomeArquivo, const char* timestamp, int idDisp, int idSens);
void exportarValoresCSV(ListaDisp* lista,  char* nomeArquivo);

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
void adicionarSensor(ListaDisp* lista);
void adicionarSensorNoDisp(ListaDisp** lista);
void listarSensores(ListaDisp* lista, int num);
void removerSensor(ListaDisp* lista);
int verficarSeHaDisp(ListaDisp** lista);
void incluirValoresSensor(ListaDisp* dispositivos);

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
void imprimirSensoresDoDispositivo(ListaDisp* lista);
void valorAtual(ListaSensores* novoSensor);
void obterTimestampAtual(char* buffer, size_t size);


#endif
