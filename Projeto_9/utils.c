// Funcções Auxiliarers no codigo

#include <stdlib.h>

void limparTela() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
};

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