#ifndef ESTRUTURA_H
#define ESTRUTURA_H


typedef struct listaSensores {
    int id;
    char nome[50];
    // char tipo[];
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

/*
    typedef struct priAlta{


    } PriAlta;

    typedef struct priMedia{

    } PriMedia;

    typedef struct priBaixa{

    } PriBaixa;

*/

// quando cad o disposivo ele automaticamente esta desligado CERTO
// quando executar o evento mudar o status do dispositivo CERTO 
// cria a funcao dentro(mudarStatusDisp()) da funcao executar_evento() para mudar o status do dipositivo CERTO 


extern int idDispositivo;
extern int idSensor;


void adicionarSensor(ListaSensores** lista, char nome[]);
ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]);
void adicionarDispositivo(ListaDisp** lista);
void removerDispositivo(ListaDisp** lista);
void atualizarDispositivo(ListaDisp** lista);
void buscarID(ListaDisp* lista, int valor);
void buscarPorDescricao(ListaDisp* lista, char descricao[]);
void listarDispositivos(ListaDisp* lista);
void liberarMemoria(ListaDisp* lista);


void mostrarInformacao(ListaDisp* lista);

#endif
