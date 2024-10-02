#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VEICULOS 100
#define MAX_MENSALISTAS 50

typedef struct {
    char placa[10];
    char condutor[50];
    time_t horaEntrada;
    float valorPagar;
} Veiculo;

typedef struct {
    char placa[10];
    char condutor[50];
    int diaPagamento;
} Mensalista;

Veiculo veiculos[MAX_VEICULOS];
Mensalista mensalistas[MAX_MENSALISTAS];
int totalVeiculos = 0;
int totalMensalistas = 0;
float rendaTotal = 0;

// Funções auxiliares
void limparTela() {
    system("clear || cls");
}

void pausa() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void entradaVeiculo() {
    limparTela();
    if (totalVeiculos < MAX_VEICULOS) {
        Veiculo novoVeiculo;
        printf("Placa do veículo: ");
        scanf("%s", novoVeiculo.placa);
        printf("Nome do condutor: ");
        scanf("%s", novoVeiculo.condutor);
        novoVeiculo.horaEntrada = time(NULL); // Marca a hora de entrada
        novoVeiculo.valorPagar = 10.0; // Valor inicial de 1 hora
        veiculos[totalVeiculos++] = novoVeiculo;
        printf("\nVeículo registrado com sucesso.\n");
    } else {
        printf("\nCapacidade máxima de veículos atingida.\n");
    }
    pausa();
}

void saidaVeiculo() {
    limparTela();
    if (totalVeiculos == 0) {
        printf("Nenhum veículo no estacionamento.\n");
        pausa();
        return;
    }

    printf("Veículos no estacionamento:\n");
    for (int i = 0; i < totalVeiculos; i++) {
        printf("%d. Placa: %s, Condutor: %s\n", i + 1, veiculos[i].placa, veiculos[i].condutor);
    }

    int index;
    printf("Selecione o veículo que está saindo (número): ");
    scanf("%d", &index);
    index--;

    if (index >= 0 && index < totalVeiculos) {
        time_t horaSaida = time(NULL);
        double tempoDecorrido = difftime(horaSaida, veiculos[index].horaEntrada) / 3600; // Tempo em horas
        if (tempoDecorrido > 1) {
            veiculos[index].valorPagar += (int)(tempoDecorrido - 1) * 5.0;
        }

        printf("Veículo %s saiu.\nTotal a pagar: R$ %.2f\n", veiculos[index].placa, veiculos[index].valorPagar);

        // Solicita a forma de pagamento
        char formaPagamento[20];
        printf("Forma de pagamento (Débito/Crédito/Pix/Dinheiro): ");
        scanf("%s", formaPagamento);

        // Adiciona o valor ao total de renda
        rendaTotal += veiculos[index].valorPagar;

        // Remover o veículo da lista
        for (int i = index; i < totalVeiculos - 1; i++) {
            veiculos[i] = veiculos[i + 1];
        }
        totalVeiculos--;
    } else {
        printf("Veículo inválido.\n");
    }
    pausa();
}

void listaMensalistas() {
    limparTela();
    printf("1. Adicionar Mensalista\n");
    printf("2. Ver Lista de Mensalistas\n");
    int opcao;
    scanf("%d", &opcao);

    if (opcao == 1) {
        if (totalMensalistas < MAX_MENSALISTAS) {
            Mensalista novoMensalista;
            printf("Placa do veículo: ");
            scanf("%s", novoMensalista.placa);
            printf("Nome do condutor: ");
            scanf("%s", novoMensalista.condutor);
            printf("Dia do pagamento: ");
            scanf("%d", &novoMensalista.diaPagamento);
            mensalistas[totalMensalistas++] = novoMensalista;
            printf("Mensalista adicionado com sucesso.\n");
        } else {
            printf("Limite de mensalistas atingido.\n");
        }
    } else if (opcao == 2) {
        printf("Lista de mensalistas:\n");
        for (int i = 0; i < totalMensalistas; i++) {
            printf("%d. Placa: %s, Condutor: %s, Dia de pagamento: %d\n", i + 1, mensalistas[i].placa, mensalistas[i].condutor, mensalistas[i].diaPagamento);
        }
    } else {
        printf("Opção inválida.\n");
    }
    pausa();
}

void relatorio() {
    limparTela();
    printf("Relatório de entrada e saída:\n");
    printf("Total de veículos que entraram: %d\n", totalVeiculos);
    printf("Renda total do dia: R$ %.2f\n", rendaTotal);
    pausa();
}

void alertaMensalistas() {
    limparTela();
    time_t now = time(NULL);
    struct tm *dataAtual = localtime(&now);
    int diaAtual = dataAtual->tm_mday;

    printf("Mensalistas com pagamento no dia %d:\n", diaAtual);
    for (int i = 0; i < totalMensalistas; i++) {
        if (mensalistas[i].diaPagamento == diaAtual) {
            printf("Placa: %s, Condutor: %s\n", mensalistas[i].placa, mensalistas[i].condutor);
        }
    }
    pausa();
}

int main() {
    int opcao;

    do {
        limparTela();
        printf("Sistema de Estacionamento\n");
        printf("1. Entrada de veículo\n");
        printf("2. Saída de veículo\n");
        printf("3. Lista de mensalistas\n");
        printf("4. Relatório de entrada e saída\n");
        printf("5. Alerta de pagamento de mensalistas\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                entradaVeiculo();
                break;
            case 2:
                saidaVeiculo();
                break;
            case 3:
                listaMensalistas();
                break;
            case 4:
                relatorio();
                break;
            case 5:
                alertaMensalistas();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                pausa();
        }
    } while (opcao != 6);

    return 0;
}