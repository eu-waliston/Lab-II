#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

int idDispositivo = 1;
int idSensor = 1;

void adicionarSensor(ListaSensores** lista, char nome[]) {
    ListaSensores* novo = (ListaSensores*)malloc(sizeof(ListaSensores));
    novo->id = idSensor++;
    strcpy(novo->nome, nome);
    novo->prox = *lista;
    *lista = novo;
}

ListaDisp* criarDispositivo(char descricao[], char tipo[], char status[]) {
    ListaDisp* novo = (ListaDisp*)malloc(sizeof(ListaDisp));
    novo->id = idDispositivo++;
    strcpy(novo->descricao, descricao);
    strcpy(novo->tipo, tipo);
    strcpy(novo->status, status);
    novo->sensores = NULL;
    novo->prox = NULL;
    return novo;
}

void adicionarDispositivo(ListaDisp** lista) {
    char descricao[50], tipo[50], status[50];
    int qtdSensores, i;
    char nomeSensor[50];

    printf("\nDigite a descricao do dispositivo (ex: Luz da sala, camera do quintal, etc.): ");
    scanf(" %[^\n]", descricao);
    printf("Digite o tipo do dispositivo (ex: lampada, camera, tomada, etc.): ");
    scanf(" %[^\n]", tipo);
    printf("Digite o status do dispositivo (ex: ligado, desligado, offline, com erro, etc.): ");
    scanf(" %[^\n]", status);
    
    ListaDisp* novo = criarDispositivo(descricao, tipo, status);
    
    printf("Quantos sensores deseja adicionar ao dispositivo? ");
    scanf("%d", &qtdSensores);
    
    for (i = 0; i < qtdSensores; i++) {
        printf("Digite o nome do sensor %d (ex: temperatura, movimento, umidade, etc.): ", i + 1);
        scanf(" %[^\n]", nomeSensor);
        adicionarSensor(&(novo->sensores), nomeSensor);
    }
    
    novo->prox = *lista;
    *lista = novo;
}

void removerDispositivo(ListaDisp** lista) {
    if (*lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }
    
    int id;
    printf("Digite o ID do dispositivo a ser removido: ");
    scanf("%d", &id);
    
    ListaDisp* atual = *lista;
    ListaDisp* anterior = NULL;
    
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Dispositivo com ID %d nao encontrado.\n", id);
        return;
    }
    
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    ListaSensores* sensor = atual->sensores;
    while (sensor != NULL) {
        ListaSensores* tempSensor = sensor;
        sensor = sensor->prox;
        free(tempSensor);
    }
    
    free(atual);
    printf("Dispositivo removido com sucesso.\n");
}

void atualizarDispositivo(ListaDisp** lista) {
    if (*lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }
    
    int id;
    printf("Digite o ID do dispositivo a ser atualizado: ");
    scanf("%d", &id);
    
    ListaDisp* atual = *lista;
    while (atual != NULL && atual->id != id) {
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Dispositivo com ID %d nao encontrado.\n", id);
        return;
    }
    
    printf("Digite a nova descricao do dispositivo: ");
    scanf(" %[^\n]", atual->descricao);
    printf("Digite o novo tipo do dispositivo: ");
    scanf(" %[^\n]", atual->tipo);
    printf("Digite o novo status do dispositivo: ");
    scanf(" %[^\n]", atual->status);
    
    printf("Dispositivo atualizado com sucesso.\n");
}

void buscarDispositivos(ListaDisp* lista, char atributo[], char valor[]) {
    ListaDisp* atual = lista;
    int encontrado = 0;
    
    while (atual != NULL) {
        if ((strcmp(atributo, "descricao") == 0 && strcmp(atual->descricao, valor) == 0) ||
            (strcmp(atributo, "tipo") == 0 && strcmp(atual->tipo, valor) == 0) ||
            (strcmp(atributo, "status") == 0 && strcmp(atual->status, valor) == 0)) {
            printf("\nDispositivo ID: %d\n", atual->id);
            printf("Descricao: %s\n", atual->descricao);
            printf("Tipo: %s\n", atual->tipo);
            printf("Status: %s\n", atual->status);
            encontrado = 1;
        }
        atual = atual->prox;
    }
    
    if (!encontrado) {
        printf("Nenhum dispositivo encontrado com esse criterio.\n");
    }
}

void listarDispositivos(ListaDisp* lista) {
    if (lista == NULL) {
        printf("Nenhum dispositivo cadastrado.\n");
        return;
    }
    
    while (lista != NULL) {
        printf("\nDispositivo ID: %d\n", lista->id);
        printf("Descricao: %s\n", lista->descricao);
        printf("Tipo: %s\n", lista->tipo);
        printf("Status: %s\n", lista->status);
        lista = lista->prox;
    }
}

void liberarMemoria(ListaDisp* lista) {
    while (lista != NULL) {
        ListaSensores* sensor = lista->sensores;
        while (sensor != NULL) {
            ListaSensores* tempSensor = sensor;
            sensor = sensor->prox;
            free(tempSensor);
        }
        ListaDisp* tempDisp = lista;
        lista = lista->prox;
        free(tempDisp);
    }
}
