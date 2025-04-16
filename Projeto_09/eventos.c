// ---------------------------
// GERENCIAMENTO DE EVENTOS
// ---------------------------


/*
    printf("\n===== MENU EVENTO =====\n");
      printf("1. Adicionar evento\n");
      printf("2. Listar eventos agendados\n");
      printf("3. Executar próximo evento\n");
*/

void inicializarFilas(FilaEventos* fila) {
    fila->inicioAlta = fila->fimAlta = NULL;
    fila->inicioMedia = fila->fimMedia = NULL;
    fila->inicioBaixa = fila->fimBaixa = NULL;
}

void adicionarEvento(FilaEventos* fila, ListaDisp* lista, int idDispositivo, int idSensor, char* descricao, char prioridade) {
    ListaDisp* disp = lista;
    while (disp != NULL && disp->id != idDispositivo) disp = disp->prox;
    if (!disp) {
        printf("Dispositivo com ID %d nao encontrado.\n", idDispositivo);
        return;
    }

    ListaSensores* sensor = disp->sensores;
    while (sensor != NULL && sensor->id != idSensor) sensor = sensor->prox;
    if (!sensor) {
        printf("Sensor com ID %d nao encontrado no dispositivo %d.\n", idSensor, idDispositivo);
        return;
    }

    Evento* novo = (Evento*) malloc(sizeof(Evento));
    novo->dispositivo = disp;
    novo->sensor = sensor;
    strcpy(novo->descricao, descricao);
    novo->prox = NULL;

    Evento** inicio = NULL;
    Evento** fim = NULL;

    if (prioridade == 'A') {
        inicio = &fila->inicioAlta;
        fim = &fila->fimAlta;
    } else if (prioridade == 'M') {
        inicio = &fila->inicioMedia;
        fim = &fila->fimMedia;
    } else {
        inicio = &fila->inicioBaixa;
        fim = &fila->fimBaixa;
    }

    if (*inicio == NULL) {
        *inicio = *fim = novo;
    } else {
        (*fim)->prox = novo;
        *fim = novo;
    }

    printf("Evento adicionado com sucesso!\n");
}

void listarEventos(FilaEventos* fila) {
    Evento* atual;

    printf("\n[ALTA prioridade]\n");
    atual = fila->inicioAlta;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[MEDIA prioridade]\n");
    atual = fila->inicioMedia;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }

    printf("[BAIXA prioridade]\n");
    atual = fila->inicioBaixa;
    while (atual) {
        printf("- %s (Disp %d, Sensor %d)\n", atual->descricao, atual->dispositivo->id, atual->sensor->id);
        atual = atual->prox;
    }
}

void executarEvento(FilaEventos* fila) {
    Evento** filaAtual = NULL;

    if (fila->inicioAlta) filaAtual = &fila->inicioAlta;
    else if (fila->inicioMedia) filaAtual = &fila->inicioMedia;
    else if (fila->inicioBaixa) filaAtual = &fila->inicioBaixa;
    else {
        printf("Nenhum evento agendado.\n");
        return;
    }

    Evento* evento = *filaAtual;
    *filaAtual = evento->prox;

    printf("\nExecutando evento: %s\n", evento->descricao);
    evento->dispositivo->status = !evento->dispositivo->status;
    printf("Status do dispositivo %d alterado para: %s\n", evento->dispositivo->id,
           evento->dispositivo->status ? "Ligado" : "Desligado");

    free(evento);
}