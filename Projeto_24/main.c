#include <stdio.h>
#include "estrutura.h"
#include <stdlib.h>

int main() {
    int idDispositivo = 0;
    
    ListaDisp* listaDispositivos = NULL;  // Ponteiro para a lista de dispositivos
    FilaEventos filaEventos = {NULL, NULL, NULL};  // Inicializando a fila de eventos

    importarValoresCSV(&listaDispositivos, "dados.csv");
    menuPrincipal(listaDispositivos, &filaEventos);

    liberarFilaEventos(&filaEventos);
    
    liberarMemoria(listaDispositivos);
    return 0;
}
