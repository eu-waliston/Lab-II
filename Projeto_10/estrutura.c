#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "estrutura.h"

int idDispositivo = 1;
int idSensor = 1;


// ---------------------------
// menus.c
// ---------------------------
void limparTela() {
        #ifdef _WIN32
            system("cls"); 
        #else
            system("clear"); 
        #endif
    }
    
void menuPrincipal(ListaDisp* dispositivos) {

    int opcao;
    do {
        limparTela(); 
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Opcoes de dispositivo\n");
        printf("2. Opcoes de sensor/acionador\n");
        printf("3. Opcoes de evento\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuDispositivos(dispositivos);
                break;
            case 2:
                menuSensorAcionador(dispositivos);
                break;
            case 3:
                menuEventos(dispositivos);
                break;
            case 0:
                liberarMemoria(dispositivos);
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); 
        getchar(); 
        
    } while (opcao != 3);

}

void menuDispositivos(ListaDisp* dispositivos) {
    int opcao;
    do {
        limparTela(); 

        printf("\n===== MENU DISPOSITIVO =====\n");
        printf("1. Inserir dispositivo\n");
        printf("2. Remover dispositivo >\n");
        printf("3. Atualizar dispositivo \n");
        printf("4. Buscar dispositivos apartir dos atributos;\n");
        printf("5. Listar dispositivos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarDispositivo(&dispositivos);
                break;
            case 2:
                removerDispositivo(&dispositivos);
                break;
            case 3:
                atualizarDispositivo(&dispositivos);
                break;
            case 4:
                int valor, valorId;
                printf("Digite 1 para buscar por Id: \n");
                printf("Digite 2 para buscar por descricao: \n");
                scanf(" %d", &valor);
                if(valor == 1){
                    printf("Digite o ID: ");
                    scanf(" %d", &valorId);
                    buscarID(dispositivos, valorId);
                }

                else if (valor == 2) {
                    char descricaoBusca[50];
                    printf("Digite a descrição: ");
                    scanf(" %[^\n]", descricaoBusca); 
                    buscarPorDescricao(dispositivos, descricaoBusca);
                }

                break;
            case 5:
                listarDispositivos(dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos);
                break;
            default:
                printf("Opcao invalida!\n");
        }


        printf("\nPressione Enter para continuar..."); getchar(); getchar(); 
      
    } while (opcao != 6);
}

void menuSensorAcionador(ListaDisp* dispositivos) {
    int opcao;
    do {
      limparTela(); 

      printf("\n===== MENU SENSOR OU ACIONADOR =====\n");
      printf("1. Adicionar sensor ao dispositivo\n");
      printf("2. Listar sensores de um dispositivo\n");
      printf("3. Remover sensor de um dispositivo\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

      switch (opcao) {
            case 1:
              // adicionaei um comentario aqui pra fazer tudo funcionar <3
              // adicionarSensor(listaSensores, 2);
                break;
            case 2:
                //removerDispositivo(dispositivos);
                break;
            case 3:
                //atualizarDispositivo(dispositivos);
                break;
            case 0:
                menuPrincipal(dispositivos);
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar..."); getchar(); getchar(); 
        
    } while (opcao != 6);
}

void menuEventos(ListaDisp* dispositivos) {
    int opcao;
    do {
      limparTela(); 

      printf("\n===== MENU EVENTO =====\n");
      printf("1. Adicionar evento\n");
      printf("2. Listar eventos agendados\n");
      printf("3. Executar próximo evento\n");
      printf("0. Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);

      switch (opcao) {
            case 1:
                adicionarDispositivo(&dispositivos);
                break;
            case 2:
                removerDispositivo(&dispositivos);
                break;
            case 3:
                atualizarDispositivo(&dispositivos);
                break;
             case 0:
                menuPrincipal(dispositivos);
                break;
            default:
                printf("Opcao invalida!\n");
        }

        printf("\nPressione Enter para continuar..."); getchar(); getchar(); 
        
    } while (opcao != 6);
}


// ---------------------------
// SensorAcionador.c
// ---------------------------

void adicionarSensor(ListaSensores** lista, int n) {
    char tipoSensorAtuador[50], subTipoSensorAtuador[50];

    printf("Digite o tipo (Sensor ou Atuador) %d ", n);
    scanf(" %[^\n]", tipoSensorAtuador);

    printf("Digite o  subtipo do sensor (temperatura, umidade, movimento, etc.)");
    scanf(" %[^\n]", subTipoSensorAtuador);



    //adicionarSensor(&(novo->sensores), nomeSensor);

    ListaSensores* novo = (ListaSensores*)malloc(sizeof(ListaSensores));
    novo->id = idSensor++;
    strcpy(novo->subtipo, subTipoSensorAtuador);
    novo->prox = *lista;
    *lista = novo;
}

// ---------------------------
// dispositivos.c
// ---------------------------

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
    int qtdSensores;
    //int qtdSensores, i >> esse i aqui esta dando Warning tambpem, talvez ele n esteja aqui quanod vc chegar

    printf("\nDigite a descricao do dispositivo (ex: Luz da sala, camera do quintal, etc.): ");
    scanf(" %[^\n]", descricao);
    printf("Digite o tipo do dispositivo (ex: lampada, camera, tomada, etc.): ");
    scanf(" %[^\n]", tipo);
    printf("Digite o status do dispositivo (ex: ligado, desligado, offline, com erro, etc.): ");
    scanf(" %[^\n]", status);

    ListaDisp* novo = criarDispositivo(descricao, tipo, status);

    printf("Quantos sensores deseja adicionar ao dispositivo? ");
    scanf("%d", &qtdSensores);
    for ( int i = 0; i < qtdSensores; i++) {
        /*printf("Digite o nome do sensor %d (ex: temperatura, movimento, umidade, etc.): ", i + 1);
        scanf(" %[^\n]", nomeSensor);*/
        adicionarSensor(&(novo->sensores), i);
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

void buscarID(ListaDisp* lista, int valorid) {
    ListaDisp* atual = lista;
    int encontrado = 0;


    while (atual != NULL) {
        if(atual->id == valorid){
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

void buscarPorDescricao(ListaDisp* lista, char descricaoBuscada[]) {
    ListaDisp* atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->descricao, descricaoBuscada) == 0) {
            printf("\nDispositivo ID: %d\n", atual->id);
            printf("Descricao: %s\n", atual->descricao);
            printf("Tipo: %s\n", atual->tipo);
            printf("Status: %s\n", atual->status);
            encontrado = 1;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("Nenhum dispositivo encontrado com a descrição: %s\n", descricaoBuscada);
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
