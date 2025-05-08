#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

//🔧 Exportar para CSV (exportarValoresCSV)

//Percorre todos os sensores de todos os dispositivos e salvar os valores em um arquivo .csv,
//evitando valores repetidos (supondo que não haja duplicatas na memória).

void exportarValoresCSV(ListaDisp* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    //fprintf(arquivo, "timestamp,id_dispositivo,id_sensor,valor\n");
    fprintf(arquivo, "%s,%d,%d,%.2f\n", lista->id, lista->sensores->id, lista->sensores->valor);


    for (ListaDisp* d = lista; d != NULL; d = d->prox) {
        for (ListaSensores* s = d->sensores; s != NULL; s = s->prox) {
            for (ListaValores* v = s->valores; v != NULL; v = v->prox) {
                fprintf(arquivo, "%s,%d,%d,%.2f\n", v->timestamp, d->id, s->id, v->valor);
            }
        }
    }

    fclose(arquivo);
    printf("Exportado com sucesso para %s!\n", nomeArquivo);
}

//📥 Importar do CSV (importarValoresCSV)

//Ler os dados do CSV e adicioná-los ao sensor correspondente,
//evitando duplicação (verificando timestamp e valor já existente).

/*
int valorJaExiste(ListaValores* lista, const char* timestamp, float valor) {
    for (ListaValores* v = lista; v != NULL; v = v->prox) {
        if (strcmp(v->timestamp, timestamp) == 0 && v->valor == valor) {
            return 1; // Já existe
        }
    }
    return 0;
}

void importarValoresCSV(ListaDisp* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // pular cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        char timestamp[30];
        int id_disp, id_sens;
        float valor;

        if (sscanf(linha, "%[^,],%d,%d,%f", timestamp, &id_disp, &id_sens, &valor) == 4) {
            ListaDisp* disp = lista;
            while (disp && disp->id != id_disp) disp = disp->prox;
            if (!disp) continue;

            ListaSensores* sens = disp->sensores;
            while (sens && sens->id != id_sens) sens = sens->prox;
            if (!sens) continue;

            if (!valorJaExiste(sens->valores, timestamp, valor)) {
                ListaValores* novo = (ListaValores*)malloc(sizeof(ListaValores));
                strcpy(novo->timestamp, timestamp);
                novo->valor = valor;
                novo->prox = sens->valores;
                sens->valores = novo;
            }
        }
    }

    fclose(arquivo);
    printf("Importação concluída com sucesso!\n");
}

// 🧪 Exemplos de uso

//exportarValoresCSV(lista, "valores.csv");
//importarValoresCSV(lista, "valores.csv");
*/