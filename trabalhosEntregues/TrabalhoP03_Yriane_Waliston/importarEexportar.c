#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"


void importarValoresCSV(ListaDisp** lista, char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Verifica se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    if (tamanho == 0) {
        printf("Arquivo vazio, nada a importar.\n");
        fclose(arquivo);
        return;
    }
    rewind(arquivo);

    char linha[150];
    int maiorID = idDispositivo;  // Começa com o valor atual

    while (fgets(linha, sizeof(linha), arquivo)) {
        char timestamp[30];
        int idDisp, idSens;
        float valor;

        linha[strcspn(linha, "\n")] = '\0';

        int lidos = sscanf(linha, "%[^,],%d,%d,%f", timestamp, &idDisp, &idSens, &valor);
        if (lidos == 4) {
            if (idDisp > maiorID) {
                maiorID = idDisp;  // Atualiza o maior ID
            }

            ListaDisp* disp = encontrarOuCriarIDDispositivo(lista, idDisp);
            ListaSensores* sens = encontrarOuCriarIDSensor(&disp->sensores, idSens);
            adicionarValorSensor(sens, timestamp, valor);
        } else {
            printf("Linha inválida: %s\n", linha);
        }
    }

    fclose(arquivo);

    idDispositivo = maiorID + 1;  // Atualiza o ID global para continuar sequência
}


ListaDisp* encontrarOuCriarIDDispositivo(ListaDisp** lista, int id) {
    ListaDisp* atual = *lista;
    while (atual) {
        if (atual->id == id) {
            return atual;  // Já existe
        }
        atual = atual->prox;
    }

    // Não existe, cria
    ListaDisp* novo = (ListaDisp*)malloc(sizeof(ListaDisp));
    novo->id = id;
    strcpy(novo->descricao, "Desconhecido");  
    strcpy(novo->tipo, "Desconhecido");
    strcpy(novo->status, "Desconhecido");
    novo->sensores = NULL;
    novo->contadorSensores = 0;
    novo->prox = *lista;
    *lista = novo;
    return novo;
}



ListaSensores* encontrarOuCriarIDSensor(ListaSensores** sensores, int id) {
    ListaSensores* atual = *sensores;
    while (atual) {
        if (atual->id == id) {
            return atual;  
        }
        atual = atual->prox;
    }

    // Não existe, cria 
    ListaSensores* novo = (ListaSensores*)malloc(sizeof(ListaSensores));

    novo->id = id;
    strcpy(novo->tipo, "Desconhecido");
    strcpy(novo->subtipo, "Desconhecido");
    novo->valores = NULL;
    novo->prox = *sensores;
    *sensores = novo;
    return novo;
}

void adicionarValorSensor(ListaSensores* sensor, const char* timestamp, float valor) {
    Valor* novoValor = (Valor*)malloc(sizeof(Valor));
    if (timestamp != NULL) {
        strcpy(novoValor->timestamp, timestamp);
    } else {
        strcpy(novoValor->timestamp, "NULL");
    }
    novoValor->valor = valor;
    novoValor->prox = sensor->valores;
    sensor->valores = novoValor;
}



// Verifica se o valor já foi exportado
int jaFoiExportado(const char* nomeArquivo, const char* timestamp, int idDisp, int idSens) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return 0;

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char ts[30];
        int disp, sens;
        float valor;
        sscanf(linha, "%[^,], %d, %d, %f", ts, &disp, &sens, &valor);
        if (strcmp(ts, timestamp) == 0 && disp == idDisp && sens == idSens) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

void exportarValoresCSV(ListaDisp* lista, char* nomeArquivo) {
    // Primeiro, verifica se o arquivo existe (modo "r")
    FILE* arquivo = fopen(nomeArquivo, "r");
    int existe = (arquivo != NULL);
    if (existe) fclose(arquivo);

    // Agora abre em "a+" para leitura e escrita no final
    arquivo = fopen(nomeArquivo, "a+");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para exportacao.\n");
        return;
    }

    // Se o arquivo não existia, escreve o cabeçalho
    if (!existe) {
        fprintf(arquivo, "timestamp,id_dispositivo,id_sensor,valor\n");
    }

    ListaDisp* disp = lista;
    while (disp) {
        ListaSensores* sensor = disp->sensores;
        while (sensor) {
            Valor* val = sensor->valores;
            while (val) {
                if (!jaFoiExportado(nomeArquivo, val->timestamp, disp->id, sensor->id)) {
                    fprintf(arquivo, "%s,%d,%d,%.3f\n", val->timestamp, disp->id, sensor->id, val->valor);
                }
                val = val->prox;
            }
            sensor = sensor->prox;
        }
        disp = disp->prox;
    }

    fclose(arquivo);
    printf("Exportacao concluida.\n");
}
