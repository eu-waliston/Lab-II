#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

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

void exportarValoresCSV(ListaDisp* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "a+");
    if (!arquivo) {
        printf("Erro ao abrir arquivo para exportacao.\n");
        return;
    }

    ListaDisp* disp = lista;
    while (disp) {
        ListaSensores* sensor = disp->sensores;
        while (sensor) {
            Valor* val = sensor->valores;
            while (val) {
                if (!jaFoiExportado(nomeArquivo, val->timestamp, disp->id, sensor->id)) {
                    fprintf(arquivo, "%s, %d, %d, %.2f\n", val->timestamp, disp->id, sensor->id, val->valor);
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

void importarValoresCSV(ListaDisp* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Arquivo CSV nao encontrado para importar.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char timestamp[30];
        int idDisp, idSens;
        float valor;

        sscanf(linha, "%[^,], %d, %d, %f", timestamp, &idDisp, &idSens, &valor);

        ListaDisp* disp = lista;
        while (disp && disp->id != idDisp) disp = disp->prox;
        if (!disp) continue;

        ListaSensores* sensor = disp->sensores;
        while (sensor && sensor->id != idSens) sensor = sensor->prox;
        if (!sensor) continue;

        // Verifica se valor já existe
        Valor* atual = sensor->valores;
        int duplicado = 0;
        while (atual) {
            if (strcmp(atual->timestamp, timestamp) == 0 && atual->valor == valor) {
                duplicado = 1;
                break;
            }
            atual = atual->prox;
        }
        if (duplicado) continue;

        // Cria novo valor
        Valor* novo = (Valor*)malloc(sizeof(Valor));
        strcpy(novo->timestamp, timestamp);
        novo->valor = valor;
        novo->prox = sensor->valores;
        sensor->valores = novo;
    }

    fclose(arquivo);
    printf("Importacao concluida.\n");
}
