#ifndef ESTRUTURA_H
#define ESTRUTURA_H


typedef struct listaSensores {
    int id;
    char nome[50];
    struct listaSensores* prox;
} ListaSensores;

// Estrutura para a lista de dispositivos
typedef struct listaDisp {
    int id;
    char descricao[50];
    char tipo[50];
    char status[50];
    ListaSensores* sensores; // Ponteiro para a lista de sensores do dispositivo
    struct listaDisp* prox;
} ListaDisp;

extern int idDispositivo;
extern int idSensor;


void adicionarSensor(ListaSensores** lista, char nome[]);
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
//void buscarDescricao(int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);
void liberarMemoria(ListaDisp* lista);

#endif
