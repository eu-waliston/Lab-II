#include <stdio.h>
#include "estrutura.h"
#include <stdlib.h>

// Prototipando a função que está em outro arquivo

void limparTela();

int main() {
    ListaDisp* dispositivos = NULL;
    int opcao;

    menuPrincipal(&dispositivos);
    
    return 0;
}
