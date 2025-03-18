// Função para adicionar um sensor a um dispositivo
void adicionarSensor(Dispositivo* dispositivo, Sensor* sensor) {
    dispositivo->sensores = (Sensor**)realloc(dispositivo->sensores, sizeof(Sensor*) * (dispositivo->numSensores + 1));
    if (!dispositivo->sensores) {
        printf("Erro ao alocar memória para sensores\n");
        return;
    }
    dispositivo->sensores[dispositivo->numSensores] = sensor;
    dispositivo->numSensores++;
}

// Função para remover um sensor de um dispositivo
void removerSensor(Dispositivo* dispositivo, int idSensor) {
    for (int i = 0; i < dispositivo->numSensores; i++) {
        if (dispositivo->sensores[i]->id == idSensor) {
            liberarSensor(dispositivo->sensores[i]);
            for (int j = i; j < dispositivo->numSensores - 1; j++) {
                dispositivo->sensores[j] = dispositivo->sensores[j + 1];
            }
            dispositivo->numSensores--;
            dispositivo->sensores = (Sensor**)realloc(dispositivo->sensores, sizeof(Sensor*) * dispositivo->numSensores);
            return;
        }
    }
    printf("Sensor não encontrado\n");
}

// Função para listar todos os sensores de um dispositivo
void listarSensores(Dispositivo* dispositivo) {
    printf("Sensores do dispositivo %d:\n", dispositivo->id);
    for (int i = 0; i < dispositivo->numSensores; i++) {
        printf("Sensor ID: %d, Tipo: %d, Valor: %.2f\n", dispositivo->sensores[i]->id, dispositivo->sensores[i]->tipo, dispositivo->sensores[i]->valor);
    }
}

// Função para atualizar o status de um dispositivo
void atualizarStatus(Dispositivo* dispositivo, Status novoStatus) {
    dispositivo->status = novoStatus;
}

// Função para atualizar a descrição de um dispositivo
void atualizarDescricao(Dispositivo* dispositivo, const char* novaDescricao) {
    strcpy(dispositivo->descricao, novaDescricao);
}

// Função para listar todos os dispositivos cadastrados
void listarDispositivos(Dispositivo** dispositivos, int numDispositivos) {
    for (int i = 0; i < numDispositivos; i++) {
        printf("Dispositivo ID: %d, Descrição: %s, Tipo: %d, Status: %d\n", dispositivos[i]->id, dispositivos[i]->descricao, dispositivos[i]->tipo, dispositivos[i]->status);
    }
}
