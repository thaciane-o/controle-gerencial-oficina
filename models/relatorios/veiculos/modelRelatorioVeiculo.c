#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../veiculos/modelVeiculos.h"
#include "../../clientes/modelClientes.h"

// Imprime o relatório na tela
void imprimirRelatorioVeiculo(struct ListaVeiculos *listaVeiculos, struct ListaClientes *listaClientes, char *nome,
                              int id) {
    int existeVeiculo = 0;

    // Verifica se há pelo menos um registro
    if (listaVeiculos->qtdVeiculos > 0) {
        // Exibe todos os registros
        for (int i = 0; i < listaVeiculos->qtdVeiculos; i++) {
            // Verifica se não está deletado e aplica os filtros
            if (listaVeiculos->listaVeiculos[i].deletado == 0 &&
                ((strlen(nome) > 0 && strstr(listaVeiculos->listaVeiculos[i].modelo, nome) != NULL) ||
                 (id != 0 && listaVeiculos->listaVeiculos[i].id == id))) {
                existeVeiculo = 1;
                printf("\n===================\n"
                       "| VEÍCULO %d       |\n"
                       "==================="
                       "\nPROPRIETÁRIO: %s"
                       "\nMODELO: %s"
                       "\nMARCA: %s"
                       "\nANO DE FABRICAÇÃO: %d"
                       "\nPLACA: %s"
                       "\nCHASSI: %s\n",
                        listaVeiculos->listaVeiculos[i].id,
                        listaClientes->listaClientes[listaVeiculos->listaVeiculos[i].id - 1].nome,
                        listaVeiculos->listaVeiculos[i].modelo,
                        listaVeiculos->listaVeiculos[i].marca,
                        listaVeiculos->listaVeiculos[i].anoFabricacao,
                        listaVeiculos->listaVeiculos[i].placa,
                        listaVeiculos->listaVeiculos[i].chassi);
            }
        }
    }

    // Verifica se não há registros
    if (!existeVeiculo) {
        printf("Nenhum veículo foi cadastrado.\n\n");
    }
}

// Armazena o relatório em arquivo
void armazenarRelatorioVeiculo(struct ListaVeiculos *listaVeiculos, struct ListaClientes *listaClientes, char *nome,
                              int id) {
    // Abrindo ou criando arquivo para adicionar dados
    FILE *relatorioVeiculo;

    // Abrindo o arquivo de texto para escrita
    relatorioVeiculo = fopen("RelatorioVeiculo.txt", "w");

    // Verificando se foi possível abrir o arquivo
    if (relatorioVeiculo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de texto.\n\n");
        return;
    }

    // Inserindo os dados no arquivo de relatório
    for (int i = 0; i < listaVeiculos->qtdVeiculos; i++) {
        if (listaVeiculos->listaVeiculos[i].deletado == 0 &&
            ((strlen(nome) > 0 && strstr(listaVeiculos->listaVeiculos[i].modelo, nome) != NULL) ||
             (id != 0 && listaVeiculos->listaVeiculos[i].id == id))) {
            fprintf(relatorioVeiculo, "%d;%s;%s;%s;%d;%s;%s\n",
                listaVeiculos->listaVeiculos[i].id,
                listaClientes->listaClientes[listaVeiculos->listaVeiculos[i].id - 1].nome,
                listaVeiculos->listaVeiculos[i].modelo,
                listaVeiculos->listaVeiculos[i].marca,
                listaVeiculos->listaVeiculos[i].anoFabricacao,
                listaVeiculos->listaVeiculos[i].placa,
                listaVeiculos->listaVeiculos[i].chassi);
        }
    }

    printf("Relatório de veículos realizado com sucesso!\n\n");

    // Fechando o arquivo
    fclose(relatorioVeiculo);
}
