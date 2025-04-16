// ---------------------------
// GERENCIAMENTO DE DISPOSITIVOS
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

// ---------------------------
// MOSTRAR NA TELA 
// ---------------------------

void buscarID(ListaDisp* lista, int valorid) {
    ListaDisp* atual = lista;
    int encontrado = 0;


    while (atual != NULL) {
        if(atual->id == valorid){
            mostrarInformacao(atual);
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
            mostrarInformacao(atual);
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
        mostrarInformacao(lista);
        lista = lista->prox;
    }
}


void mostrarInformacao(ListaDisp* lista){
    ListaDisp* atual = lista;
    printf("\nDispositivo ID: %d\n", atual->id);
    printf("Descricao: %s\n", atual->descricao);
    printf("Tipo: %s\n", atual->tipo);
    printf("Status: %s\n", atual->status);
}
